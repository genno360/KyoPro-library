#pragma once
#include "../Template/template.hpp"

// ==========================================
// 1. ストレージポリシー (コンテナ管理)
// ==========================================

// A. Setベース (Algo)
template <typename Edge>
class SetStorage {
protected:
	int N;
	vector<set<Edge>> concat;

public:
	SetStorage() = default;
	explicit SetStorage(int n) : N(n), concat(n) {}

	const auto& get_neighbors(int v) const { return concat[v]; }
	auto& get_neighbors(int v) { return concat[v]; }
	int size() const { return N; }

	void add_edge_raw(int a, const Edge& e) { concat[a].insert(e); }
	void remove_edge_raw(int a, const Edge& e) { concat[a].erase(e); }
	bool find_edge_raw(int a, const Edge& e) const { return concat[a].find(e) != concat[a].end(); }

	void print_dot(ostream& os) const {
		for (int i = 0; i < N; ++i) {
			for (const auto& c : concat[i]) {
				os << i << " " << c << el;
			}
		}
	}
};

// B. Vector + Posベース (Heuristic / O(1)削除)
template <typename Edge>
class VectorStorage {
protected:
	int N;
	vector<vector<Edge>> concat;
	vector<vector<int>> pos; // 高速削除用インデックスマップ

	// Edgeから宛先頂点(to)を取得するヘルパー (int または pairに対応)
	static int get_to(int v) { return v; }
	static int get_to(const pair<int, ll>& p) { return p.first; }

public:
	VectorStorage() = default;
	explicit VectorStorage(int n) : N(n), concat(n), pos(n, vector<int>(n, -1)) {}

	const auto& get_neighbors(int v) const { return concat[v]; }
	auto& get_neighbors(int v) { return concat[v]; }
	int size() const { return N; }

	void add_edge_raw(int a, const Edge& e) {
		int target = get_to(e);
		pos[a][target] = concat[a].size();
		concat[a].push_back(e);
	}

	void remove_edge_raw(int a, const Edge& e) {
		int target = get_to(e);
		int i = pos[a][target];
		if (i == -1) return;

		auto last = concat[a].back();
		concat[a][i] = last;
		pos[a][get_to(last)] = i;

		concat[a].pop_back();
		pos[a][target] = -1;
	}

	bool find_edge_raw(int a, const Edge& e) const {
		return pos[a][get_to(e)] != -1;
	}

	void update_weight(int u, int v, ll w) {
		// 重み付きの場合の更新用（必要に応じて）
		// テンプレートの制約で重み付きのみ有効にするか、pairの場合のみ定義
	}

	void print_dot(ostream& os) const {
		for (int i = 0; i < N; ++i) {
			for (const auto& c : concat[i]) {
				os << i << " " << c << el;
			}
		}
	}
};


// ==========================================
// 2. グラフアルゴリズム本体 (共通テンプレート)
// ==========================================
template <typename Storage, typename Edge>
class GraphTemplate : public Storage {
public:
	using Storage::Storage;

	// 辺の操作ラッパー
	void add(int a, int b) { this->add_edge_raw(a, b); }
	void add(int a, int b, ll c) { this->add_edge_raw(a, { b, c }); }

	void add_bidir(int a, int b) { add(a, b); add(b, a); }
	void add_bidir(int a, int b, ll c) { add(a, b, c); add(b, a, c); }

	void remove(int a, int b) { this->remove_edge_raw(a, b); }
	void remove(int a, int b, ll c) { this->remove_edge_raw(a, { b, c }); }

	bool find(int a, int b) const { return this->find_edge_raw(a, b); }
	bool find(int a, int b, ll c) const { return this->find_edge_raw(a, { b, c }); }

