#pragma once
#include "../Template/template.hpp"

//ドロネー三角形分割 O(N log N) (分割統治 + quad-edge)
//参考: KACTL FastDelaunay (CC0)
/* 使用例
	vector<pll> P(N); cin >> P;
	DELAUNAY dt(P);
	for (auto [a, b, c] : dt.triangles) {}	// 三角形(元の添字, 反時計回り)
	for (auto [u, v] : dt.edges) {}		// 辺(u < v) ユークリッドMSTはこの辺の上で求まる
	整数座標のみ・判定は__int128で厳密、|x|,|y| <= 5e8 程度まで
	重複点は最初に現れた添字にまとめる (重複した点は三角形・辺に現れない)
	全点が一直線上なら triangles は空、edges は直線上で隣り合う点の組
	4点以上が同一円周上にある場合、分割の仕方は一意でないがどれか1つを返す
*/
struct DELAUNAY {
	vector<array<int, 3>> triangles;
	vector<pair<int, int>> edges;

	DELAUNAY() {}
	DELAUNAY(const vector<pll>& P) { build(P); }

	void build(const vector<pll>& P) {
		triangles.clear(); edges.clear(); pool.clear(); H = nullptr;
		int n = P.size();
		vector<int> ord(n);
		iota(ord.begin(), ord.end(), 0);
		stable_sort(ord.begin(), ord.end(), [&](int i, int j) { return P[i] < P[j]; });
		pts.clear(); id.clear();
		for (int i : ord) {
			if (!pts.empty() && pts.back() == P[i]) continue;
			pts.push_back(P[i]); id.push_back(i);
		}
		int m = pts.size();
		if (m < 2) return;
		bool collinear = true;
		for (int i = 2; i < m; i++) if (cross(0, 1, i) != 0) { collinear = false; break; }
		if (collinear) {
			for (int i = 0; i + 1 < m; i++) add_edge(id[i], id[i + 1]);
			return;
		}
		Q e = rec(0, m).first;
		vector<Q> q = { e };
		while (cross(e->o->F(), e->F(), e->p) < 0) e = e->o;
		auto walk = [&](Q e, bool keep) {
			array<int, 3> t; int k = 0;
			Q c = e;
			do {
				c->mark = true;
				if (k < 3) t[k] = c->p;
				k++;
				q.push_back(c->r());
				c = c->next();
			} while (c != e);
			if (keep && k == 3) triangles.push_back({ id[t[0]], id[t[1]], id[t[2]] });
		};
		walk(e, false);	//外側の面
		for (size_t qi = 0; qi < q.size(); qi++) if (!q[qi]->mark) walk(q[qi], true);
		for (auto& t : triangles) rep(k, 0, 3) add_edge(t[k], t[(k + 1) % 3]);
		sort(edges.begin(), edges.end());
		edges.erase(unique(edges.begin(), edges.end()), edges.end());
	}

private:
	using lll = i128;
	struct Quad {
		Quad* rot = nullptr; Quad* o = nullptr; int p = -1; bool mark = false;
		int& F() { return r()->p; }
		Quad*& r() { return rot->rot; }
		Quad* prev() { return rot->o->rot; }
		Quad* next() { return r()->prev(); }
	};
	using Q = Quad*;
	deque<Quad> pool;
	Q H = nullptr;	//再利用リスト
	vector<pll> pts;	//重複を除きソートした点
	vector<int> id;	//pts[i] の元の添字

	void add_edge(int u, int v) { edges.emplace_back(min(u, v), max(u, v)); }
	//(b - a) × (c - a)
	ll cross(int a, int b, int c) const {
		return (pts[b].first - pts[a].first) * (pts[c].second - pts[a].second)
			- (pts[b].second - pts[a].second) * (pts[c].first - pts[a].first);
	}
	//点pが三角形abc(反時計回り)の外接円の内部に厳密に含まれるか
	bool circ(int p, int a, int b, int c) const {
		auto [px, py] = pts[p];
		lll ax = pts[a].first - px, ay = pts[a].second - py;
		lll bx = pts[b].first - px, by = pts[b].second - py;
		lll cx = pts[c].first - px, cy = pts[c].second - py;
		lll A = ax * ax + ay * ay, B = bx * bx + by * by, C = cx * cx + cy * cy;
		return (ax * by - ay * bx) * C + (bx * cy - by * cx) * A + (cx * ay - cy * ax) * B > 0;
	}
	Q make_edge(int orig, int dest) {
		Q r = H;
		if (r) H = r->o;
		else {
			Q a[4];
			rep(i, 0, 4) { pool.emplace_back(); a[i] = &pool.back(); }
			rep(i, 0, 4) a[i]->rot = a[(i + 1) % 4];
			r = a[0];
		}
		rep(i, 0, 4) r = r->rot, r->p = -1, r->mark = false, r->o = (i & 1) ? r : r->r();
		r->p = orig; r->F() = dest;
		return r;
	}
	void splice(Q a, Q b) {
		swap(a->o->rot->o, b->o->rot->o);
		swap(a->o, b->o);
	}
	Q connect(Q a, Q b) {
		Q q = make_edge(a->F(), b->p);
		splice(q, a->next());
		splice(q->r(), b);
		return q;
	}
	//pts[l, r) を三角形分割し、(最左点から出る凸包の辺, 最右点から出る凸包の辺) を返す
	pair<Q, Q> rec(int l, int r) {
		int n = r - l;
		if (n <= 3) {
			Q a = make_edge(l, l + 1), b = make_edge(l + 1, r - 1);
			if (n == 2) return { a, a->r() };
			splice(a->r(), b);
			ll side = cross(l, l + 1, l + 2);
			Q c = side ? connect(b, a) : nullptr;
			return { side < 0 ? c->r() : a, side < 0 ? c : b->r() };
		}
		int mid = r - n / 2;
		auto [ra, A] = rec(l, mid);
		auto [B, rb] = rec(mid, r);
		//下側の共通接線を探す
		while ((cross(B->p, A->F(), A->p) < 0 && (A = A->next())) ||
			(cross(A->p, B->F(), B->p) > 0 && (B = B->r()->o)));
		Q base = connect(B->r(), A);
		if (A->p == ra->p) ra = base->r();
		if (B->p == rb->p) rb = base;
		auto valid = [&](Q e) { return cross(e->F(), base->F(), base->p) > 0; };
		auto del = [&](Q e, bool left) {
			if (!valid(e)) return e;
			while (true) {
				Q t = left ? e->o : e->prev();
				if (!circ(t->F(), base->F(), base->p, e->F())) break;
				splice(e, e->prev());
				splice(e->r(), e->r()->prev());
				e->o = H; H = e;
				e = t;
			}
			return e;
		};
		while (true) {
			Q LC = del(base->r()->o, true);
			Q RC = del(base->prev(), false);
			if (!valid(LC) && !valid(RC)) break;
			if (!valid(LC) || (valid(RC) && circ(RC->F(), RC->p, LC->F(), LC->p)))
				base = connect(RC, base->r());
			else
				base = connect(base->r(), LC->r());
		}
		return { ra, rb };
	}
};
