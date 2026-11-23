#pragma once
#include "../Template/template.hpp"

//最大公約数 (ユークリッドの互除法)
// ※ ll など int 以外を渡すと std::gcd が呼ばれる
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}
