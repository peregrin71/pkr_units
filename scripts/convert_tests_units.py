#!/usr/bin/env python3
"""
convert_tests_units.py

Small safe script to add <double> to uninstantiated pkr::units unit types in test sources.
Usage:
  python scripts/convert_tests_units.py --preview   # show diffs
  python scripts/convert_tests_units.py --apply     # apply changes in-place

It ignores content inside // comments, /* */ comments and string/char literals.
"""
import argparse
import os
import re
import sys
from pathlib import Path
import difflib

TEST_DIR = Path(__file__).resolve().parents[1] / 'tests'

# Patterns to match in code regions only
PAT_UNIT = re.compile(r"\bpkr::units::([A-Za-z_][A-Za-z0-9_]*_t)\b(?!\s*<)")
PAT_SYMBOL = re.compile(r"\bpkr::units::([A-Za-z_][A-Za-z0-9_]*_t)\s*::")
PAT_UNITCAST = re.compile(r"unit_cast\s*<\s*pkr::units::([A-Za-z_][A-Za-z0-9_]*_t)\s*>")

def mask_code_regions(text: str):
    """Return a boolean list same len as text: True if char is in code (not comment/string)."""
    n = len(text)
    mask = [True] * n
    i = 0
    state = 'code'
    string_delim = ''
    raw_delim = None
    while i < n:
        ch = text[i]
        if state == 'code':
            if ch == '/':
                if i+1 < n and text[i+1] == '/':
                    # line comment
                    mask[i] = mask[i+1] = False
                    i += 2
                    state = 'line_comment'
                    continue
                elif i+1 < n and text[i+1] == '*':
                    mask[i] = mask[i+1] = False
                    i += 2
                    state = 'block_comment'
                    continue
            elif ch == '"' or ch == "'":
                string_delim = ch
                mask[i] = False
                i += 1
                state = 'string'
                continue
            elif ch == 'R' and i+1 < n and text[i+1] == '"':
                # raw string literal R"delim( ... )delim"
                # find delim
                j = i+2
                # read until (
                start = j
                while j < n and text[j] != '(':
                    j += 1
                delim = text[start:j]
                raw_delim = delim
                # mark R" as non-code
                for k in range(i, j+1): mask[k] = False
                i = j+1
                state = 'raw_string'
                continue
            # normal code char
            mask[i] = True
            i += 1
        elif state == 'line_comment':
            mask[i] = False
            if ch == '\n':
                state = 'code'
            i += 1
        elif state == 'block_comment':
            mask[i] = False
            if ch == '*' and i+1 < n and text[i+1] == '/':
                mask[i+1] = False
                i += 2
                state = 'code'
            else:
                i += 1
        elif state == 'string':
            mask[i] = False
            if ch == '\\':
                # skip escaped char
                if i+1 < n:
                    mask[i+1] = False
                    i += 2
                else:
                    i += 1
            elif ch == string_delim:
                i += 1
                state = 'code'
            else:
                i += 1
        elif state == 'raw_string':
            mask[i] = False
            # look for )delim"
            delim = raw_delim
            if ch == ')' and delim is not None:
                if text.startswith(delim + '"', i+1):
                    end = i + 1 + len(delim) + 1
                    for k in range(i, end): mask[k] = False
                    i = end
                    state = 'code'
                    raw_delim = None
                else:
                    i += 1
            else:
                i += 1
        else:
            i += 1
    return mask


def replace_in_code(text: str):
    mask = mask_code_regions(text)
    changed = False

    # helper to perform replacements only where mask True
    def replace_pattern(pattern, repl_func):
        nonlocal text, mask, changed
        out = []
        i = 0
        for m in pattern.finditer(text):
            s, e = m.span()
            if all(mask[k] for k in range(s, e)):
                out.append(text[i:s])
                out.append(repl_func(m))
                i = e
                changed = True
        out.append(text[i:])
        if changed:
            text = ''.join(out)
            mask = mask_code_regions(text)
        return

    # 1) unit type bare -> add <double>
    def repl_unit(m):
        name = m.group(1)
        return f'pkr::units::{name}<double>'
    replace_pattern(PAT_UNIT, repl_unit)

    # 2) ::symbol usages -> ensure template args
    def repl_sym(m):
        name = m.group(1)
        return f'pkr::units::{name}<double>::'
    replace_pattern(PAT_SYMBOL, repl_sym)

    # 3) unit_cast< pkr::units::X_t > -> add <double>
    def repl_uc(m):
        name = m.group(1)
        return f'unit_cast<pkr::units::{name}<double>>'
    replace_pattern(PAT_UNITCAST, repl_uc)

    return text, changed


def process_file(path: Path, apply: bool):
    text = path.read_text(encoding='utf-8')
    new, changed = replace_in_code(text)
    if not changed:
        return None
    diff = ''.join(difflib.unified_diff(text.splitlines(True), new.splitlines(True), fromfile=str(path), tofile=str(path) + '.new'))
    if apply:
        path.write_text(new, encoding='utf-8')
    return diff


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--apply', action='store_true')
    args = parser.parse_args()

    files = list(TEST_DIR.rglob('*.cpp')) + list(TEST_DIR.rglob('*.cxx')) + list(TEST_DIR.rglob('*.h')) + list(TEST_DIR.rglob('*.hpp'))
    total_changes = 0
    diffs = []
    for f in files:
        # skip generated/third party if any
        if 'external' in f.parts:
            continue
        res = process_file(f, apply=args.apply)
        if res:
            diffs.append(res)
            total_changes += 1
    if not diffs:
        print('No changes necessary.')
        return
    for d in diffs:
        print(d)

    print(f'Files changed: {total_changes}')
    if args.apply:
        print('Changes applied.')
    else:
        print('Run with --apply to write these changes.')

if __name__ == '__main__':
    main()
