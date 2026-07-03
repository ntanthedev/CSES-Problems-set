#!/usr/bin/env python3
"""Extract GPT checker paste from agent transcript jsonl."""
import json
import re
import sys

TRANSCRIPT = r"C:\Users\nhatt\.cursor\projects\d-ntancode-Code-cses-crawler\agent-transcripts\4ac45f95-a23d-4fa8-9e50-865fdb37b975\4ac45f95-a23d-4fa8-9e50-865fdb37b975.jsonl"
OUT = r"d:\ntancode\Code\cses-crawler\_gpt_paste.txt"

def main():
    with open(TRANSCRIPT, encoding='utf-8') as f:
        for line in f:
            obj = json.loads(line)
            if obj.get('role') != 'user':
                continue
            for part in obj.get('message', {}).get('content', []):
                if part.get('type') != 'text':
                    continue
                text = part.get('text', '')
                if '===CHECKER:2423===' not in text:
                    continue
                m = re.search(r'(===CHECKER:\d+===.*?===END===)', text, re.DOTALL)
                if not m:
                    # grab from first marker to last END
                    start = text.find('===CHECKER:2423===')
                    end = text.rfind('===END===')
                    if start == -1 or end == -1:
                        print('markers not found', file=sys.stderr)
                        sys.exit(1)
                    blob = text[start:end + len('===END===')]
                else:
                    # get all blocks
                    blocks = re.findall(r'===CHECKER:\d+===.*?===END===', text, re.DOTALL)
                    blob = '\n'.join(blocks)
                with open(OUT, 'w', encoding='utf-8', newline='\n') as out:
                    out.write(blob)
                    if not blob.endswith('\n'):
                        out.write('\n')
                n = len(re.findall(r'===CHECKER:\d+===', blob))
                print(f'Extracted {n} blocks -> {OUT}')
                return
    print('No matching user message found', file=sys.stderr)
    sys.exit(1)

if __name__ == '__main__':
    main()
