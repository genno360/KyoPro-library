# DataStructure

[トップへ戻る](../README.md)

|File Name|Algorithm|Explanation|
|:--:|:--:|:--:|
|[union_find.hpp](union_find.hpp)|Union-Find|集合の併合と同じ集合かの判定、集合サイズ|
|[segment_tree.hpp](segment_tree.hpp)|セグメントツリー|一点更新・区間取得（和 / 最大 / 最小 / 自作の演算）|
|[fenwick_tree.hpp](fenwick_tree.hpp)|フェニック木 (BIT)|一点加算・区間和|
|[interval_set.hpp](interval_set.hpp)|区間をsetで管理|`[l, r)` 区間の追加・削除・値の塗りつぶし・mex|
|[doubling.hpp](doubling.hpp)|ダブリング|「K 回移動した先」を O(log K) で求める|
|[persistent_stack.hpp](persistent_stack.hpp)|永続スタック|過去の状態を残したまま push / pop。行動列の復元に使う|
|[indexed_set.hpp](indexed_set.hpp)|添字つき集合|`0..N-1` の整数の追加・削除・存在判定が O(1)、ランダムに1つ選べる|

---

## union_find.hpp

```cpp
UNIONFIND uf(N);
uf.merge(a, b);      // a と b の集合を併合
uf.connected(a, b);  // 同じ集合か
uf.find(a);          // 代表元
uf.size(a);          // a を含む集合の要素数
```

- 経路圧縮 + union by size。各操作ほぼ O(1)（O(α(N))）。
- 参考: https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/union-find

## segment_tree.hpp

```cpp
SEGMENTTREE<ll, SumOp> seg;
seg.init(N);           // 長さ N、全要素を単位元で初期化
seg.update(pos, x);    // pos 番目を x に**置き換える**（加算ではない）
seg.query(l, r);       // [l, r) の演算結果（l == r なら単位元）
```

- 計算量: `init` O(N)、`update` / `query` O(log N)
- 用意されている演算: `SumOp`（和、単位元 0）、`MaxOp`（最大、単位元 `LLONG_MIN`）、`MinOp`（最小、単位元 `LLONG_MAX`）
- 加算したいときは `seg.update(i, seg.query(i, i + 1) + x)`。

自作の演算は `operator()` と `id()`（単位元）を持つ構造体を作る:

```cpp
struct XorOp {
	ll operator()(ll a, ll b) const { return a ^ b; }
	ll id() const { return 0; }
};
SEGMENTTREE<ll, XorOp> seg; seg.init(N);
```

## fenwick_tree.hpp

```cpp
FenwickTree fw(N);
fw.add(idx, val);      // A[idx] += val
fw.sum(l, r);          // A[l] + ... + A[r]   ※ r を**含む**閉区間
fw.sum_prefix(idx);    // A[0] + ... + A[idx] ※ idx を含む
```

- 0-indexed。計算量: 各操作 O(log N)
- `sum` は**閉区間 `[l, r]`** なので、セグ木（半開区間）と混同しないよう注意。

```cpp
// 転倒数
FenwickTree fw(N);
ll inv = 0;
rep(i, 0, N) { inv += i - fw.sum_prefix(A[i]); fw.add(A[i], 1); }  // A は 0..N-1 の順列
```

## interval_set.hpp

`[l, r)` の区間を `set` で管理する。各区間は値 `val` を持ち、隣り合う同じ値の区間は自動でつながる。
出典: drken1215 (https://github.com/drken1215/algorithm, CC0 1.0)

```cpp
IntervalSet<ll> S;                 // 値を使わない（区間の和集合だけ）
IntervalSet<ll, ll> S(identity);   // 値つき。どの区間にも含まれない点の値は identity
```

|メンバ|意味|
|:--|:--|
|`insert(l, r)`|`[l, r)` を追加（重なり・隣接はつながる）|
|`erase(l, r)`|`[l, r)` を削除（区間が分割されることもある）|
|`update(l, r, val)`|`[l, r)` を値 `val` で塗りつぶす|
|`covered(p)` / `covered(l, r)`|点 `p` / 区間 `[l, r)` が1つの区間に含まれるか|
|`same(p, q)`|`p` と `q` が同じ区間に含まれるか|
|`get(p)`|`p` を含む区間のイテレータ（なければ `end()`）。`it->l`, `it->r`, `it->val`|
|`lower_bound(p)`|`p` を含む区間、なければ `p` より右にある最初の区間|
|`get_val(p)` / `S[p]`|`p` を含む区間の値（なければ identity）|
|`get_mex(p = 0)`|`p` 以上で、どの区間にも含まれない最小の値|
|`for (auto [l, r, val] : S)`|区間を左から順に列挙|

- 計算量: 各操作 ならし O(log N)
- `insert` / `erase` / `update` には `add(l, r, val)` と `del(l, r, val)` のコールバックを渡せる。区間が増減するたびに呼ばれるので、「覆われている長さの合計」などを管理できる。

```cpp
IntervalSet<ll> S;
ll covered_len = 0;
auto add = [&](ll l, ll r, ll) { covered_len += r - l; };
auto del = [&](ll l, ll r, ll) { covered_len -= r - l; };
S.insert(0, 3, add, del);
S.insert(2, 5, add, del);   // [0, 5) にまとまる
S.erase(1, 2, add, del);    // [0, 1) と [2, 5)
cout << covered_len;        // 4
```

## doubling.hpp

```cpp
DOUBLING db(N, a, max_step);  // a[i] = 頂点 i から1回移動した先
int db.query(pos, step);      // pos から step 回移動した先
```

- 計算量: 構築 O(N log max_step)、クエリ O(log step)、メモリ O(N log max_step)
- `step <= max_step` で使う。

```cpp
// 10^18 回テレポートした先
DOUBLING db(N, A, 1000000000000000000LL);
cout << db.query(0, K) + 1;
```

## persistent_stack.hpp

```cpp
PersistentStack<T> s;
auto s2 = s.push(x);   // s は変わらない。新しいスタックを返す
auto s3 = s2.pop();
s2.top(); s2.empty();
vector<T> v = s2.to_vector();  // 底 → 上 の順
```

- 各操作 O(1)、`to_vector` O(長さ)。途中までの履歴を共有するのでメモリ効率がよい。
- ビームサーチで各状態の「ここまでの行動列」を持つのに使う。
- 参考: https://jetbead.github.io/AtCoderHeuristicContestMemo/Library/persistent_stack.html

## indexed_set.hpp

```cpp
IndexedSet st(N);      // 0..N-1 の整数を入れる集合
st.add(a);             // 追加（既にあれば false）
st.remove(a);          // 削除（なければ false）
st.contains(a);
st.size();
st[i];                 // i 番目の要素（順序は追加・削除で変わる）
st.position(a);        // a の位置（なければ -1）
```

- すべて O(1)。削除は末尾と入れ替えるので順序は保たれない。
- ランダムに1つ選ぶ: `st[random_int_range(0, st.size())]`（ヒューリスティックで便利）。
