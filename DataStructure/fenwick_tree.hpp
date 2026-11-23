#pragma once
#include "../Template/template.hpp"

//フェネック木(フェネックツリー)
// 一点更新 + 区間和取得をどちらも O(log N) で行えるデータ構造
// 別名 BIT (Binary Indexed Tree)
/* 使用例

	FenwickTree fw(100);

	fw.add(5,10);

	cout<<fw.sum(0,5)<<endl;
*/
struct FenwickTree {
	int n;
	vector<ll> bit;

	FenwickTree(int n) :n(n) {
		bit.assign(n + 1, 0);
	}

	void add(int idx, ll val) {
		idx++;

		while (idx <= n) {
			bit[idx] += val;
			idx += idx & -idx;
		}
	}

	ll sum_prefix(int idx) {
		idx++;

		ll res = 0;

		while (idx > 0) {
			res += bit[idx];
			idx -= idx & -idx;
		}

		return res;
	}

	ll sum(int l, int r) {
		if (l > r) return 0;

		return sum_prefix(r)
			- (l ? sum_prefix(l - 1) : 0);
	}
};
