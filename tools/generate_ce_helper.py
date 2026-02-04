#!/usr/bin/env python3
"""Generate a Compiler Explorer helper header that includes absolute raw GitHub
URLs for all *non-aggregator* headers under sdk/include/pkr_units.

Rules:
- A header is considered "non-aggregator" if, after removing comments and
  preprocessor directives (#include, #pragma, #if, etc.), it contains any
  declaration/definition tokens (class, struct, enum, template, constexpr,
  inline, namespace, using, typedef, concept, requires, operator, static,
  extern, friend, auto <id>(...), or function definitions).
- Aggregator-only headers (those that simply #include other headers and
  contain only comments/pragmas) are excluded.

Output:
- Writes a topologically-sorted list where dependencies appear before
  dependents. When multiple nodes are available, the script prefers
  headers with higher reference counts (i.e., many other headers include them)
  to appear earlier.

Usage:
  python tools/generate_ce_helper.py [--branch BRANCH] [--out FILE]

"""

import os
import re
import sys
from collections import defaultdict, deque

ROOT = os.path.join(os.path.dirname(__file__), '..', 'sdk', 'include', 'pkr_units')
REPO = 'peregrin71/pkr_units'
BRANCH = 'main'
RAW_BASE_TEMPLATE = 'https://raw.githubusercontent.com/{repo}/{branch}/sdk/include/pkr_units'

# Tokens that indicate a header contains declarations/definitions
DECL_TOKENS = [
    r"\bclass\b",
    r"\bstruct\b",
    r"\benum\b",
    r"\btemplate\b",
    r"\bconstexpr\b",
    r"\binline\b",
    r"\bnamespace\b",
    r"\busing\b",
    r"\btypedef\b",
    r"\bconcept\b",
    r"\brequires\b",
    r"\boperator\b",
    r"\bstatic\b",
    r"\bextern\b",
    # function-like detect (return_type name(...)) - simple heuristic
    r"\)\s*->|\w+\s+\w+\s*\([^)]*\)\s*(?:->|\{|;)",
]
DECL_RE = re.compile("(?:%s)" % ("|".join(DECL_TOKENS)))
INCLUDE_RE = re.compile(r'#\s*include\s*(?:<|\")([^">]+)(?:>|\")')


def list_headers(root):
    headers = []
    for dirpath, _, filenames in os.walk(root):
        for fn in filenames:
            if not fn.endswith('.h') and not fn.endswith('.hpp'):
                continue
            path = os.path.join(dirpath, fn)
            rel = os.path.relpath(path, root).replace('\\', '/')
            headers.append(rel)
    headers.sort()
    return headers


def strip_comments(text):
    # Remove block comments
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    # Remove line comments
    text = re.sub(r'//.*', '', text)
    return text


def is_non_aggregator(path, root):
    abs_path = os.path.join(root, path)
    try:
        with open(abs_path, 'r', encoding='utf-8') as f:
            text = f.read()
    except Exception:
        return True  # be conservative: include if unreadable
    body = strip_comments(text)
    # Remove preprocessor directives and blank lines
    lines = [ln for ln in body.splitlines() if ln.strip() and not ln.strip().startswith('#')]
    if not lines:
        return False
    # If any line matches a declaration token, this is non-aggregator
    if DECL_RE.search('\n'.join(lines)):
        return True
    # Heuristic: if there is a namespace bracket block with anything inside
    if re.search(r'namespace\s+\w+\s*\{', '\n'.join(lines)):
        return True
    # Otherwise, treat as aggregator-only
    return False


def resolve_include(inc, current_rel):
    # If include uses pkr_units/... form, extract relative part
    if 'pkr_units/' in inc:
        idx = inc.find('pkr_units/')
        rel = inc[idx + len('pkr_units/'):]
        return rel
    # Otherwise resolve relative to current header
    cur_dir = os.path.dirname(current_rel)
    joined = os.path.normpath(os.path.join(cur_dir, inc)).replace('\\', '/')
    return joined


def build_graph(root, headers):
    header_set = set(headers)
    edges = defaultdict(set)  # header -> included headers (in header_set)
    ref_counts = defaultdict(int)  # counts of how many headers include a header (for popularity)

    for h in headers:
        abs_path = os.path.join(root, h)
        try:
            with open(abs_path, 'r', encoding='utf-8') as f:
                text = f.read()
        except Exception:
            continue
        for m in INCLUDE_RE.finditer(text):
            inc = m.group(1).strip()
            resolved = resolve_include(inc, h)
            if resolved in header_set and resolved != h:
                edges[h].add(resolved)
                ref_counts[resolved] += 1
    # Ensure all headers exist in maps
    for h in headers:
        edges.setdefault(h, set())
        ref_counts.setdefault(h, 0)
    return edges, ref_counts


