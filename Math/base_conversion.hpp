#pragma once
#include "../Template/template.hpp"

ll from_base_n(int base, const vector<ll>& digits) {//n進数を数字に
	ll value = 0;
	ll power = 1;
	for (ll d : digits) {
		value += d * power;
		power *= base;
	}
	return value;
}

vector<ll> to_base_m(ll value, int base) {//数字をn進数に
	if (value == 0) return { 0 };
	vector<ll> digits;
	while (value > 0) {
		digits.push_back(value % base);
		value /= base;
	}
	return digits;
}

vector<ll> convert_base_digits(//a進数をb進数に
	int from_base,
	int to_base,
	const vector<ll>& digits
) {
	return to_base_m(from_base_n(from_base, digits), to_base);
}
