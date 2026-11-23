#pragma once
#include "../Template/template.hpp"
#include "../Other/random.hpp"
#include "../Other/timer.hpp"
#include "../DataStructure/persistent_stack.hpp"

namespace BEAMSEARCH {

	struct Beam {
		using ACTION = int;
		/*TODO:スコアが小さいほど良いかどうかを確認する*/
		bool LOWER_IS_BETTER = true;
		const int BEAM_WIDTH = 700;
		const int BEAM_TURN = 1000;	//必要ターン数見積もり(初期状態も含まれることに注意)

		//スコアが小さいほうが良いか?
		inline bool better(int a, int b) {
			if (LOWER_IS_BETTER) {
				return a < b;
			}
			else {
				return a > b;
			}
		}
		// スコアだけ計算して上位を選ぶために用いる仮ノード
		struct TemporaryNode {
			int score;
			uint64_t hash;
			int node_index;
			ACTION actions_;
			double rand; // タイブレーク用

			TemporaryNode(int score, uint64_t hash, int node_index, ACTION& actions_) :
				score(score), hash(hash), node_index(node_index), actions_(actions_) {
				rand = random_real_0_1();
			}
		};

		struct State {
			int score_;

			PersistentStack<ACTION> stack;// どの行動で来たか


			uint64_t hash_;

			State() {

			}

			bool isDone() const {
				return false;
			}

			void advance(const ACTION& action) {
				// 状態更新
				// score_ もここで更新

			}
			pair<int, uint64_t> try_move(const ACTION& action) const {
				//点数とハッシュを返す
				return { 0,0 };
			}
			vector<ACTION> legalActions() const {
				vector<ACTION> act;


				return act;
			}

			//bool operator<(const State& other) const {		//未使用
			//	return score_ > other.score_; // 降順
			//}
		};

		State make_first() {
			State state;
			return state;
		}

		void task() {

			TIMER timer;
			vector<State> cur, next;

			cur.reserve(BEAM_WIDTH);
			next.reserve(BEAM_WIDTH);
			vector<TemporaryNode> temp_nodes;
			temp_nodes.reserve(BEAM_WIDTH * 100);
			unordered_map<uint64_t, int> mp_index;

			cur.push_back(make_first());
			for (int turn = 0; turn < BEAM_TURN; turn++) {


				temp_nodes.clear();
				mp_index.clear();
				// --- 展開 ---
				rep(i, 0, cur.size()) {
					auto& st = cur[i];
					auto actions = st.legalActions();
					for (auto action : actions) {
						auto [next_score, next_hash] = st.try_move(action);
						if (mp_index.count(next_hash)) {
							int idx = mp_index[next_hash];

							// 既存より良いなら更新
							if (better(next_score, temp_nodes[idx].score)) {
								temp_nodes[idx] = { next_score, next_hash, (int)i, action };
							}
						}
						else {
							mp_index[next_hash] = temp_nodes.size();
							temp_nodes.emplace_back(next_score, next_hash, i, action);
						}
					}
				}


				// --- 上位K件 ---

				int node_size = temp_nodes.size();
				// 候補がビーム幅より多いなら上位beam_width個を選ぶ
				if (node_size > BEAM_WIDTH) {
					nth_element(temp_nodes.begin(), temp_nodes.begin() + BEAM_WIDTH, temp_nodes.end(),
						[this](TemporaryNode& n1, TemporaryNode& n2) {
						if (n1.score == n2.score) {
							return n1.rand < n2.rand;
						}
						/*	TODO：scoreが大きいほど良いのか、小さいほど良いのか確認 */
						return better(n1.score, n2.score);
					});
				}
				for (int i = 0; i < min(BEAM_WIDTH, node_size); i++) {
					int index = temp_nodes[i].node_index;
					next.emplace_back(cur[index]);
					next.back().advance(temp_nodes[i].actions_);
					next.back().stack = next.back().stack.push(temp_nodes[i].actions_);
					// 必要ならスコアとハッシュ値を確認
					//assert(next.back().score_ == temp_nodes[i].score);
					//assert(next.back().hash_ == temp_nodes[i].hash);
				}
				// --- 終了判定 ---
				// 終了した状態があれば、その中で最もスコアの良いものの行動列を復元する
				vector<int> doned_index;
				for (int i = 0; i < (int)next.size(); i++) {
					if (next[i].isDone()) doned_index.push_back(i);
				}
				if (!doned_index.empty()) {
					auto ite = min_element(doned_index.begin(), doned_index.end(), [&](int n1, int n2) {
						return better(next[n1].score_, next[n2].score_);
					});

					int i = *ite;

					vector<ACTION> ans = next[i].stack.to_vector();
					// TODO: ans を出力する

					return;
				}
				// --- 入れ替え ---
				swap(cur, next);
				next.clear();
			}

		}
	};
}
