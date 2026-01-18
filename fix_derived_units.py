#!/usr/bin/env python3
"""
Fix all derived unit type files by:
1. Replacing invalid include path with correct one
2. Replacing bare unit_t< with details::unit_t<
3. Replacing using _base = unit_t< with using _base = details::unit_t<
"""

import re
from pathlib import Path

derived_dir = Path("sdk/include/pkr_units/derived")
files = list(derived_dir.glob("*.h"))

for file_path in sorted(files):
    print(f"\nProcessing {file_path.name}...")
    
    with open(file_path, 'r', encoding='utf-8', errors='replace') as f:
        content = f.read()
    
    original_content = content
    
    # Fix 1: Replace invalid include path
    content = content.replace(
        '#include <pkr_units/impl/details/si_unit.h>',
        '#include "../impl/common/unit.h"'
    )
    
    # Fix 2: Fix namespace_config include path (missing impl/)
    content = content.replace(
        '#include "../namespace_config.h"',
        '#include "../impl/namespace_config.h"'
    )
    
    # Fix 3: Ensure unit.h include is present
    if '#include "../impl/common/unit.h"' not in content:
        # Find the namespace_config include and add after it
        content = content.replace(
            '#include "../impl/namespace_config.h"',
            '#include "../impl/namespace_config.h"\n#include "../impl/common/unit.h"'
        )
    
    # Fix 4: Replace bare unit_t< with details::unit_t<
    # Pattern: public unit_t< or using _base = unit_t<
    content = re.sub(r'\bpublic unit_t<', 'public details::unit_t<', content)
    content = re.sub(r'\busing _base = unit_t<', 'using _base = details::unit_t<', content)
    
    if content != original_content:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(content)
        print(f"  ✓ Fixed {file_path.name}")
    else:
        print(f"  - No changes needed for {file_path.name}")

print("\n✓ All derived unit files processed!")
