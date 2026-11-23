#pragma once
#include "../Template/template.hpp"

template<typename T>
double euclid(T a, T b) {
	ll dx = a.first - b.first;
	ll dy = a.second - b.second;
	return sqrt(dx * dx + dy * dy);
}
template<typename T>
double euclid(T ax, T ay, T bx, T by) {
	ll dx = ax - bx;
	ll dy = ay - by;
	return sqrt(dx * dx + dy * dy);
}
template<typename T>
T getDistanceSq(T x1, T y1, T x2, T y2) {
	T dx = x1 - x2;
	T dy = y1 - y2;
	return dx * dx + dy * dy;
}

template<typename T>
ll manhattan(T ax, T ay, T bx, T by) {
	return abs(ax - bx) + abs(ay - by);
}
inline bool isInArea(int a, int b, int H, int W) {
	return a >= 0 && b >= 0 && a < H && b < W;
}
