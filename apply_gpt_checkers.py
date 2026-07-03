#!/usr/bin/env python3
"""Apply ===CHECKER:ID=== ... ===END=== blocks to problem dirs."""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.abspath(__file__))


def find_problem_dir(pid: str) -> str | None:
    for cat in os.listdir(ROOT):
        cdir = os.path.join(ROOT, cat)
        if not os.path.isdir(cdir) or cat.startswith('.'):
            continue
        for folder in os.listdir(cdir):
            if folder.startswith(f"{pid}_"):
                return os.path.join(cdir, folder)
    return None


def clean_code(raw: str) -> str:
    lines = []
    for line in raw.splitlines():
        if line.strip() == '```':
            continue
        lines.append(line)
    text = '\n'.join(lines).strip()
    if not text.endswith('\n'):
        text += '\n'
    return text


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, '_gpt_paste.txt')
    text = open(path, encoding='utf-8').read()
    pattern = re.compile(r'===CHECKER:(\d+)===\s*(.*?)\s*===END===', re.DOTALL)
    blocks = pattern.findall(text)
    if not blocks:
        print('No checker blocks found', file=sys.stderr)
        sys.exit(1)

    ok, fail = [], []
    for pid, raw in blocks:
        pdir = find_problem_dir(pid)
        if not pdir:
            fail.append((pid, 'directory not found'))
            continue
        out = os.path.join(pdir, 'checker.cpp')
        code = clean_code(raw)
        open(out, 'w', encoding='utf-8', newline='\n').write(code)
        ok.append((pid, out))
        print(f'Wrote {pid} -> {out}')

    print(f'\n{len(ok)} written, {len(fail)} failed')
    for pid, msg in fail:
        print(f'  FAIL {pid}: {msg}')
    if fail:
        sys.exit(1)


if __name__ == '__main__':
    main()
