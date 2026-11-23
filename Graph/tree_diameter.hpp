#pragma once
#include "../Template/template.hpp"
#include "graph.hpp"

struct DIAMETERTREE {
	int a;
	int b;
	ll dist;
};

//木の直径(重み無し)
DIAMETERTREE calc_diameter_of_tree(GRAPH& graph) {

	int a, b;
	int N = graph.size();
	ll d = 0;
	{
		vector<int> dist(N, -1), route(N, -1);

		graph.bfs(0, dist, route);

		a = distance(dist.begin(), max_element(ALL(dist)));
	}
	{
		vector<int> dist(N, -1), route(N, -1);

		graph.bfs(a, dist, route);

		b = distance(dist.begin(), max_element(ALL(dist)));

		d = dist[b];
	}
	return { a,b,d };
}
//木の直径(重み有り)
DIAMETERTREE calc_diameter_of_tree(WGRAPH& graph) {
	int N = graph.size();
	auto farthest = [&](int start) {
		int vertex = start;
		ll max_dist = 0;
		stack<tuple<int, int, ll>> st;
		st.push({ start, -1, 0 });

		while (!st.empty()) {
			auto [v, parent, dist] = st.top();
			st.pop();
			if (dist > max_dist) {
				vertex = v;
				max_dist = dist;
			}
			for (const auto& nx : graph.get_neighbors(v)) {
				int u = nx.first;
				if (u != parent) st.push({ u, v, dist + nx.second });
			}
		}
		return pair<int, ll>{ vertex, max_dist };
	};

	int a = farthest(0).first;
	auto [b, d] = farthest(a);
	return { a, b, d };
}
