#!/usr/bin/env python3
"""#include "..." で読み込んだライブラリを展開して、提出用の1ファイルにまとめる。

使い方:
    python3 tools/bundle.py main.cpp > submit.cpp

- "..." で書いたローカルの include だけ展開する (<atcoder/all> などはそのまま残す)
- #pragma once のファイルは1回だけ展開する
- 探索順: そのファイルのあるディレクトリ → リポジトリのルート
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INCLUDE = re.compile(r'^\s*#\s*include\s*"([^"]+)"')
PRAGMA_ONCE = re.compile(r'^\s*#\s*pragma\s+once\b')

done = set()


def resolve(name, base_dir):
    for d in (base_dir, ROOT):
        p = os.path.normpath(os.path.join(d, name))
        if os.path.isfile(p):
            return p
    raise FileNotFoundError(f'include "{name}" が見つかりません ({base_dir} から)')


def expand(path, out):
    path = os.path.realpath(path)
    with open(path, encoding='utf-8-sig') as f:
        lines = f.read().split('\n')
    if any(PRAGMA_ONCE.match(l) for l in lines):
        if path in done:
            return
        done.add(path)
    for line in lines:
        if PRAGMA_ONCE.match(line):
            continue
        m = INCLUDE.match(line)
        if m:
            expand(resolve(m.group(1), os.path.dirname(path)), out)
        else:
            out.append(line)


def main():
    if len(sys.argv) != 2:
        print(__doc__, file=sys.stderr)
        sys.exit(1)
    out = []
    expand(sys.argv[1], out)
    text = '\n'.join(out)
    text = re.sub(r'\n{3,}', '\n\n', text)  # 連続する空行を詰める
    sys.stdout.write(text.strip('\n') + '\n')


if __name__ == '__main__':
    main()
