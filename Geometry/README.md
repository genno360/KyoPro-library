# Geometry

[トップへ戻る](../README.md)

|File Name|Algorithm|Explanation|
|:--:|:--:|:--:|
|[distance.hpp](distance.hpp)|距離・範囲判定|ユークリッド距離・距離の2乗・マンハッタン距離・グリッド範囲内判定|
|[line.hpp](line.hpp)|直線|`ax + by + c = 0` を整数で一意に表現。平行・垂直・同一判定、垂直二等分線|
|[delaunay.hpp](delaunay.hpp)|ドロネー三角形分割|O(N log N) で三角形分割。ユークリッド MST の候補辺を得る|
|[mst_points.hpp](mst_points.hpp)|点の最小全域木|完全グラフ上のプリム法 O(N²)|

---

## distance.hpp

|関数|意味|
|:--|:--|
|`double euclid(T a, T b)`|`pair` の2点のユークリッド距離|
|`double euclid(T ax, T ay, T bx, T by)`|座標4つ版|
|`T getDistanceSq(T x1, T y1, T x2, T y2)`|距離の2乗（誤差なしで比較したいとき）|
|`ll manhattan(T ax, T ay, T bx, T by)`|マンハッタン距離|
|`bool isInArea(int a, int b, int H, int W)`|`0 <= a < H` かつ `0 <= b < W`|

```cpp
euclid(pll{0, 0}, pll{3, 4});        // 5.0
getDistanceSq<ll>(0, 0, 3, 4);       // 25
rep(d, 0, 4) {
	int nx = x + DX[d], ny = y + DY[d];
	if (!isInArea(nx, ny, H, W)) continue;
}
```

## line.hpp

```cpp
LINE l(a, b, c);         // ax + by + c = 0
LINE l(px, py, qx, qy);  // 2点 (px,py), (qx,qy) を通る直線
LINE get_canonical(px, py, qx, qy);  // 2点の垂直二等分線
```

- 係数を最大公約数で割り、`a > 0`（`a == 0` なら `b > 0`）にそろえるので、**同じ直線は同じ (a, b, c)** になる。`set<LINE>` や `map<LINE, int>` で直線の種類を数えられる。
- 整数座標専用。同じ2点を渡すと `a = b = c = 0` になり0除算になるので注意。

|メンバ|意味|
|:--|:--|
|`contains(x, y)`|点が直線上にあるか|
|`eval(x, y)`|`ax + by + c`（符号で直線のどちら側かわかる）|
|`is_parallel(l)` / `is_vertical(l)` / `is_same(l)`|平行 / 垂直 / 同一|
|`direction()` / `normal()`|方向ベクトル `(-b, a)` / 法線ベクトル `(a, b)`|

```cpp
// N 点から2点を選んで引ける直線の種類数
set<LINE> st;
rep(i, 0, N) rep(j, i + 1, N) st.insert(LINE(X[i], Y[i], X[j], Y[j]));
cout << st.size();
```

## delaunay.hpp

```cpp
vector<pll> P(N); cin >> P;
DELAUNAY dt(P);
for (auto [a, b, c] : dt.triangles) {}  // 三角形（元の添字、反時計回り）
for (auto [u, v] : dt.edges) {}         // 辺（u < v）
```

- 分割統治 + quad-edge による O(N log N)。参考: KACTL FastDelaunay (CC0)
- **ユークリッド最小全域木はこの辺の中に含まれる**ので、`edges` を重み（距離の2乗）でソートして Kruskal すれば O(N log N)。
- 整数座標のみ。判定は `__int128` で厳密。`|x|, |y| <= 5e8` 程度まで。
- 重複点は最初に現れた添字にまとめる（重複した点は三角形・辺に現れない）。
- 全点が一直線上なら `triangles` は空で、`edges` は直線上で隣り合う点の組。
- 4点以上が同一円周上にあるときは分割が一意でないが、どれか1つを返す。

```cpp
// ユークリッド MST
DELAUNAY dt(P);
vector<tuple<ll, int, int>> es;
for (auto [u, v] : dt.edges) es.push_back({getDistanceSq(P[u].first, P[u].second, P[v].first, P[v].second), u, v});
sort(ALL(es));
UNIONFIND uf(N);
for (auto [w, u, v] : es) if (!uf.connected(u, v)) { uf.merge(u, v); /* 採用 */ }
```

## mst_points.hpp

```cpp
vector<pii> mst_points(const vector<pair<T, T>>& p)
```

- 点集合のユークリッド最小全域木の辺 `{親, 子}` を `N-1` 本返す（完全グラフ上のプリム法）。
- 計算量: O(N²)。N が数千までなら手軽。大きいときは `delaunay.hpp` を使う。
- 空の入力には対応していない（`N >= 1`）。
