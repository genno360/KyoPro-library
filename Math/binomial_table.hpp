#pragma once
#include "../Template/template.hpp"

struct C2 {//二項係数

	C2(int n = 3000) {
		C.resize(n + 10, vector<ll>(n + 10));
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= i; j++) {
				if (j == 0 || j == i) {
					C[i][j] = 1;
				}
				else {
					C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
				}
			}
		}
	}

	ll get(ll A, ll B) {
		if (A < B) return 0;
		if (A < 0 || B < 0) return 0;
		return C[A][B];
	}
private:
	vector<vector<ll>> C;
};
