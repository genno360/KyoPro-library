#pragma once
#include "../Template/template.hpp"

//二分探索
//Funcはboolが返り値で引数に整数を持つ関数
//https://atcoder.jp/contests/typical90/submissions/80262367
//条件を満たす最小のnを探す
template <typename Func>
ll binary_search_range(ll low, ll high, Func check) {
	ll left = low;
	ll right = high;
	ll result = -1; // 条件を満たす値が見つからなかった場合の初期値

	while (left <= right) {
		ll mid = left + (right - left) / 2; // オーバーフロー防止

		if (check(mid)) {
			result = mid;      // midは条件を満たすので候補として記録
			right = mid - 1;   // さらに小さな値で満たすか左側を探索
		}
		else {
			left = mid + 1;    // midは条件を満たさないので右側を探索
		}
	}
	return result;
}

//条件を満たす最大のnを探す
template <typename Func>
ll binary_search_range_max(ll low, ll high, Func check) {
	ll left = low;
	ll right = high;
	ll result = -1;

	while (left <= right) {
		ll mid = left + (right - left) / 2;

		if (check(mid)) {
			result = mid;
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	return result;
}
