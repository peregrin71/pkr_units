#!/usr/bin/env python3
"""
Utility to update all SI Units headers to use namespace configuration macros
"""

import re
from pathlib import Path

def get_include_path(file_path):
    """Determine the appropriate include path based on file location"""
    rel_to_sdk = Path(file_path).relative_to(Path('c:/Data/projects/si_units/sdk/include/si_units'))
    depth = len(rel_to_sdk.parts) - 1  # -1 because last part is filename
    
    return "../" * depth + "namespace_config.h"

def update_file(file_path):
    """Update a single file to use namespace macros"""
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original = content
    
    # Check if file has "namespace si"
    if "namespace si" not in content:
        return False, "No 'namespace si' found"
    
    # Find the pragma once line to insert include after
    pragma_match = re.search(r'(#pragma once\n)', content)
    if not pragma_match:
        return False, "No '#pragma once' found"
    
    # Check if namespace_config.h is already included
    if "namespace_config.h" not in content:
        # Insert the include after pragma once
        insert_pos = pragma_match.end()
        include_path = get_include_path(file_path)
        # Find where to insert - after other includes and before namespace
        last_include = max(
            (m.end() for m in re.finditer(r'#include [^\n]+\n', content[:insert_pos + 200])),
            default=insert_pos
        )
        content = (content[:last_include] + 
                  f'#include "{include_path}"\n' + 
                  content[last_include:])
    else:
        # Update old path to new path
        content = re.sub(
            r'#include ["\'].*?/impl/details/namespace_config\.h["\']',
            f'#include "{get_include_path(file_path)}"',
            content
        )
    
    # Replace "namespace si" with PKR_SI_BEGIN_NAMESPACE
    content = re.sub(r'\bnamespace\s+si\s*\n\{', 'PKR_SI_BEGIN_NAMESPACE\n{', content)
    
    # Replace closing namespace with PKR_SI_NAMESPACE_END
    content = re.sub(r'\}\s*//\s*namespace\s+si', 'PKR_SI_NAMESPACE_END', content)
    content = re.sub(r'\}\s*//\s*PKR_SI_NAMESPACE', 'PKR_SI_NAMESPACE_END', content)
    
    if content == original:
        return False, "No changes made"
    
    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return True, "Updated successfully"

def main():
    base_path = Path('c:/Data/projects/si_units/sdk/include/si_units')
    
    # Find all .h files
    header_files = list(base_path.glob('**/*.h'))
    
    print(f"Found {len(header_files)} header files")
    
    updated = 0
    skipped = 0
    
    for file_path in sorted(header_files):
        rel_path = file_path.relative_to(base_path)
        success, message = update_file(str(file_path))
        
        if success:
            print(f"✓ {rel_path}")
            updated += 1
        else:
            print(f"⊘ {rel_path}: {message}")
            skipped += 1
    
    print(f"\nSummary: {updated} updated, {skipped} skipped")

if __name__ == '__main__':
    main()
