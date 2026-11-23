#pragma once
#include "../Template/template.hpp"

struct LINE {
	/*
		ax + by + c = 0の直線

	*/

	ll a;
	ll b;
	ll c;
	friend auto operator<=>(const LINE&, const LINE&) = default;
	LINE(ll A, ll B, ll C) {
		a = A; b = B; c = C;
		normalization();
	}
	LINE(ll px, ll py, ll qx, ll qy) {
		a = qy - py;
		b = px - qx;
		c = qx * py - px * qy;

		normalization();
	}
	//表現の正規化 　以下をすることで同じ直線が一意に表現される
	void normalization() {
		//全部の最大公約数で割る
		ll g = gcd(a, gcd(b, c));
		a /= g, b /= g, c /= g;
		//傾きを正の向きに直す
		if (a < 0) a = -a, b = -b, c = -c;
		//傾き0なら、bを正にする
		if (a == 0 and b < 0) b = -b, c = -c;
	}
	//点が線上にある
	bool contains(ll x, ll y) const {
		return a * x + b * y + c == 0;
	}
	//点が上側or下側
	ll eval(ll x, ll y) const {
		return a * x + b * y + c;
	}

	//平行の関係
	bool is_parallel(const LINE& rhs) const {
		return a * rhs.b == b * rhs.a;
	}
	//同じ
	bool is_same(const LINE& rhs) const {
		return *this == rhs;
	}
	//垂直
	bool is_vertical(const LINE& rhs) const {
		return a * rhs.a + b * rhs.b == 0;
	}
	//向きベクトル
	pair<ll, ll> direction() const {
		return { -b,a };
	}
	// 法線ベクトル
	pair<ll, ll> normal() const {
		return { a,b };
	}
};
//垂直二等分線を得る
LINE get_canonical(ll px, ll py, ll qx, ll qy) {

	ll a = 2 * (qx - px);
	ll b = 2 * (qy - py);
	ll c = px * px + py * py - qx * qx - qy * qy;
	LINE l(a, b, c);
	return l;
}
