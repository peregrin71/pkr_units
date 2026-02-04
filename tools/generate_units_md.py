#!/usr/bin/env python3
"""Generate docs/units_table.md listing unit types and their string constants.

Scans headers under sdk/include/pkr_units for structs that derive from
`details::unit_t` and extracts:
 - unit type name (struct name)
 - `static constexpr std::string_view name{...}` (human name)
 - `static constexpr std::string_view symbol{...}` (ASCII symbol)
 - `static constexpr std::wstring_view w_symbol{L"..."}` (wide symbol)
 - `static constexpr std::u8string_view u8_symbol{u8"..."}` (UTF-8 symbol)

Outputs a markdown table with columns: Header, Unit Type, name, symbol, w_symbol, u8_symbol

Usage:
    python tools/generate_units_md.py
"""

import os
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1] / 'sdk' / 'include' / 'pkr_units'
OUT = Path(__file__).resolve().parents[1] / 'docs' / 'units_table.md'

struct_re = re.compile(r'struct\s+(\w+)\b[^:]*:\s*public\s+details::unit_t[^\{]*\{(.*?)\};', re.S)
name_re = re.compile(r'static\s+constexpr\s+std::string_view\s+name\s*\{\s*"([^"]*)"\s*\}', re.S)
sym_re = re.compile(r'static\s+constexpr\s+std::string_view\s+symbol\s*\{\s*"([^"]*)"\s*\}', re.S)
w_sym_re = re.compile(r'static\s+constexpr\s+std::wstring_view\s+w_symbol\s*\{\s*L"([^"]*)"\s*\}', re.S)
u8_sym_re = re.compile(r'static\s+constexpr\s+std::u8string_view\s+u8_symbol\s*\{\s*u8"([^"]*)"\s*\}', re.S)

rows = []
def strip_comments(text):
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    text = re.sub(r'//.*', '', text)
    return text

def find_matching_brace(s, start_pos):
    i = start_pos
    depth = 0
    in_single = False
    in_double = False
    escape = False
    while i < len(s):
        ch = s[i]
        if escape:
            escape = False
        elif ch == '\\':
            escape = True
        elif in_single:
            if ch == "'":
                in_single = False
        elif in_double:
            if ch == '"':
                in_double = False
        else:
            if ch == "'":
                in_single = True
            elif ch == '"':
                in_double = True
            elif ch == '{':
                depth += 1
            elif ch == '}':
                depth -= 1
                if depth == 0:
                    return i
        i += 1
    return -1

# Simple patterns to locate the string literals inside a struct body
pat_symbol = re.compile(r'static\s+constexpr\s+std::string_view\s+symbol\s*\{\s*"([^"]*)"\s*\}', re.S)
pat_w_symbol = re.compile(r'static\s+constexpr\s+std::wstring_view\s+w_symbol\s*\{\s*L"([^"]*)"\s*\}', re.S)
pat_u8_symbol = re.compile(r'static\s+constexpr\s+std::u8string_view\s+u8_symbol\s*\{\s*u8"([^"]*)"\s*\}', re.S)
pat_name = re.compile(r'static\s+constexpr\s+std::string_view\s+name\s*\{\s*"([^"]*)"\s*\}', re.S)

for path in sorted(ROOT.rglob('*.h')):
    rel = path.relative_to(ROOT).as_posix()
    try:
        raw = path.read_text(encoding='utf-8')
    except Exception:
        continue
    text = strip_comments(raw)

    # Find 'struct NAME' occurrences and extract full body using brace matching
    for m in re.finditer(r'struct\s+(\w+)\b', text):
        unit_type = m.group(1)
        start = m.end()
        # find first '{' after the declaration
        brace_pos = text.find('{', start)
        if brace_pos == -1:
            continue
        decl_part = text[start:brace_pos]
        # ensure this struct inherits from details::unit_t
        if 'details::unit_t' not in decl_part:
            continue
        end_pos = find_matching_brace(text, brace_pos)
        if end_pos == -1:
            continue
        body = text[brace_pos+1:end_pos]

        # Extract fields using simple patterns
        name_val = ''
        symbol_val = ''
        w_symbol_val = ''
        u8_symbol_val = ''

        mn = pat_name.search(body)
        if mn:
            name_val = mn.group(1)
        ms = pat_symbol.search(body)
        if ms:
            symbol_val = ms.group(1)
        mw = pat_w_symbol.search(body)
        if mw:
            s = mw.group(1)
            # If the literal contains backslashes, decode escape sequences; otherwise keep raw unicode
            if '\\' in s:
                import codecs
                try:
                    w_decoded = codecs.decode(s, 'unicode_escape')
                except Exception:
                    w_decoded = s
            else:
                w_decoded = s
            w_symbol_val = w_decoded
        mu = pat_u8_symbol.search(body)
        if mu:
            s = mu.group(1)
            if '\\' in s:
                import codecs
                try:
                    u8_decoded = codecs.decode(s, 'unicode_escape')
                except Exception:
                    u8_decoded = s
            else:
                u8_decoded = s
            u8_symbol_val = u8_decoded

        rows.append({
            'header': rel,
            'unit': unit_type,
            'name': name_val,
            'symbol': symbol_val,
            'w_symbol': w_symbol_val,
            'u8_symbol': u8_symbol_val,
        })

# Sort rows by header then unit
rows.sort(key=lambda r: (r['header'], r['unit']))

# Ensure docs directory exists
OUT.parent.mkdir(parents=True, exist_ok=True)

with OUT.open('w', encoding='utf-8') as f:
    f.write('# Unit types and symbols\n\n')
    f.write('| Header | Unit type | name | symbol (string_view) | w_symbol (wstring_view) | u8_symbol (u8string_view) |\n')
    f.write('|---|---:|---|---|---|---|\n')
    for r in rows:
        # Escape pipe characters
        def esc(s):
            if not s:
                return ''
            return s.replace('|', '\\|')
        f.write(f"| `{r['header']}` | `{r['unit']}` | {esc(r['name'])} | {esc(r['symbol'])} | {esc(r['w_symbol'])} | {esc(r['u8_symbol'])} |\n")

print(f'Wrote {OUT} with {len(rows)} unit entries')
