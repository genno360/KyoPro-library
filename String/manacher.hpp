#pragma once
#include "../Template/template.hpp"

vector<int> manacher(string& str) {
	//その文字を中心とした最長の回文の半径を計算する
	vector<int> res(str.size());
	int i = 0, j = 0;
	while (i < str.size()) {
		while (i - j >= 0 && i + j < str.size() && str[i - j] == str[i + j]) ++j;
		res[i] = j;
		int k = 1;
		while (i - k >= 0 && k + res[i - k] < j) res[i + k] = res[i - k], ++k;
		i += k; j -= k;
	}
	return res;
}
