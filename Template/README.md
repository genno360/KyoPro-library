# Template

[トップへ戻る](../README.md)

|File Name|Algorithm|Explanation|
|:--:|:--:|:--:|
|[template.hpp](template.hpp)|共通テンプレート|型・マクロ・入出力演算子など。全ライブラリがこれを前提にする|
|[main.cpp](main.cpp)|提出用ひな形|ライブラリを include して `tools/bundle.py` で1ファイル化する|

---

## template.hpp

`#include <bits/stdc++.h>` と `#include <atcoder/all>` を読み込み、`using namespace std; using namespace atcoder;` 済み。

### 型

|名前|中身|
|:--|:--|
|`ll`|`long long`|
|`pll` / `pii`|`pair<ll, ll>` / `pair<int, int>`|
|`i128` / `u128`|128bit 整数（GCC/Clang は `__int128`、MSVC は `_Signed128`）|
|`mint`|`modint1000000007`（998244353 にしたいときはコメントを切り替える）|

### マクロ

|マクロ|意味|
|:--|:--|
|`rep(i, P, n)`|`for (ll i = P; i < n; i++)`|
|`REP(i, P, n)`|`for (ll i = P; i <= n; i++)`（n を含む）|
|`repm(i, P, n, m)`|`i += m` ずつ進む `rep`|
|`rrep(i, P, n)`|`for (ll i = P; i >= n; i--)`（逆順）|
|`Yes` / `No`|`Yes` / `No` を改行付きで出力|
|`debug(x)`|`cerr` に `x = 値` を出力|
|`el`|`'\n'`|
|`SETPREC(X)`|小数点以下 X 桁で出力（`cout << SETPREC(10) << x`）|
|`ALL(x)`|`(x).begin(), (x).end()`|
|`DEF_CMP(T)`|構造体に書くと全メンバで比較できるようになる（sort や map の key に使える）|

```cpp
struct P { int x, y; DEF_CMP(P) };
set<P> st;  // そのまま使える
```

### 関数・定数

|名前|意味|
|:--|:--|
|`chmax(a, b)` / `chmin(a, b)`|`a` を更新し、更新したら `true`|
|`YN(ok)`|`ok` なら `Yes`、そうでなければ `No` を出力|
|`ABC` / `abc`|大文字 / 小文字のアルファベット文字列|
|`DX[4]` / `DY[4]`|上下左右の移動量（`{-1,1,0,0}` / `{0,0,-1,1}`）|
|`INF`|`LLONG_MAX / 4`（足し算1回ではオーバーフローしない）|

### 入出力

- `cin >> vec;` で `vector` を要素数ぶん読み込める（先にサイズを決めておく）。`cin >> p;` で `pair` も読める。
- `cout << vec;` / `set` / `multiset` は空白区切り、`map` / `multimap` は `key:value` の空白区切りで出力。`pair` は `first second`。
- `ios::sync_with_stdio(0); cin.tie(0);` は自動で実行される。

```cpp
int N; cin >> N;
vector<ll> A(N); cin >> A;
cout << A << el;  // 1 2 3
```

### デバッグ用 multiset

`_DEBUG` が定義されている（Visual Studio のデバッグビルド）とき、`multiset::erase(値)` を呼ぶと警告を出して止まる。
値で erase すると同じ値がすべて消えるため。1個だけ消すときは `st.erase(st.find(x))` を使う。

---

## main.cpp

```cpp
#include "template.hpp"
#include "../Graph/graph.hpp"   // 使うものを追加

int main() { ... }
```

```sh
python3 tools/bundle.py Template/main.cpp > submit.cpp
```
