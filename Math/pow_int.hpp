#pragma once
#include "../Template/template.hpp"

template<typename T>
T pow_int(T base, unsigned int exponent) {
	T result = 1;
	while (exponent > 0) {
		if (exponent & 1) {  // 奇数の場合
			result *= base;
		}
		base *= base;
		exponent >>= 1;  // 2で割る
	}
	return result;
}
