# Graph

[トップへ戻る](../README.md)

|File Name|Algorithm|Explanation|
|:--:|:--:|:--:|
|[graph.hpp](graph.hpp)|グラフ本体|隣接リスト + BFS / DFS / 0-1 BFS / ダイクストラ / ワーシャルフロイド / トポロジカルソート / 閉路検出 / 木の中心・重心 / 経路復元|
|[tree_diameter.hpp](tree_diameter.hpp)|木の直径|重みなし・重みありの木の直径と両端点|
|[lca.hpp](lca.hpp)|最小共通祖先 (LCA)|ダブリングで LCA・2点間の距離・k 個上の祖先|

---

## graph.hpp

### 型

|型|辺|中身|用途|
|:--|:--|:--|:--|
|`GRAPH`|重みなし (`int`)|下の2つのどちらか|普段はこれを使う|
|`WGRAPH`|重みあり (`pair<int, ll>` = `{行き先, コスト}`)|同上|同上|
|`GraphAlgo` / `WeightGraphAlgo`|-|`set` で隣接を持つ|多重辺なし・隣接頂点がソート済み・追加削除 O(log)|
|`GraphHeuristic` / `WeightGraphHeuristic`|-|`vector` + 位置表|辺の追加・削除・存在判定が O(1)。メモリ O(N²)|

`GRAPH` / `WGRAPH` は通常 `set` 版。graph.hpp を include する**前**に `#define HEURISTIC_GRAPH` を書くと `vector` 版に切り替わる。

- `vector` 版は N×N の表を持つので N は数千まで。同じ2頂点間の多重辺は扱えない。

### 辺の操作

```cpp
GRAPH g(N);
g.add(a, b);          // 有向辺 a → b
g.add_bidir(a, b);    // 無向辺
g.remove(a, b);       // 削除
g.find(a, b);         // 存在判定
g.get_neighbors(v);   // v の隣接（範囲 for で回す）
g.size();             // 頂点数

WGRAPH wg(N);
wg.add(a, b, c);  wg.add_bidir(a, b, c);  wg.remove(a, b, c);  wg.find(a, b, c);
for (auto [to, cost] : wg.get_neighbors(v)) {}
```

### アルゴリズム

|メンバ|対象|意味|計算量|
|:--|:--|:--|:--|
|`dfs(start, visited)`|両方|`start` から到達できる頂点に `visited[v] = true`（非再帰）|O(N + M)|
|`bfs(start, dist)`|両方|辺の本数での最短距離。**`dist` は `-1` で初期化して渡す**|O(N + M)|
|`bfs(start, dist, route)`|両方|上に加えて `route[v]` = 直前の頂点。**`route` も `-1` で初期化**|O(N + M)|
|`dijkstra(start)`|重みあり|最短距離の `vector<ll>` を返す。到達不能は `INF`|O(M log N)|
|`dijkstra(start, dist, route)`|重みあり|経路復元つき。**`dist` は `INF`、`route` は `-1` で初期化**|O(M log N)|
|`bfs01(start)`|重みあり|重みが 0 か 1 のときの最短距離の `vector<ll>` を返す。到達不能は `INF`|O(N + M)|
|`bfs01(start, dist, route)`|重みあり|経路復元つき。**`dist` は `INF`、`route` は `-1` で初期化**|O(N + M)|
|`warshall_floyd()`|重みあり|全点対最短距離。到達不能は `INF`|O(N³)|
|`topological_sort(lex_min = false)`|有向グラフ|トポロジカル順の頂点列。閉路があれば空。`true` で辞書順最小|O(N + M)（辞書順最小は O(N + M log N)）|
|`dfs_cycle(v, -1, visited)`|無向グラフ|`v` を含む連結成分に閉路があるか（再帰）|O(N + M)|
|`get_tree_centers()`|木|木の中心（1個または2個）|O(N)|
|`get_tree_centroids()`|木|木の重心（1個または2個、再帰）|O(N)|
|`print_debug()`|両方|辺を `cerr` に出力。https://emkjp.github.io/WebTools/dot.html に貼ると図になる|-|

- 負の辺があるときはダイクストラは使えない。
- `bfs01` は重みが 0 と 1 以外の辺があると正しく動かない。
- `dfs_cycle` / `get_tree_centroids` は再帰なので、深さ 10⁵ を超えるとスタックが足りないことがある。

### 経路復元

```cpp
vector<int> restoration(int goal, vector<int>& route)
```

- `bfs` / `dijkstra` で得た `route` から、`goal` → スタートの順に頂点列を返す（**逆順**なので必要なら `reverse`）。

```cpp
WGRAPH g(N);
rep(i, 0, M) { int a, b; ll c; cin >> a >> b >> c; a--, b--; g.add_bidir(a, b, c); }

vector<ll> dist(N, INF);
vector<int> route(N, -1);
g.dijkstra(0, dist, route);
auto path = restoration(N - 1, route);
reverse(ALL(path));  // 0 → N-1
```

```cpp
GRAPH g(N);
vector<int> dist(N, -1);
g.bfs(0, dist);
```

---

## tree_diameter.hpp

```cpp
DIAMETERTREE calc_diameter_of_tree(GRAPH& graph)   // 重みなし（辺の本数）
DIAMETERTREE calc_diameter_of_tree(WGRAPH& graph)  // 重みあり（コストは非負）
struct DIAMETERTREE { int a; int b; ll dist; };    // 両端点と直径
```

- 頂点 0 から最も遠い点 `a` を求め、`a` から最も遠い点 `b` までが直径。
- 計算量: O(N)
- 入力は木（連結・閉路なし）であること。

```cpp
GRAPH g(N);
rep(i, 0, N - 1) { int u, v; cin >> u >> v; u--, v--; g.add_bidir(u, v); }
auto [a, b, d] = calc_diameter_of_tree(g);
cout << d + 1 << el;  // 直径上の頂点数
```

---

## lca.hpp

```cpp
LCA lca(g, root);        // g は GRAPH / WGRAPH（木）、root は根（省略時 0）
lca.get(u, v);           // u と v の最小共通祖先
lca.dist(u, v);          // u-v 間の辺の本数
lca.wdist(u, v);         // u-v 間の重みの和（GRAPH なら dist と同じ）
lca.ancestor(v, k);      // v から k 個上の祖先（根を越えたら -1）
lca.depth[v];            // 根からの深さ（辺の本数）
lca.parent[v];           // 親（根は -1）
```

- [ダブリング](../DataStructure/doubling.hpp) で親の表を作る。
- 計算量: 前処理 O(N log N)、各クエリ O(log N)
- 入力は木（連結・閉路なし）であること。辺は `add_bidir` で張る。BFS で根から辿るので深い木でもスタックは溢れない。

```cpp
WGRAPH g(N);
rep(i, 0, N - 1) { int u, v; ll c; cin >> u >> v >> c; u--, v--; g.add_bidir(u, v, c); }
LCA lca(g, 0);
cout << lca.wdist(a, b) << el;  // a-b 間の距離
```
