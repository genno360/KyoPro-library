#pragma once
#include "../Template/template.hpp"

// ダブリング
struct DOUBLING {
	int N;
	vector<vector<int>> table;

	DOUBLING(int n, const vector<int>& a, ll max_step) : N(n) {
		int log = 1;
		while ((1LL << log) <= max_step) log++;

		table.assign(log, vector<int>(N));
		table[0] = a;

		for (int k = 1; k < log; k++) {
			for (int i = 0; i < N; i++) {
				table[k][i] = table[k - 1][table[k - 1][i]];
			}
		}
	}

	int query(int pos, ll step) {
		for (int k = 0; step > 0; k++, step >>= 1) {
			if (step & 1) pos = table[k][pos];
		}
		return pos;
	}
};
