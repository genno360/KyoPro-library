#pragma once
#include "../Template/template.hpp"
#include "../Other/random.hpp"
#include "../Other/timer.hpp"

namespace ANNEALING {
	template<class T>
	bool temperature(
		double& turn,
		double& turn_max,
		T& old_score,
		T& new_score,
		double start_temp = 30.0,
		double end_temp = 2.0,
		bool is_minimizing = true// trueなら小さい方が良い
	) {
		double temp = start_temp + (end_temp - start_temp) * turn / turn_max;
		T score_diff = is_minimizing ? new_score - old_score : old_score - new_score;

		if (score_diff <= 0) return true;
		double probability = exp(-score_diff / temp);
		return random_real_0_1() < probability;
	}


	/*
	BURNクラス：焼きなまし法を行う
	*/
	template<class State, class Task, class Prob>
	class BURN {
	public:
		BURN(State& s, Task task, Prob prob, double tl = 1.95)
			: state(s), task(task), prob(prob), timeLimit(tl) {
		}
		double time;
		void run() {
			TIMER timer;
			ll loop = 0, adopt = 0;

			while ((time = timer.count()) < timeLimit) {
				if (task(state, time, timeLimit)) {
					adopt++;
				}
				loop++;
			}
			cerr << "loop=" << loop << " adopt=" << adopt << el;
		}

	private:
		State& state;
		Task task;
		Prob prob;
		double timeLimit;
	};
	//温度関数

	inline bool probability(double old_score, double new_score,
		double now, double limit) {
		return temperature(
			now, limit,
			old_score, new_score,
			30.0, 2.0,
			false	//小さいほうが良いスコアならtrue
		);
	};
	//焼きなまし法における現状態の管理を行う
	struct Annealing {
		int score_ = 0;

		void input() {

		}

		void make_first() {

		}

		int cale_score_all() {
			score_ = 0;
			return score_;
		}
		int cale_score() {
			int score = 0;
			return score;
		}
		void print() {

		}
		//bool operator<(const Annealing& other) const {
		//	return score_ < other.score_;
		//}
	};



	//焼きなまし法の1ループで行うこと
	bool task1(Annealing& s, double& time, double& timeLimit) {

		int new_score = 0;
		if (!probability(s.score_, new_score, time, timeLimit)) {

			return false;
		}

		return true;

	}
	bool task(Annealing& s, double& time, double& timeLimit) {

		return task1(s, time, timeLimit);

	};
	void solve_burn() {

		Annealing state;
		state.input();
		state.make_first();
		state.cale_score_all();
		BURN burn(
			state,
			task,
			probability,
			1.95
		);

		burn.run();
		state.print();
	}
}