	// --- 汎用 DFS ---
	void dfs(int start, vector<bool>& visited) const {
		stack<int> st;
		st.push(start);
		while (!st.empty()) {
			int v = st.top();
			st.pop();
			if (visited[v]) continue;
			visited[v] = true;
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (!visited[u]) {
					st.push(u);
				}
			}
		}
	}

	// --- 汎用 BFS ---
	void bfs(int start, vector<int>& dist, vector<int>& route) const {
		vector<int> q;
		q.reserve(this->size());
		int head = 0;

		q.push_back(start);
		dist[start] = 0;

		while (head < (int)q.size()) {
			int v = q[head++];
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (dist[u] == -1) {
					dist[u] = dist[v] + 1;
					route[u] = v;
					q.push_back(u);
				}
			}
		}
	}

	void bfs(int start, vector<int>& dist) const {
		vector<int> q;
		q.reserve(this->size());
		int head = 0;

		q.push_back(start);
		dist[start] = 0;

		while (head < (int)q.size()) {
			int v = q[head++];
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (dist[u] == -1) {
					dist[u] = dist[v] + 1;
					q.push_back(u);
				}
			}
		}
	}

	// --- 木の中心 (Tree Center) ---
	vector<int> get_tree_centers() const {
		int N = this->size();
		if (N == 0) return {};

		vector<int> dist1(N, -1), route1(N, -1);
		bfs(0, dist1, route1);

		int u = 0;
		for (int i = 0; i < N; ++i) {
			if (dist1[i] > dist1[u]) u = i;
		}

		vector<int> dist2(N, -1), route2(N, -1);
		bfs(u, dist2, route2);

		int v = u;
		for (int i = 0; i < N; ++i) {
			if (dist2[i] > dist2[v]) v = i;
		}

		vector<int> path;
		for (int cur = v; cur != -1; cur = route2[cur]) {
			path.push_back(cur);
		}

		int len = path.size();
		if (len % 2 == 1) return { path[len / 2] };
		return { path[len / 2 - 1], path[len / 2] };
	}

	// --- 木の重心 (Tree Centroid) ---
	vector<int> get_tree_centroids() const {
		int N = this->size();
		if (N == 0) return {};

		vector<int> centroids;
		vector<int> subtree_size(N, 0);

		auto dfs_size = [&](auto self, int v, int p) -> void {
			subtree_size[v] = 1;
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (u != p) {
					self(self, u, v);
					subtree_size[v] += subtree_size[u];
				}
			}
		};

		dfs_size(dfs_size, 0, -1);

		auto dfs_centroid = [&](auto self, int v, int p) -> void {
			bool is_centroid = true;
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (u != p) {
					if (subtree_size[u] > N / 2) is_centroid = false;
					self(self, u, v);
				}
			}
			if (N - subtree_size[v] > N / 2) is_centroid = false;
			if (is_centroid) centroids.push_back(v);
		};

		dfs_centroid(dfs_centroid, 0, -1);
		return centroids;
	}

	// --- 閉路検出 ---
	bool dfs_cycle(int v, int parent, vector<bool>& visited) const {
		visited[v] = true;
		for (const auto& nx : this->get_neighbors(v)) {
			int u = get_to_v(nx);
			if (!visited[u]) {
				if (dfs_cycle(u, v, visited)) return true;
			}
			else if (u != parent) {
				return true;
			}
		}
		return false;
	}

	// --- ダイクストラ法 (重み付き用) ---
	vector<ll> dijkstra(int start) const {
		int N = this->size();
		vector<ll> dist(N, INF);
		dist[start] = 0;

		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
		pq.push({ 0, start });

		while (!pq.empty()) {
			auto [cd, v] = pq.top(); pq.pop();
			if (cd > dist[v]) continue;

			for (const auto& nx : this->get_neighbors(v)) {
				int to = nx.first;
				ll cost = nx.second;
				if (dist[to] > cd + cost) {
					dist[to] = cd + cost;
					pq.push({ dist[to], to });
				}
			}
		}
		return dist;
	}

	void dijkstra(int start, vector<ll>& dist, vector<int>& route) const {
		int N = this->size();
		dist[start] = 0;

		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
		pq.push({ 0, start });

		while (!pq.empty()) {
			auto [cd, v] = pq.top(); pq.pop();
			if (cd > dist[v]) continue;

			for (const auto& nx : this->get_neighbors(v)) {
				int to = nx.first;
				ll cost = nx.second;
				if (dist[to] > cd + cost) {
					dist[to] = cd + cost;
					route[to] = v;
					pq.push({ dist[to], to });
				}
			}
		}
	}

	// --- ワーシャルフロイド ---
	vector<vector<ll>> warshall_floyd() const {
		int N = this->size();
		vector<vector<ll>> dist(N, vector<ll>(N, INF));

		for (int i = 0; i < N; i++) dist[i][i] = 0;
		for (int i = 0; i < N; i++) {
			for (const auto& nx : this->get_neighbors(i)) {
				dist[i][nx.first] = min(dist[i][nx.first], (ll)nx.second);
			}
		}

		for (int k = 0; k < N; k++) {
			for (int i = 0; i < N; i++) {
				if (dist[i][k] == INF) continue;
				for (int j = 0; j < N; j++) {
					if (dist[k][j] == INF) continue;
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
		return dist;
	}

	// --- トポロジカルソート (有向グラフ) ---
	// 閉路があれば空の配列を返す
	// lex_min = true で辞書順最小 (O(M log N))
	vector<int> topological_sort(bool lex_min = false) const {
		int N = this->size();
		vector<int> indeg(N, 0);
		for (int v = 0; v < N; v++) {
			for (const auto& nx : this->get_neighbors(v)) indeg[get_to_v(nx)]++;
		}
		vector<int> res;
		res.reserve(N);
		priority_queue<int, vector<int>, greater<int>> pq;
		vector<int> q;
		for (int v = 0; v < N; v++) if (indeg[v] == 0) lex_min ? pq.push(v) : q.push_back(v);
		size_t head = 0;
		while (lex_min ? !pq.empty() : head < q.size()) {
			int v;
			if (lex_min) { v = pq.top(); pq.pop(); }
			else v = q[head++];
			res.push_back(v);
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (--indeg[u] == 0) lex_min ? pq.push(u) : q.push_back(u);
			}
		}
		if ((int)res.size() != N) return {};
		return res;
	}

	// --- 0-1 BFS (重み付き用、重みは 0 か 1) ---
	// 到達できない頂点は INF
	vector<ll> bfs01(int start) const {
		vector<ll> dist(this->size(), INF);
		vector<int> route(this->size(), -1);
		bfs01(start, dist, route);
		return dist;
	}

	void bfs01(int start, vector<ll>& dist, vector<int>& route) const {
		deque<int> dq;
		dist[start] = 0;
		dq.push_back(start);
		while (!dq.empty()) {
			int v = dq.front(); dq.pop_front();
			for (const auto& nx : this->get_neighbors(v)) {
				int to = nx.first;
				ll cost = nx.second;
				if (dist[to] > dist[v] + cost) {
					dist[to] = dist[v] + cost;
					route[to] = v;
					if (cost == 0) dq.push_front(to);
					else dq.push_back(to);
				}
			}
		}
	}

	void print_debug() const {
		cerr << "https://emkjp.github.io/WebTools/dot.html" << el;
		this->print_dot(cerr);
	}

private:
	// エッジ型から接続先頂点を取り出すヘルパー
	static int get_to_v(int to) { return to; }
	static int get_to_v(const pair<int, ll>& p) { return p.first; }
};


// ==========================================
// 3. エイリアス定義 (切り替え部分)
// ==========================================
using GraphAlgo = GraphTemplate<SetStorage<int>, int>;
using WeightGraphAlgo = GraphTemplate<SetStorage<pair<int, ll>>, pair<int, ll>>;
using GraphHeuristic = GraphTemplate<VectorStorage<int>, int>;
using WeightGraphHeuristic = GraphTemplate<VectorStorage<pair<int, ll>>, pair<int, ll>>;

#ifdef HEURISTIC_GRAPH
namespace graph_impl {
	using Graph = GraphHeuristic;
	using WGraph = WeightGraphHeuristic;
}
#else
namespace graph_impl {
	using Graph = GraphAlgo;
	using WGraph = WeightGraphAlgo;
}
#endif
using GRAPH = graph_impl::Graph;
using WGRAPH = graph_impl::WGraph;

//経路復元
vector<int> restoration(int start, vector<int>& route) {
	vector<int> path;

	path.push_back(start);

	while (1) {
		if (route[path.back()] == -1)break;
		path.push_back(route[path.back()]);
	}
	return path;
}
