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
# Default branch; the script will prefer an explicit PKR_CE_REF env var or the current commit SHA
BRANCH = 'main'

INCLUDE_RE = re.compile(r'(#\s*include\s*)(<|\")([^">]+)(>|\")')


def get_ref():
    """Return the git ref to use for raw.githubusercontent URLs.
    Priority:
      1. Environment variable PKR_CE_REF (if set)
      2. Default to BRANCH ('main')

    Note: We intentionally avoid using the local commit SHA so generated
    includes use a stable, human-friendly branch (main) by default.
    """
    env_ref = os.environ.get('PKR_CE_REF')
    if env_ref:
        return env_ref
    return BRANCH


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
    # Determine ref (commit SHA or branch) and set RAW_BASE accordingly
    ref = get_ref()
    RAW_BASE = f'https://raw.githubusercontent.com/{REPO}/{ref}/compiler_explorer/pkr_units'

    print(f'Using ref: {ref} for raw URLs')

    # Clean the existing DEST_ROOT to ensure a fresh copy (avoid stale/partial files)
    import shutil
    if DEST_ROOT.exists():
        print(f'Removing existing {DEST_ROOT} to ensure a clean copy')
        shutil.rmtree(DEST_ROOT)

    # Run copy and rewrite step
    copy_and_rewrite()

    # Generate a top-level helper header (topologically sorted) pinned to the same ref
    try:
        import subprocess
        import sys
        helper_script = Path(__file__).resolve().parents[1] / 'tools' / 'generate_ce_helper.py'
        helper_tmp = Path(__file__).resolve().parents[1] / 'compiler_explorer' / 'pkr_units_helper.tmp.h'
        print('Generating top-level helper header (temporary) using generate_ce_helper.py')
        subprocess.run([sys.executable, str(helper_script), '--branch', ref, '--out', str(helper_tmp)], check=True)

        # Post-process the helper to refer to the CE path rather than sdk/include path
        tmp_text = helper_tmp.read_text(encoding='utf-8')
        sdk_prefix = f'https://raw.githubusercontent.com/{REPO}/{ref}/sdk/include/pkr_units'
        ce_prefix = f'https://raw.githubusercontent.com/{REPO}/{ref}/compiler_explorer/pkr_units'
        fixed = tmp_text.replace(sdk_prefix, ce_prefix)

        final_helper = Path(__file__).resolve().parents[1] / 'compiler_explorer' / 'pkr_units.h'
        final_helper.write_text(fixed, encoding='utf-8')
        print(f'Wrote top-level helper: {final_helper}')

        # Cleanup temp
        try:
            helper_tmp.unlink()
        except Exception:
            pass

    except subprocess.CalledProcessError as e:
        print(f'Failed to generate helper header: {e}')
        # Don't fail the whole script: the CE tree itself is still useful
    except Exception as e:
        print(f'Unexpected error while generating helper header: {e}')

