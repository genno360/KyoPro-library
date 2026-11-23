// README に載せている使用例の動作確認
#include "../Template/template.hpp"
#include "../Geometry/distance.hpp"
#include "../Geometry/line.hpp"
#include "../Geometry/delaunay.hpp"
#include "../DataStructure/union_find.hpp"
#include "../DataStructure/segment_tree.hpp"
#include "../DataStructure/fenwick_tree.hpp"
#include "../DataStructure/interval_set.hpp"
#include "../String/run_length_encoding.hpp"
#include "../Graph/graph.hpp"
#include "../Graph/lca.hpp"
#include "../String/compress.hpp"
#include "../Math/cumulative_sum_2d.hpp"

#define CHECK(x) do { if (!(x)) { cerr << "FAILED: " #x " (line " << __LINE__ << ")\n"; exit(1); } } while (0)

struct P { int x, y; DEF_CMP(P) };
struct XorOp {
	ll operator()(ll a, ll b) const { return a ^ b; }
	ll id() const { return 0; }
};

int main() {
	{ set<P> st; st.insert({1, 2}); st.insert({1, 2}); st.insert({0, 5}); CHECK(st.size() == 2); CHECK(st.begin()->x == 0); }
	{ string S = "aabccc"; auto r = RLE(vector<char>(ALL(S))); CHECK(r.size() == 3 && r[2].second == 3); }
	{
		vector<pll> pts = { {0, 0}, {1, 1}, {2, 2}, {0, 1} };
		set<LINE> st; int N = pts.size();
		rep(i, 0, N) rep(j, i + 1, N) st.insert(LINE(pts[i].first, pts[i].second, pts[j].first, pts[j].second));
		CHECK(st.size() == 4);  // y=x, 3本の線
	}
	{
		// Delaunay で ユークリッド MST と O(N^2) を比較
		rep(trial, 0, 50) {
			int N = random_device{}() % 60 + 2;
			vector<pll> P(N); for (auto& p : P) p = { (ll)(random_device{}() % 200), (ll)(random_device{}() % 200) };
			auto mst = [&](vector<tuple<ll, int, int>> es) { sort(ALL(es)); UNIONFIND uf(N); ll s = 0; for (auto [w, u, v] : es) if (!uf.connected(u, v)) { uf.merge(u, v); s += w; } return s; };
			DELAUNAY dt(P); vector<tuple<ll, int, int>> e1, e2;
			for (auto [u, v] : dt.edges) e1.push_back({ getDistanceSq(P[u].first, P[u].second, P[v].first, P[v].second), u, v });
			rep(u, 0, N) rep(v, u + 1, N) e2.push_back({ getDistanceSq(P[u].first, P[u].second, P[v].first, P[v].second), (int)u, (int)v });
			// 重複点があると Delaunay では重複点が辺に現れないので、重複なしの場合だけ比較
			set<pll> uniq(ALL(P)); if ((int)uniq.size() != N) continue;
			CHECK(mst(e1) == mst(e2));
		}
	}
	{ SEGMENTTREE<ll, XorOp> seg; seg.init(4); seg.update(0, 5); seg.update(1, 3); CHECK(seg.query(0, 2) == 6); }
	{
		vector<int> A = { 2, 0, 3, 1 }; int N = 4;
		FenwickTree fw(N); ll inv = 0;
		rep(i, 0, N) { inv += i - fw.sum_prefix(A[i]); fw.add(A[i], 1); }
		CHECK(inv == 3);
	}
	{
		IntervalSet<ll> S; ll covered_len = 0;
		auto add = [&](ll l, ll r, ll) { covered_len += r - l; };
		auto del = [&](ll l, ll r, ll) { covered_len -= r - l; };
		S.insert(0, 3, add, del); S.insert(2, 5, add, del); CHECK(covered_len == 5);
		S.erase(1, 2, add, del); CHECK(covered_len == 4);
		vector<pair<ll, ll>> segs; for (auto [l, r, val] : S) segs.push_back({ l, r });
		CHECK((segs == vector<pair<ll, ll>>{{0, 1}, { 2, 5 }}));
	}
	{
		vector<ll> A = { 100, -5, 100, 7 };
		auto B = compress(A); CHECK((B == vector<int>{2, 0, 2, 1}));
		COMPRESS<ll> cp(A); CHECK(cp[cp.get(7)] == 7);
	}
	{
		int H = 3, W = 3; IMOS2D im(H, W); im.add(0, 0, 2, 2, 1); im.add(1, 1, 3, 3, 1);
		auto B = im.build(); CHECK(B[1][1] == 2 && B[0][2] == 0 && B[2][2] == 1);
		CUMSUM2D cs(B); CHECK(cs.query(0, 0, H, W) == 8);
	}
	{
		int N = 4; WGRAPH g(N);
		g.add_bidir(0, 1, 5); g.add_bidir(1, 2, 2); g.add_bidir(1, 3, 7);
		LCA lca(g, 0); CHECK(lca.wdist(2, 3) == 9); CHECK(lca.get(2, 3) == 1);
	}
	cout << "EXAMPLES OK" << el;
}
