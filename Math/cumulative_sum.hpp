#pragma once
#include "../Template/template.hpp"

vector<ll> cumulative_sum(const vector<ll>& A) {//累積和 元配列 A の区間 [l, r) の和は B[r] - B[l]
	vector<ll> B;
	B.push_back(0);
	rep(i, 0, A.size()) {
		B.push_back(B.back() + A[i]);
	}
	return B;
}
