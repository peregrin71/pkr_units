#!/usr/bin/env python3
"""
Fix all namespace_config.h include paths to point to correct location
"""

from pathlib import Path
import re

def fix_includes(file_path):
    """Fix namespace_config.h include paths in a file"""
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original = content
    
    # Determine correct path based on file location relative to si_units root
    rel_to_root = Path(file_path).relative_to(Path('c:/Data/projects/si_units/sdk/include/si_units'))
    depth = len(rel_to_root.parts) - 1  # -1 because last part is filename
    
    correct_path = "../" * depth + "namespace_config.h"
    
    # Replace all variations of the old path
    # Pattern 1: "..../impl/details/namespace_config.h"
    content = re.sub(
        r'#include\s+["\'].*?impl/details/namespace_config\.h["\']',
        f'#include "{correct_path}"',
        content
    )
    
    # Pattern 2: <si_units/impl/details/namespace_config.h>
    content = re.sub(
        r'#include\s+<si_units/impl/details/namespace_config\.h>',
        f'#include "{correct_path}"',
        content
    )
    
    if content != original:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(content)
        return True, correct_path
    return False, correct_path

def main():
    base_path = Path('c:/Data/projects/si_units/sdk/include/si_units')
    header_files = list(base_path.glob('**/*.h'))
    
    print(f"Checking {len(header_files)} header files...")
    
    fixed = 0
    for file_path in sorted(header_files):
        success, expected_path = fix_includes(str(file_path))
        if success:
            rel_path = file_path.relative_to(base_path)
            print(f"✓ {rel_path} → {expected_path}")
            fixed += 1
    
    print(f"\nFixed {fixed} files")

if __name__ == '__main__':
    main()
