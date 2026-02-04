import os,re
ROOT = os.path.join(os.path.dirname(__file__),'..','sdk','include','pkr_units')
INCLUDE_RE = re.compile(r'#\s*include\s*(?:<|\")([^">]+)(?:>|\")')
headers=[]
for dirpath,_,filenames in os.walk(ROOT):
    for fn in filenames:
        if fn.endswith('.h') or fn.endswith('.hpp'):
            rel=os.path.relpath(os.path.join(dirpath,fn),ROOT).replace('\\\\','/')
            headers.append(rel)
headers.sort()
header_set=set(headers)
ref_counts={h:0 for h in headers}
for h in headers:
    p=os.path.join(ROOT,h)
    txt=open(p,'r',encoding='utf-8').read()
    for m in INCLUDE_RE.finditer(txt):
        inc=m.group(1).strip()
        if 'pkr_units/' in inc:
            rel=inc[inc.find('pkr_units/')+len('pkr_units/'):]
        else:
            rel=os.path.normpath(os.path.join(os.path.dirname(h),inc)).replace('\\\\','/')
        if rel in header_set and rel!=h:
            ref_counts[rel]+=1
items=sorted(ref_counts.items(), key=lambda x:(-x[1],x[0]))
for i,(p,c) in enumerate(items[:50],1):
    print(f"{i:2d}. {p} -> {c}")
