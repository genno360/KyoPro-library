#pragma once
#include "../Template/template.hpp"

template<class T, class Op>
//セグメントツリー
// 宣言は SEGMENTTREE<ll, SumOp> seg_sum;というように
//initで初期化(長さN、各要素e)
// //updateでpos番目をxに更新 /
// /queryでl番目からr番目の区間の演算値を得る
class SEGMENTTREE {
public:
	int siz;
	vector<T> dat;
	Op op;

	void init(int N) {
		siz = 1;
		while (siz < N) siz <<= 1;
		dat.assign(siz * 2, op.id());
	}

	void update(int pos, T x) {
		pos += siz;
		dat[pos] = x;
		while (pos > 1) {
			pos >>= 1;
			dat[pos] = op(dat[pos * 2], dat[pos * 2 + 1]);
		}
	}

	T query(int l, int r) const {
		T vl = op.id(), vr = op.id();
		l += siz; r += siz;
		while (l < r) {
			if (l & 1) vl = op(vl, dat[l++]);
			if (r & 1) vr = op(dat[--r], vr);
			l >>= 1; r >>= 1;
		}
		return op(vl, vr);
	}
};
struct SumOp {
	ll operator()(ll a, ll b) const { return a + b; }
	ll id() const { return 0; }
};

struct MaxOp {
	ll operator()(ll a, ll b) const { return max(a, b); }
	ll id() const { return LLONG_MIN; }
};

struct MinOp {
	ll operator()(ll a, ll b) const { return min(a, b); }
	ll id() const { return LLONG_MAX; }
};
