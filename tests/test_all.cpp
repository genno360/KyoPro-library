// 全ライブラリの動作確認 (assert)
// g++ -std=gnu++20 -I <ac-libraryのパス> tests/test_all.cpp && ./a.out
#include "../Template/template.hpp"
#include "../Other/random.hpp"
#include "../Other/splitmix64.hpp"
#include "../Other/timer.hpp"
#include "../Math/pow_int.hpp"
#include "../Math/cumulative_sum.hpp"
#include "../Math/cumulative_sum_2d.hpp"
#include "../Math/prime.hpp"
#include "../Math/gcd.hpp"
#include "../Math/base_conversion.hpp"
#include "../Math/binomial_table.hpp"
#include "../Math/combination.hpp"
#include "../Search/binary_search.hpp"
#include "../String/run_length_encoding.hpp"
#include "../String/manacher.hpp"
#include "../String/compress.hpp"
#include "../Geometry/distance.hpp"
#include "../Geometry/line.hpp"
#include "../Geometry/delaunay.hpp"
#include "../Geometry/mst_points.hpp"
#include "../Graph/graph.hpp"
#include "../Graph/tree_diameter.hpp"
#include "../Graph/lca.hpp"
#include "../DataStructure/union_find.hpp"
#include "../DataStructure/segment_tree.hpp"
#include "../DataStructure/fenwick_tree.hpp"
#include "../DataStructure/interval_set.hpp"
#include "../DataStructure/doubling.hpp"
#include "../DataStructure/persistent_stack.hpp"
#include "../DataStructure/indexed_set.hpp"
#include "../Heuristic/kmeans.hpp"
#include "../Heuristic/simple_connection_judge.hpp"
#include "../Heuristic/bit_field.hpp"
#include "../Heuristic/annealing.hpp"
#include "../Heuristic/beam_search.hpp"

#define CHECK(x) do { if (!(x)) { cerr << "FAILED: " #x " (line " << __LINE__ << ")\n"; exit(1); } } while (0)

