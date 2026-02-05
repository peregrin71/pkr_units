#!/usr/bin/env python3
"""Scan literal headers and ensure UDL return types are explicit <double> instantiations.

This updates lines like:
  constexpr miles_per_hour_t operator""_mph(long double value) noexcept
  {
      return miles_per_hour_t{static_cast<double>(value)};
  }

to:
  constexpr miles_per_hour_t<double> operator""_mph(long double value) noexcept
  {
      return miles_per_hour_t<double>{static_cast<double>(value)};
  }

It runs over all headers under sdk/include/pkr_units and modifies files in-place.
"""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
LITERAL_GLOB = str(ROOT / 'sdk' / 'include' / 'pkr_units' / '**' / 'impl' / 'literals' / '*.h')

udl_decl_re = re.compile(r'^(\s*)(constexpr\s+)([A-Za-z_:][A-Za-z0-9_:<>]*)\s+(operator""_\w+\s*\([^)]*\)\s*noexcept)', re.MULTILINE)
ctor_re = re.compile(r'\b([A-Za-z_:][A-Za-z0-9_:]*)\s*\{\s*static_cast<\s*double\s*>\(value\)\s*\}')

files = list(Path(ROOT).glob('sdk/include/pkr_units/**/impl/literals/*.h'))
modified = []
for f in files:
    s = f.read_text(encoding='utf-8')
    orig = s

    # Replace UDL declaration return types lacking '<' with '<double>' unless they already have template args
    def decl_sub(m):
        indent = m.group(1)
        pre = m.group(2)
        rtype = m.group(3)
        rest = m.group(4)
        # If return type already contains '<', leave as-is
        if '<' in rtype:
            return m.group(0)
        # Do not modify function pointer types or others (unlikely here)
        new_rtype = rtype + '<double>'
        print(f'Updating return type in {f}: {rtype} -> {new_rtype}')
        return f'{indent}{pre}{new_rtype} {rest}'

    s = udl_decl_re.sub(decl_sub, s)

    # Fix constructor usages like 'X{static_cast<double>(value)}' -> 'X<double>{static_cast<double>(value)}'
    def ctor_sub(m):
        name = m.group(1)
        # if name already has <, skip
        if '<' in name:
            return m.group(0)
        new = name + '<double>{static_cast<double>(value)}'
        print(f'Updating ctor usage in {f}: {name} -> {name}<double>')
        return new

    s = ctor_re.sub(ctor_sub, s)

    if s != orig:
        f.write_text(s, encoding='utf-8')
        modified.append(str(f))

print('Modified files:')
for m in modified:
    print(' -', m)
