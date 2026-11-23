#pragma once
#include "../Template/template.hpp"

//座標圧縮
/* 使用例
	COMPRESS<ll> cp(A);		// A の値をまとめて登録 (cp.add(x) で追加してから cp.build() でも可)
	cp.get(x);				// x の番号 (0 始まり、x 以上で最小の値の番号)
	cp[i];					// 番号 i の元の値
	cp.size();				// 異なる値の個数
	auto B = compress(A);	// A を番号の列に置き換えたもの
*/
template<typename T>
struct COMPRESS {
	vector<T> xs;
	COMPRESS() {}
	COMPRESS(const vector<T>& A) : xs(A) { build(); }
	void add(const T& x) { xs.push_back(x); }
	void build() {
		sort(xs.begin(), xs.end());
		xs.erase(unique(xs.begin(), xs.end()), xs.end());
	}
	int get(const T& x) const { return lower_bound(xs.begin(), xs.end(), x) - xs.begin(); }
	const T& operator[](int i) const { return xs[i]; }
	int size() const { return xs.size(); }
};
template<typename T>
vector<int> compress(const vector<T>& A) {
	COMPRESS<T> cp(A);
	vector<int> res(A.size());
	rep(i, 0, A.size()) res[i] = cp.get(A[i]);
	return res;
}