int main() {
	// --- Math ---
	CHECK(pow_int<ll>(3, 13) == 1594323);
	CHECK(pow_int<mint>(2, 40).val() == mint(2).pow(40).val());
	{ auto B = cumulative_sum({ 3, 1, 4, 1, 5 }); CHECK(B.size() == 6); CHECK(B[4] - B[1] == 6); }
	{
		CUMSUM2D cs({ {1, 2, 3}, {4, 5, 6} });
		CHECK(cs.query(0, 0, 2, 3) == 21); CHECK(cs.query(1, 1, 2, 3) == 11); CHECK(cs.query(0, 1, 2, 2) == 7); CHECK(cs.query(1, 1, 1, 3) == 0);
		IMOS2D im(3, 4); im.add(0, 0, 2, 2, 1); im.add(1, 1, 3, 4, 10); im.add(2, 2, 2, 4, 100);
		CHECK((im.build() == vector<vector<ll>>{{1, 1, 0, 0}, { 1, 11, 10, 10 }, { 0, 10, 10, 10 }}));
	}
	{ auto p = era(30); CHECK((p == vector<ll>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29})); CHECK(era(2) == vector<ll>{2}); CHECK(era(1).empty()); }
	{ auto f = prime_factor<ll>(360); CHECK((f == vector<pll>{{2, 3}, { 3, 2 }, { 5, 1 }})); CHECK(prime_factor<ll>(1).empty()); }
	CHECK(gcd(12, 18) == 6); CHECK(gcd(7, 0) == 7); CHECK(gcd(0, 7) == 7);
	{ auto d = to_base_m(10, 2); CHECK((d == vector<ll>{0, 1, 0, 1})); CHECK(from_base_n(2, d) == 10); CHECK((convert_base_digits(10, 16, { 5, 5, 2 }) == vector<ll>{15, 15})); }
	{ C2 c(60); CHECK(c.get(5, 2) == 10); CHECK(c.get(60, 30) == 118264581564861424LL); CHECK(c.get(2, 5) == 0); }
	{ Combination comb(1000); CHECK(comb(5, 2).val() == 10); CHECK(comb.P(5, 2).val() == 20); CHECK(comb.H(3, 2).val() == 6); CHECK(comb(3, 5).val() == 0); }
	// --- Search ---
	CHECK(binary_search_range(0, 100, [](ll x) { return x * x >= 50; }) == 8);
	CHECK(binary_search_range_max(0, 100, [](ll x) { return x * x <= 50; }) == 7);
	CHECK(binary_search_range(0, 5, [](ll x) { return x > 10; }) == -1);
	// --- String ---
	{ auto r = RLE(vector<char>{'a', 'a', 'b', 'c', 'c', 'c'}); CHECK((r == vector<pair<char, int>>{{'a', 2}, { 'b', 1 }, { 'c', 3 }})); }
	{ string s = "abaaababa"; auto r = manacher(s); CHECK((r == vector<int>{1, 2, 1, 4, 1, 2, 3, 2, 1})); }
	{
		vector<ll> A = { 100, -5, 100, 7 };
		CHECK((compress(A) == vector<int>{2, 0, 2, 1}));
		COMPRESS<ll> cp(A); CHECK(cp.size() == 3); CHECK(cp[cp.get(7)] == 7); CHECK(cp.get(8) == 2); CHECK(cp.get(-100) == 0);
		COMPRESS<int> c2; c2.add(5); c2.add(1); c2.add(5); c2.build(); CHECK(c2.size() == 2); CHECK(c2.get(5) == 1);
	}
	// --- Geometry ---
	CHECK(abs(euclid(pll{ 0, 0 }, pll{ 3, 4 }) - 5.0) < 1e-9);
	CHECK(abs(euclid<ll>(0, 0, 3, 4) - 5.0) < 1e-9);
	CHECK(getDistanceSq<ll>(0, 0, 3, 4) == 25);
	CHECK(manhattan<ll>(1, 2, 4, -2) == 7);
	CHECK(isInArea(0, 2, 3, 3) && !isInArea(3, 0, 3, 3));
	{
		LINE l1(0, 0, 2, 2), l2(1, 1, 5, 5), l3(0, 1, 1, 2), l4(0, 0, 1, -1);
		CHECK(l1.is_same(l2)); CHECK(l1.is_parallel(l3)); CHECK(!l1.is_same(l3)); CHECK(l1.is_vertical(l4));
		CHECK(l1.contains(7, 7)); CHECK(!l1.contains(7, 6));
		LINE pb = get_canonical(0, 0, 2, 0); CHECK(pb.contains(1, 100)); CHECK(pb.is_same(LINE(1, 0, 1, 5)));
	}
	{
		vector<pll> P = { {0, 0}, {4, 0}, {0, 4}, {4, 4}, {2, 1} };
		DELAUNAY dt(P);
		CHECK(dt.triangles.size() == 4); // 点 n=5, 凸包 h=4 → 2n-2-h = 4
		CHECK(dt.edges.size() == 8);     // 3n-3-h = 8
		vector<pll> Q = { {0, 0}, {1, 1}, {2, 2} }; DELAUNAY dq(Q);
		CHECK(dq.triangles.empty()); CHECK(dq.edges.size() == 2);
	}
	{ vector<pll> P = { {0, 0}, {10, 0}, {1, 0} }; auto e = mst_points(P); CHECK(e.size() == 2); }
	// --- Graph ---
	{
		GRAPH g(5);
		g.add_bidir(0, 1); g.add_bidir(1, 2); g.add_bidir(2, 3); g.add_bidir(1, 4);
		vector<int> dist(5, -1), route(5, -1); g.bfs(0, dist, route);
		CHECK(dist[3] == 3);
		auto path = restoration(3, route); CHECK((path == vector<int>{3, 2, 1, 0}));
		vector<bool> vis(5); g.dfs(0, vis); CHECK(count(ALL(vis), true) == 5);
		CHECK((g.get_tree_centers() == vector<int>{1, 2} || g.get_tree_centers() == vector<int>{2, 1}));
		CHECK(g.get_tree_centroids() == vector<int>{1});
		vector<bool> v2(5); CHECK(!g.dfs_cycle(0, -1, v2));
		g.add_bidir(3, 0); vector<bool> v3(5); CHECK(g.dfs_cycle(0, -1, v3)); g.remove(3, 0); g.remove(0, 3);
		CHECK(g.find(0, 1)); CHECK(!g.find(0, 3));
		auto d = calc_diameter_of_tree(g); CHECK(d.dist == 3);
		LCA lca(g, 0);
		CHECK(lca.get(3, 4) == 1); CHECK(lca.get(3, 2) == 2); CHECK(lca.get(0, 4) == 0);
		CHECK(lca.dist(3, 4) == 3); CHECK(lca.wdist(3, 4) == 3);
		CHECK(lca.ancestor(3, 2) == 1); CHECK(lca.ancestor(3, 3) == 0); CHECK(lca.ancestor(3, 4) == -1);
		CHECK(lca.depth[3] == 3); CHECK(lca.parent[0] == -1); CHECK(lca.parent[4] == 1);
		LCA l2(g, 3); CHECK(l2.get(0, 4) == 1);
	}
	{
		GRAPH d(4); d.add(2, 0); d.add(0, 1); d.add(3, 1);
		CHECK((d.topological_sort(true) == vector<int>{2, 0, 3, 1}));
		auto t = d.topological_sort(); CHECK(t.size() == 4);
		vector<int> pos(4); rep(i, 0, 4) pos[t[i]] = i; CHECK(pos[2] < pos[0] && pos[0] < pos[1] && pos[3] < pos[1]);
		d.add(1, 2); CHECK(d.topological_sort().empty()); CHECK(d.topological_sort(true).empty());
	}
	{
		WGRAPH g(5); g.add(0, 1, 1); g.add(1, 2, 0); g.add(0, 2, 1); g.add(2, 3, 1); g.add(0, 3, 1);
		auto d = g.bfs01(0); CHECK((d == vector<ll>{0, 1, 1, 1, INF})); CHECK(d == g.dijkstra(0));
		vector<ll> dist(5, INF); vector<int> route(5, -1); g.bfs01(1, dist, route);
		CHECK(dist[3] == 1); CHECK((restoration(3, route) == vector<int>{3, 2, 1}));
		WGRAPH t(4); t.add_bidir(0, 1, 3); t.add_bidir(1, 2, 4); t.add_bidir(1, 3, 10);
		LCA lw(t, 0); CHECK(lw.wdist(2, 3) == 14); CHECK(lw.dist(2, 3) == 2); CHECK(lw.wdist(0, 3) == 13);
	}
	{
		WGRAPH g(4);
		g.add(0, 1, 5); g.add(1, 2, 1); g.add(0, 2, 10); g.add(2, 3, 2);
		auto d = g.dijkstra(0); CHECK(d[2] == 6); CHECK(d[3] == 8);
		vector<ll> dist(4, INF); vector<int> route(4, -1); g.dijkstra(0, dist, route);
		CHECK((restoration(3, route) == vector<int>{3, 2, 1, 0}));
		auto wf = g.warshall_floyd(); CHECK(wf[0][3] == 8); CHECK(wf[3][0] == INF);
		WGRAPH t(4); t.add_bidir(0, 1, 3); t.add_bidir(1, 2, 4); t.add_bidir(1, 3, 10);
		auto dm = calc_diameter_of_tree(t); CHECK(dm.dist == 14);
	}
	{
		GraphHeuristic g(4); g.add_bidir(0, 1); g.add_bidir(1, 2); g.add(2, 3);
		CHECK(g.find(1, 2)); g.remove(1, 2); CHECK(!g.find(1, 2)); CHECK(g.get_neighbors(1).size() == 1);
		WeightGraphHeuristic w(3); w.add(0, 1, 4); w.add(1, 2, 3); CHECK(w.dijkstra(0)[2] == 7);
	}
	// --- DataStructure ---
	{ UNIONFIND uf(5); uf.merge(0, 1); uf.merge(3, 4); uf.merge(1, 4); CHECK(uf.connected(0, 3)); CHECK(!uf.connected(0, 2)); CHECK(uf.size(4) == 4); }
	{
		SEGMENTTREE<ll, SumOp> s; s.init(5); rep(i, 0, 5) s.update(i, i + 1); CHECK(s.query(1, 4) == 9); CHECK(s.query(0, 5) == 15); CHECK(s.query(2, 2) == 0);
		SEGMENTTREE<ll, MaxOp> mx; mx.init(3); mx.update(0, 5); mx.update(2, 7); CHECK(mx.query(0, 2) == 5); CHECK(mx.query(0, 3) == 7);
		SEGMENTTREE<ll, MinOp> mn; mn.init(3); mn.update(1, -4); CHECK(mn.query(0, 3) == -4);
	}
	{ FenwickTree fw(10); fw.add(3, 5); fw.add(7, 2); CHECK(fw.sum(0, 3) == 5); CHECK(fw.sum(4, 9) == 2); CHECK(fw.sum(0, 9) == 7); CHECK(fw.sum_prefix(2) == 0); }
	{
		IntervalSet<ll, ll> S(-1);
		S.update(0, 10, 1); S.update(3, 5, 2);
		CHECK(S.get_val(2) == 1); CHECK(S.get_val(3) == 2); CHECK(S.get_val(5) == 1); CHECK(S.get_val(10) == -1); CHECK(S[4] == 2);
		CHECK(S.covered(0, 10) == false); CHECK(S.covered(3, 5)); CHECK(S.same(3, 4)); CHECK(!S.same(2, 3));
		S.erase(4, 7); CHECK(!S.covered(5)); CHECK(S.covered(3)); CHECK(S.covered(7));
		IntervalSet<ll> I; I.insert(0, 3); I.insert(3, 5); I.insert(7, 9);
		CHECK(I.same(0, 4)); CHECK(I.get_mex(0) == 5); CHECK(I.get_mex(6) == 6);
		ll total = 0; I.insert(4, 8, [&](ll l, ll r, ll) { total += r - l; }, [&](ll l, ll r, ll) { total -= r - l; }); CHECK(total == 9 - 5 - 2); CHECK(I.covered(0, 9));
	}
	{ DOUBLING db(3, { 1, 2, 0 }, 1000000000000LL); CHECK(db.query(0, 4) == 1); CHECK(db.query(0, 1000000000000LL) == 1000000000000LL % 3); }
	{ PersistentStack<int> s0; auto s1 = s0.push(1); auto s2 = s1.push(2); auto s3 = s1.push(3); CHECK((s2.to_vector() == vector<int>{1, 2})); CHECK((s3.to_vector() == vector<int>{1, 3})); CHECK(s3.pop().top() == 1); CHECK(s0.empty()); }
	{ IndexedSet st(10); st.add(3); st.add(5); st.add(7); CHECK(!st.add(3)); st.remove(3); CHECK(st.size() == 2); CHECK(!st.contains(3)); CHECK(st[st.position(7)] == 7); }
	// --- Other / Heuristic ---
	{ rep(i, 0, 1000) { int x = random_int_range(3, 7); CHECK(3 <= x && x < 7); double d = random_real_0_1(); CHECK(0 <= d && d < 1); } vector<int> v = { 1, 2, 3, 4 }; shuffle_vector(v); sort(ALL(v)); CHECK((v == vector<int>{1, 2, 3, 4})); CHECK(random_pickup(v) >= 1); }
	CHECK(splitmix64(1) != splitmix64(2));
	{ TIMER t; CHECK(t.is_under(10.0)); }
	{
		vector<pll> pts = { {0, 0}, {1, 0}, {0, 1}, {100, 100}, {101, 100}, {100, 101} };
		vector<int> id = { 0, 1, 0, 1, 0, 1 };
		kMeans(pts, id, 2); CHECK(id[0] == id[1] && id[1] == id[2] && id[3] == id[4] && id[4] == id[5] && id[0] != id[3]);
		vector<int> id2 = { 0, 1, 0, 1, 0, 1 }; kMeansWithSizes(pts, id2, 2);
		CHECK(count(ALL(id2), 0) == 3); CHECK(id2[0] == id2[1] && id2[1] == id2[2]);
	}
	{
		vector<vector<int>> V = { {1, 1, 1}, {0, 1, 0}, {0, 0, 0} };
		CHECK(simple_connection_judge(3, V, 1, 1));
		vector<vector<int>> W = { {1, 1, 0}, {0, 1, 0}, {0, 1, 1} };
		CHECK(!simple_connection_judge(3, W, 1, 1));
	}
	{
		BIT_FIELD bf; bf.init_mask(); bf.set(0, 9); bf.bit_shift_w(1); CHECK(bf.allocated_blocks.none());
		bf.set(2, 0); bf.bit_shift_w(-1); CHECK(bf.allocated_blocks.none());
		bf.set(2, 3); bf.bit_shift_hw(1, -2); CHECK(bf.allocated_blocks.count() == 1 && bf.allocated_blocks[3 * 10 + 1]);
	}
	{ double turn = 0, mx = 100; ll o = 10, n = 5; CHECK(ANNEALING::temperature(turn, mx, o, n)); }
	cout << "ALL OK" << el;
}
