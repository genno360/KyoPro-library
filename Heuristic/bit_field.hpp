#pragma once
#include "../Template/template.hpp"

// 10x10 盤面を bitset<100> で管理する (旧版)
struct BIT_FIELD {
	// (x, y) は x 行目 y 列目。bit_shift_h(+n) で下へ、bit_shift_w(+n) で右へずらす
	const int AREA_H = 10;
	const int AREA_W = 10;
	bitset<100> allocated_blocks;
	bitset<100> LEFT_EDGE;
	bitset<100> RIGHT_EDGE;

	void init_mask() {
		rep(i, 0, 10) {
			LEFT_EDGE.set(i * 10 + 0);
			RIGHT_EDGE.set(i * 10 + 9);
		}
	}
	void set(int x, int y) {
		allocated_blocks.set(x * AREA_W + y);
	}
	void reset(int x, int y) {
		allocated_blocks.reset(x * AREA_W + y);
	}
	void bit_shift_h(int n) {
		if (n > 0) {
			allocated_blocks = allocated_blocks << n * AREA_W;
		}
		else {
			allocated_blocks = allocated_blocks >> -n * AREA_W;
		}
	}
	void bit_shift_w(int n) {
		if (n > 0) {
			rep(i, 0, n) {
				allocated_blocks &= ~RIGHT_EDGE;
				allocated_blocks <<= 1;
			}

		}
		else {
			rep(i, 0, -n) {
				allocated_blocks &= ~LEFT_EDGE;
				allocated_blocks >>= 1;
			}
		}
	}
	void bit_shift_hw(int h, int w) {
		bit_shift_h(h);
		bit_shift_w(w);
	}

	void print() {

		rep(i, 0, AREA_H) {
			rep(j, 0, AREA_W) {
				cout << allocated_blocks[i * AREA_W + j];
			}
			cout << el;
		}
	}
};

