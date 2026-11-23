#pragma once
#include "../Template/template.hpp"
#include "../DataStructure/doubling.hpp"
#include "graph.hpp"

//最小共通祖先 LCA (ダブリング)
/* 使用例
	GRAPH g(N); (または WGRAPH) に木の辺を add_bidir で張る
	LCA lca(g, root);
	lca.get(u, v);			// u と v の最小共通祖先
	lca.dist(u, v);			// 辺の本数
	lca.wdist(u, v);		// 重みの和 (GRAPH なら dist と同じ)
	lca.ancestor(v, k);		// v から k 個上の祖先 (根を越えたら -1)
	lca.depth[v], lca.parent[v]	// 深さ、親 (根の親は -1)
	前処理 O(N log N)、クエリ O(log N)
*/
struct LCA {
	int N, LOG;
	vector<int> depth, parent;
	vector<ll> wdepth;
	vector<vector<int>> up;	// up[k][v] : v から 2^k 個上 (根を越えたら根)

	template<typename G>
	LCA(const G& g, int root = 0) : N(g.size()), depth(N, -1), parent(N, -1), wdepth(N, 0) {
		vector<int> q = { root };
		depth[root] = 0;
		for (size_t head = 0; head < q.size(); head++) {
			int v = q[head];
			for (const auto& nx : g.get_neighbors(v)) {
				int u = to_v(nx);
				if (depth[u] != -1) continue;
				depth[u] = depth[v] + 1;
				wdepth[u] = wdepth[v] + cost(nx);
				parent[u] = v;
				q.push_back(u);
			}
		}
		vector<int> a(N);
		rep(v, 0, N) a[v] = parent[v] == -1 ? v : parent[v];
		DOUBLING db(N, a, N);
		up = std::move(db.table);
		LOG = up.size();
	}

	int ancestor(int v, int k) const {
		if (k > depth[v]) return -1;
		for (int i = 0; k > 0; i++, k >>= 1) if (k & 1) v = up[i][v];
		return v;
	}
	int get(int u, int v) const {
		if (depth[u] < depth[v]) swap(u, v);
		u = ancestor(u, depth[u] - depth[v]);
		if (u == v) return u;
		for (int k = LOG - 1; k >= 0; k--) {
			if (up[k][u] != up[k][v]) u = up[k][u], v = up[k][v];
		}
		return up[0][u];
	}
	int dist(int u, int v) const { return depth[u] + depth[v] - 2 * depth[get(u, v)]; }
	ll wdist(int u, int v) const { return wdepth[u] + wdepth[v] - 2 * wdepth[get(u, v)]; }

private:
	static int to_v(int to) { return to; }
	static int to_v(const pair<int, ll>& p) { return p.first; }
	static ll cost(int) { return 1; }
	static ll cost(const pair<int, ll>& p) { return p.second; }
};
