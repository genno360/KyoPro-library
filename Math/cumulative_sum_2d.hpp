#pragma once
#include "../Template/template.hpp"

//二次元累積和
/* 使用例
	vector<vector<ll>> A(H, vector<ll>(W)); cin >> A;
	CUMSUM2D cs(A);
	cs.query(x1, y1, x2, y2);	// [x1, x2) × [y1, y2) の和
*/
struct CUMSUM2D {
	vector<vector<ll>> S;
	CUMSUM2D() {}
	CUMSUM2D(const vector<vector<ll>>& A) {
		int H = A.size(), W = H ? A[0].size() : 0;
		S.assign(H + 1, vector<ll>(W + 1, 0));
		rep(i, 0, H) rep(j, 0, W) S[i + 1][j + 1] = S[i][j + 1] + S[i + 1][j] - S[i][j] + A[i][j];
	}
	ll query(int x1, int y1, int x2, int y2) const {
		if (x1 >= x2 || y1 >= y2) return 0;
		return S[x2][y2] - S[x1][y2] - S[x2][y1] + S[x1][y1];
	}
};

//二次元いもす法
/* 使用例
	IMOS2D im(H, W);
	im.add(x1, y1, x2, y2, v);	// [x1, x2) × [y1, y2) に v を足す
	auto B = im.build();		// B[i][j] が各マスの値 (H × W)
*/
struct IMOS2D {
	int H, W;
	vector<vector<ll>> D;
	IMOS2D(int h, int w) : H(h), W(w), D(h + 1, vector<ll>(w + 1, 0)) {}
	void add(int x1, int y1, int x2, int y2, ll v) {
		if (x1 >= x2 || y1 >= y2) return;
		D[x1][y1] += v; D[x1][y2] -= v; D[x2][y1] -= v; D[x2][y2] += v;
	}
	vector<vector<ll>> build() const {
		vector<vector<ll>> B = D;
		rep(i, 0, H + 1) rep(j, 1, W + 1) B[i][j] += B[i][j - 1];
		rep(i, 1, H + 1) rep(j, 0, W + 1) B[i][j] += B[i - 1][j];
		B.pop_back();
		for (auto& row : B) row.pop_back();
		return B;
	}
};
