# KyoPro-library

競技プログラミングで使用するコンテスト開始前に作成したコードです。
生成AIを用いて作成・整理・改変されたコードを含みます。
Atcoder新ルール対応のために公開されています。

(*C++ library for competitive programming / AtCoder.*)

## Algorithm List

|Algorithm|Contents|
|:--:|:--:|
|[Template](Template)|テンプレート（マクロ・型・入出力）|
|[Math](Math)|数学関連のライブラリ（素数・二項係数・進数変換など）|
|[Search](Search)|探索関連のライブラリ（二分探索）|
|[String](String)|文字列・列関連のライブラリ|
|[Geometry](Geometry)|幾何・座標関連のライブラリ|
|[Graph](Graph)|グラフ・木関連のライブラリ|
|[DataStructure](DataStructure)|データ構造（Union-Find・セグ木・BIT など）|
|[DP](DP)|DP関連のサンプル|
|[Heuristic](Heuristic)|ヒューリスティック（焼きなまし・ビームサーチなど）|
|[Other](Other)|その他（乱数・タイマー・ハッシュ）|

各ディレクトリの `README.md` に、ファイルごとの使い方・計算量・使用例をまとめています。

## 使い方

すべてのファイルは [`Template/template.hpp`](Template/template.hpp)（`ll`・`rep`・`INF` などの定義）を前提にしています。
各 `.hpp` は必要なファイルを `#include "..."` で読み込むので、使いたいものを include するだけで使えます。

```cpp
#include "Template/template.hpp"
#include "Graph/graph.hpp"
#include "DataStructure/union_find.hpp"

int main() {
	int N, M; cin >> N >> M;
	UNIONFIND uf(N);
	...
}
```

### 提出用に1ファイルにまとめる

AtCoder には1ファイルしか提出できないので、[`tools/bundle.py`](tools/bundle.py) で `#include "..."` を展開します。
`<atcoder/all>` などの `<...>` はそのまま残ります。`#pragma once` のファイルは1回だけ展開されます。

```sh
python3 tools/bundle.py main.cpp > submit.cpp
```

### 必要な環境

- C++20 以上（`<=>` を使用）
- [AtCoder Library](https://github.com/atcoder/ac-library)（`modint` を使用）
- Visual Studio (MSVC) でも動くように `i128` / `u128` を切り替えています

## テスト

[`tests/test_all.cpp`](tests/test_all.cpp) に全ライブラリの動作確認、[`tests/test_examples.cpp`](tests/test_examples.cpp) に README の使用例の動作確認があります。

```sh
g++ -std=gnu++20 -I <ac-libraryのパス> tests/test_all.cpp -o test && ./test   # ALL OK と出れば成功
```

## ディレクトリ構成

```
Template/       template.hpp（共通ヘッダ）, main.cpp（提出用ひな形）
Math/  Search/  String/  Geometry/  Graph/  DataStructure/  DP/  Heuristic/  Other/
tools/bundle.py 提出用の1ファイル化スクリプト
tests/          動作確認
disorganized/   整理前の1ファイル版（元のコード）
```
