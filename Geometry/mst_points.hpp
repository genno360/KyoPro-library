#pragma once
#include "../Template/template.hpp"

template<class T>
vector<pii> mst_points(const vector<pair<T, T>>& p) {	//最小全域木 
	int N = p.size();
	const ll INF = (1LL << 62);

	vector<ll> dist(N, INF);
	vector<int> parent(N, -1);
	vector<bool> used(N, false);

	dist[0] = 0;

	for (int it = 0; it < N; it++) {
		int v = -1;
		for (int i = 0; i < N; i++) {
			if (!used[i] && (v == -1 || dist[i] < dist[v])) v = i;
		}
		used[v] = true;

		for (int u = 0; u < N; u++) {
			if (used[u]) continue;
			ll dx = p[v].first - p[u].first;
			ll dy = p[v].second - p[u].second;
			ll w = dx * dx + dy * dy;
			if (w < dist[u]) {
				dist[u] = w;
				parent[u] = v;
			}
		}
	}

	vector<pii> res;
	for (int i = 1; i < N; i++) {
		res.push_back({ parent[i], i });
	}
	return res;
}
