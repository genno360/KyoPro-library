#pragma once
#include "../Template/template.hpp"

struct Combination {// modint用二項係数を扱う構造体
	std::vector<mint> fac, finv, inv;

	// コンストラクタで最大値 (MAX) を指定してテーブルを初期化
	Combination(int max_val = 700000) : fac(max_val), finv(max_val), inv(max_val) {
		const int MOD = mint::mod();
		fac[0] = fac[1] = 1;
		finv[0] = finv[1] = 1;
		inv[1] = 1;

		for (int i = 2; i < max_val; i++) {
			fac[i] = fac[i - 1] * i;
			inv[i] = MOD - inv[MOD % i] * (MOD / i);
			finv[i] = finv[i - 1] * inv[i];
		}
	}

	// nCk を計算
	mint operator()(int n, int k) const {
		if (n < k || n < 0 || k < 0) return 0;
		return fac[n] * finv[k] * finv[n - k];
	}

	// 順列 nPk も必要な場合に
	mint P(int n, int k) const {
		if (n < k || n < 0 || k < 0) return 0;
		return fac[n] * finv[n - k];
	}

	// 重複組合せ nHk (= n+k-1 C k)
	mint H(int n, int k) const {
		if (n < 0 || k < 0) return 0;
		if (n == 0 && k == 0) return 1;
		return (*this)(n + k - 1, k);
	}
};
