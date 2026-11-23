#pragma once
#include "../Template/template.hpp"

template<typename T>
vector<pair<T, int>> RLE(const vector<T>& A) { //ランレングス圧縮
	vector<pair<T, int>> ans;
	if (A.empty()) return ans;

	ans.push_back({ A[0], 1 });

	for (size_t i = 1; i < A.size(); i++) {
		if (ans.back().first == A[i]) {
			ans.back().second++;
		}
		else {
			ans.push_back({ A[i], 1 });
		}
	}
	return ans;
}