def topological_sort(headers, edges, ref_counts):
    # Compute indegrees (only for the headers we consider)
    indegree = {h: 0 for h in headers}
    for src, targets in edges.items():
        for t in targets:
            if t in indegree:
                indegree[t] += 1

    # Initialize heap of zero-indegree nodes, prioritized by ref_count desc, then name
    import heapq
    heap = []
    for h, d in indegree.items():
        if d == 0:
            heapq.heappush(heap, (-ref_counts.get(h, 0), h))

    order = []
    indeg = indegree.copy()
    while heap:
        _, n = heapq.heappop(heap)
        if n in order:
            continue
        order.append(n)
        for m in list(edges.get(n, [])):
            if m not in indeg:
                continue
            indeg[m] -= 1
            if indeg[m] == 0:
                heapq.heappush(heap, (-ref_counts.get(m, 0), m))

    # If cycles remain, break them deterministically by picking highest ref_count next
    remaining = [h for h in headers if h not in order]
    if remaining:
        remaining.sort(key=lambda x: (-ref_counts.get(x, 0), x))
        for n in remaining:
            if n not in order:
                order.append(n)
    return order


def generate_helper(branch, out_file):
    raw_base = RAW_BASE_TEMPLATE.format(repo=REPO, branch=branch)
    headers = list_headers(ROOT)

    # Determine which headers are non-aggregator
    include_candidates = [h for h in headers if is_non_aggregator(h, ROOT)]
    include_set = set(include_candidates)

    # Build graph (edges and ref_counts) across all headers to compute popularity
    edges_all, ref_counts = build_graph(ROOT, headers)

    # Optional debug: dump top ref_counts
    if os.environ.get('PKR_DUMP_REFC', ''):
        items = sorted(ref_counts.items(), key=lambda x: (-x[1], x[0]))
        print('Top reference counts:')
        for i,(p,c) in enumerate(items[:40],1):
            print(f'{i:2d}. {p} -> {c}')
        # continue normally

    # Filter edges to the subgraph induced by include_candidates (header -> its includes)
    includes_map = {h: set(t for t in edges_all.get(h, set()) if t in include_set) for h in include_candidates}

    # Build reversed graph (dependency -> dependents) so Kahn's algorithm emits
    # dependencies before dependents when we run topological sort.
    reverse_edges = {h: set() for h in include_candidates}
    for src, targets in includes_map.items():
        for t in targets:
            reverse_edges.setdefault(t, set()).add(src)

    # Ensure all include candidates have entries and ref_counts initialized
    for h in include_candidates:
        reverse_edges.setdefault(h, set())
        ref_counts.setdefault(h, 0)

    # Build an order that respects dependencies (includes_map) but
    # tries to place the most-referred headers as early as possible.
    # Strategy: perform a DFS-based topological order seeded by headers
    # sorted descending by ref_count. For each header, visit its dependencies
    # (sorted by ref_count desc) first, then append the header.
    # This produces a valid ordering where dependencies appear before
    # dependents and popular headers are placed early when possible.
    def build_popularity_order(includes_map, ref_counts, candidates):
        ordered_candidates = sorted(candidates, key=lambda x: (-ref_counts.get(x, 0), x))
        visited = set()
        temp = set()
        output = []

        def visit(node):
            if node in visited:
                return
            if node in temp:
                # cycle detected; break it by ignoring further recursion
                return
            temp.add(node)
            deps = sorted(includes_map.get(node, []), key=lambda x: (-ref_counts.get(x, 0), x))
            for d in deps:
                visit(d)
            temp.remove(node)
            visited.add(node)
            output.append(node)

        for h in ordered_candidates:
            visit(h)
        return output

    # includes_map: header -> its includes (dependencies)
    order = build_popularity_order(includes_map, ref_counts, include_candidates)


    # Emit header content
    lines = []
    lines.append('// Autogenerated Compiler Explorer helper header')
    lines.append('// Includes absolute raw GitHub URLs for non-aggregator headers')
    lines.append('// Ordered: dependencies before dependents, popular headers earlier where possible')
    lines.append('// Seed ordering: headers sorted by reference count (most-referred first)')
    lines.append('#pragma once')
    lines.append('')
    for h in order:
        lines.append(f'#include "{raw_base}/{h}"')

    content = '\n'.join(lines) + '\n'
    with open(out_file, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f'Wrote {out_file} with {len(order)} includes (from {len(headers)} total headers).')


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--branch', default=BRANCH, help='GitHub branch or tag to reference')
    parser.add_argument('--out', default=os.path.join(os.path.dirname(__file__), '..', 'compiler_explorer', 'pkr_units.h'), help='Output helper header path')
    args = parser.parse_args()
    os.makedirs(os.path.dirname(args.out), exist_ok=True)
    generate_helper(args.branch, args.out)
