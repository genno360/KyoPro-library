#pragma once
#include "../Template/template.hpp"

//簡易連結判定
template<typename T>
inline bool simple_connection_judge(int N, vector<vector<T>>& V, int x, int y) {
	/*
		V[i][j]が別の値になったとき、残りが連結か ?

		***		***
		.*.	→	...		OK
		...		...

		**.		**.
		.*.	→	...		ダメ
		.**		.**

		.*.		.*.
		**.	→	*..		ダメ
		...		...

	*/
	const T& c = V[x][y];

	bool U = x > 0 && V[x - 1][y] == c;
	bool D = x + 1 < N && V[x + 1][y] == c;
	bool L = y > 0 && V[x][y - 1] == c;
	bool R = y + 1 < N && V[x][y + 1] == c;

	bool UL = x > 0 && y > 0 && V[x - 1][y - 1] == c;
	bool UR = x > 0 && y + 1 < N && V[x - 1][y + 1] == c;
	bool DL = x + 1 < N && y > 0 && V[x + 1][y - 1] == c;
	bool DR = x + 1 < N && y + 1 < N && V[x + 1][y + 1] == c;

	return U + D + L + R
		- (UL && U && L)
		- (UR && U && R)
		- (DL && D && L)
		- (DR && D && R) == 1;

}
