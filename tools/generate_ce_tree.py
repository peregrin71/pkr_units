#!/usr/bin/env python3
"""Copy headers from sdk/include/pkr_units -> compiler_explorer/pkr_units and
rewrite #include directives that reference headers under pkr_units to
absolute raw GitHub URLs pointing at the compiler_explorer tree.

Example:  #include <pkr_units/impl/decls/unit_t_decl.h>
becomes:    #include "https://raw.githubusercontent.com/peregrin71/pkr_units/main/compiler_explorer/pkr_units/impl/decls/unit_t_decl.h"

Relative includes are resolved and converted if they point inside sdk/include/pkr_units.
Non-local includes (e.g., <vector>) are left unchanged.
"""

import os
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1] / 'sdk' / 'include' / 'pkr_units'
DEST_ROOT = Path(__file__).resolve().parents[1] / 'compiler_explorer' / 'pkr_units'
REPO = 'peregrin71/pkr_units'
BRANCH = 'main'
RAW_BASE = f'https://raw.githubusercontent.com/{REPO}/{BRANCH}/compiler_explorer/pkr_units'

INCLUDE_RE = re.compile(r'(#\s*include\s*)(<|\")([^">]+)(>|\")')


def resolve_include_path(inc, current_rel):
    # inc: string inside <> or ""
    # If it contains 'pkr_units/', make it relative path after that prefix
    if 'pkr_units/' in inc:
        idx = inc.find('pkr_units/')
        rel = inc[idx + len('pkr_units/'):]
        return rel
    # Otherwise treat it as relative ("../impl/foo.h") relative to current_rel
    cur_dir = os.path.dirname(current_rel)
    candidate = os.path.normpath(os.path.join(cur_dir, inc)).replace('\\', '/')
    abs_path = ROOT / candidate
    if abs_path.exists():
        return candidate
    return None


def rewrite_includes(text, current_rel):
    def repl(m):
        prefix = m.group(1)
        quote_open = m.group(2)
        inc = m.group(3)
        quote_close = m.group(4)
        resolved = resolve_include_path(inc, current_rel)
        if resolved:
            url = f'{RAW_BASE}/{resolved}'
            # use double quotes for raw URLs
            return f'{prefix}"{url}"'
        # not a project header: leave unchanged
        return m.group(0)

    return INCLUDE_RE.sub(repl, text)


def copy_and_rewrite():
    files = []
    for path in ROOT.rglob('*.h'):
        rel = path.relative_to(ROOT).as_posix()
        dest = DEST_ROOT / rel
        dest.parent.mkdir(parents=True, exist_ok=True)
        text = path.read_text(encoding='utf-8')
        new_text = rewrite_includes(text, rel)
        dest.write_text(new_text, encoding='utf-8')
        files.append(rel)
    print(f'Copied {len(files)} headers to {DEST_ROOT} and rewrote includes.')


if __name__ == '__main__':
    copy_and_rewrite()
