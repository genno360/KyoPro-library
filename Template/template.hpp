#pragma once
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;

#if defined(_MSC_VER) && !defined(__clang__)
#include <__msvc_int128.hpp>
using u128 = std::_Unsigned128;
using i128 = std::_Signed128;
#else
using u128 = unsigned __int128;
using i128 = __int128;
#endif
/*	using	*/
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using mint = modint1000000007;
//using mint = modint998244353;
/*	マクロ	*/
//#define HEURISTIC_GRAPH

#define rep(i, P, n) for (ll i = P; i < (ll)(n); i++)
#define REP(i, P, n) for (ll i = P; i <= (ll)(n); i++)
#define repm(i, P, n, m) for (ll i = P; i < (ll)(n); i += m)
#define rrep(i, P, n) for (ll i = P; i >= (ll)(n); i--)

//#define rep(i, A, n) for (int i = A; i < (n); i++)
//#define REP(i, A, n) for (int i = A; i <= (n); i++)
//#define repm(i, A, n, m) for (int i = A; i < (n); i += m)
//#define rrep(i, A, n) for (int i = A; i >= (n); i--)
#define Yes cout << "Yes" << el
#define No cout << "No" << el
#define debug(x) cerr << #x << " = " << x << el
#define el '\n'
//小数表示桁数
#define SETPREC(X)  std::fixed << std::setprecision(X)

#define ALL(x) (x).begin(), (x).end()

//構造体にこれを加えればsort可能になる mapのkeyに構造体を使うときにも
#define DEF_CMP(T) auto operator<=>(const T&) const = default;

template<class T, class U> inline bool chmax(T& a, const U& b) { if (a < b) { a = b; return true; } return false; }
template<class T, class U> inline bool chmin(T& a, const U& b) { if (a > b) { a = b; return true; } return false; }
inline void YN(bool ok) {
	cout << (ok ? "Yes" : "No") << el;
}
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string abc = "abcdefghijklmnopqrstuvwxyz";
const int DX[4] = { -1, 1, 0, 0 };
const int DY[4] = { 0, 0, -1, 1 };

const ll INF = LLONG_MAX / 4;

/*	演算子オーバーロード	*/

/* 標準入力 */
template<typename T1, typename T2> istream& operator >> (istream& is, std::pair<T1, T2>& p) { is >> p.first >> p.second; return is; }
template<typename T>istream& operator >> (istream& is, vector<T>& vec) { for (T& x : vec) is >> x; return is; }
/* 標準出力 */
struct Init { Init() { ios::sync_with_stdio(0); cin.tie(0); } }init;

template<typename T1, typename T2>
std::ostream& operator<< (std::ostream& os, std::pair<T1, T2> p) { os << p.first << " " << p.second; return os; }
/*	標準出力系	*/
template<typename T>ostream& operator << (ostream& os, vector<T>& vec) {
	bool first = true;
	for (const auto& x : vec) {
		if (!first)os << ' ';
		first = false;
		os << x;
	}
	return os;
}
template<typename T>
ostream& operator<<(ostream& os, const set<T>& st) {
	bool first = true;
	for (const auto& x : st) {
		if (!first) os << ' ';
		first = false;
		os << x;
	}
	return os;
}
template<typename K, typename V>
ostream& operator<<(ostream& os, const map<K, V>& mp) {
	bool first = true;
	for (const auto& [k, v] : mp) {
		if (!first) os << ' ';
		first = false;
		os << k << ':' << v;
	}
	return os;
}
template<typename T>
ostream& operator<<(ostream& os, const multiset<T>& st) {
	bool first = true;
	for (const auto& x : st) {
		if (!first) os << ' ';
		first = false;
		os << x;
	}
	return os;
}
template<typename K, typename V>
ostream& operator<<(ostream& os, const multimap<K, V>& mp) {
	bool first = true;
	for (const auto& [k, v] : mp) {
		if (!first) os << ' ';
		first = false;
		os << k << ':' << v;
	}
	return os;
}
#ifdef _DEBUG
template<class T>
struct DebugMultiset : std::multiset<T> {
	using Base = std::multiset<T>;
	using Base::Base;
	using Base::erase;

	void erase(const T& x) {
		cerr << "WARNING: multiset::erase(value) は同じ値全消しです\n";
		cerr << "ポインタならひとつだけ消せる\n";
		assert(false);
	}
};
#define multiset DebugMultiset
#else
#define multiset std::multiset
#endif
