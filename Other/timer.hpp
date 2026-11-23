#pragma once
#include "../Template/template.hpp"

/* 時間管理 */

class TIMER {
	chrono::system_clock::time_point start;
public:
	TIMER() : start(chrono::system_clock::now()) {}
	void reset() {
		start = chrono::system_clock::now();
	}
	double count() {
		chrono::duration<double> Time_ = chrono::system_clock::now() - start;
		return Time_.count();
	}

	bool is_under(double x) {
		return (this->count()) < x;
	}

};
