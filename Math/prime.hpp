#pragma once
#include "../Template/template.hpp"

//素数列挙(n以下) エラトステネスの篩 O(n log log n)
vector<ll> era(int n) {
	vector<ll> res;
	if (n < 2) return res;
	vector<bool> isprime(n + 1, true);
	isprime[0] = false;
	isprime[1] = false;
	for (ll i = 2; i <= n; ++i) {
		if (isprime[i]) {
			res.push_back(i);
			for (ll j = i * 2; j <= n; j += i) isprime[j] = false;
		}
	}
	return res;
}
template <typename T>
vector<pair<T, T>> prime_factor(T n) {//素因数分解 O(√n) {素因数, 指数} の昇順
	vector<pair<T, T>> ret;
	for (T i = 2; i * i <= n; i++) {
		if (n % i != 0) continue;
		T tmp = 0;
		while (n % i == 0) {
			tmp++;
			n /= i;
		}
		ret.push_back(make_pair(i, tmp));
	}
	if (n != 1) ret.push_back(make_pair(n, 1));
	return ret;
}
