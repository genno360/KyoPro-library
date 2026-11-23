#pragma once
#include "../Template/template.hpp"

/*	乱数	*/
struct Xorshift128 {
	uint64_t x = 16354976620950309654ULL, y = 12985040979062584389ULL, z = 7179524487253565650ULL, w = 4967618042211634159ULL;
	inline uint64_t next() {
		uint64_t t = x ^ (x << 11);
		x = y; y = z; z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
	inline int next_int(int n) {
		return (int)(next() % (uint64_t)n);
	} inline double next_double()
	{
		return (next() >> 11) * (1.0 / 9007199254740992.0);
	}
} rng;

inline double random_real_0_1() {
	return rng.next_double();
}
inline int random_int_range(int a, int b) {
	return a + rng.next_int(b - a);
}
template<class T>
inline T random_pickup(const vector<T>& v) {
	return v[rng.next_int((int)v.size())];
}
template<class T>
inline void shuffle_vector(vector<T>& v) {
	for (int i = (int)v.size() - 1; i > 0; --i) {
		int j = rng.next_int(i + 1); // [0, i]
		std::swap(v[i], v[j]);
	}
}
