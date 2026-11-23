# String

[トップへ戻る](../README.md)

|File Name|Algorithm|Explanation|
|:--:|:--:|:--:|
|[run_length_encoding.hpp](run_length_encoding.hpp)|ランレングス圧縮|連続する同じ値を `{値, 個数}` にまとめる|
|[manacher.hpp](manacher.hpp)|Manacher|各文字を中心とする最長回文の半径を O(N) で求める|
|[compress.hpp](compress.hpp)|座標圧縮|値を大小関係を保ったまま 0, 1, 2, ... に振り直す|

---

## run_length_encoding.hpp

```cpp
vector<pair<T, int>> RLE(const vector<T>& A)
```

- 連続する同じ値をまとめて `{値, 個数}` の列にする。空なら空を返す。
- 計算量: O(N)
- 文字列に使うときは `vector<char>(ALL(S))` に変換して渡す。

```cpp
string S = "aabccc";
auto r = RLE(vector<char>(ALL(S)));  // {a,2} {b,1} {c,3}
```

## manacher.hpp

```cpp
vector<int> manacher(string& str)
```

- `res[i]` = `str[i]` を中心とする**奇数長**の最長回文の半径（`str[i-res[i]+1 .. i+res[i]-1]` が回文、長さは `2*res[i]-1`）。
- 計算量: O(N)
- 偶数長の回文も扱うときは、文字の間にダミー文字を入れる（`"abba"` → `"a$b$b$a"`）。

```cpp
string s = "abaaababa";
auto r = manacher(s);  // 1 2 1 4 1 2 3 2 1
```

## compress.hpp

```cpp
COMPRESS<T> cp(A);       // A の値をまとめて登録（cp.add(x) で1つずつ追加して cp.build() でも可）
cp.get(x);               // x の番号（0 始まり）。x が登録されていなければ x 以上で最小の値の番号
cp[i];                   // 番号 i の元の値
cp.size();               // 異なる値の個数

vector<int> compress(const vector<T>& A)  // A の各要素を番号に置き換えた列を返す
```

- 同じ値には同じ番号がつく。
- 計算量: 構築 O(N log N)、`get` O(log N)

```cpp
vector<ll> A = { 100, -5, 100, 7 };
auto B = compress(A);    // 2 0 2 1
COMPRESS<ll> cp(A);
cp[cp.get(7)];           // 7
```
