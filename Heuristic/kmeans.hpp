#pragma once
#include "../Template/template.hpp"

template <class T>
void kMeans(						//kmeans法でクラスタリング
	const vector<pair<T, T>>& pts,	//座標
	vector<int>& cluster_id,		//クラスタ番号　予め適当に割り振る
	int K,							//クラスタ数
	int max_iterations = 100		//最大反復（繰り返し）回数 数百程度で十分
) {
	int N = pts.size();
	assert((int)cluster_id.size() == N);

	vector<pair<double, double>> centroid(K);
	vector<int> cnt(K);

	for (int iter = 0; iter < max_iterations; iter++) {
		// --- 重心計算 ---
		fill(centroid.begin(), centroid.end(), make_pair(0.0, 0.0));
		fill(cnt.begin(), cnt.end(), 0);

		for (int i = 0; i < N; i++) {
			int c = cluster_id[i];
			assert(0 <= c && c < K);
			centroid[c].first += pts[i].first;
			centroid[c].second += pts[i].second;
			cnt[c]++;
		}

		for (int k = 0; k < K; k++) {
			if (cnt[k] == 0) {
				// 空クラスタ → ランダム点を重心に
				int i = rand() % N;
				centroid[k] = {
					(double)pts[i].first,
					(double)pts[i].second
				};
			}
			else {
				centroid[k].first /= cnt[k];
				centroid[k].second /= cnt[k];
			}
		}

		// --- 再割当 ---
		bool changed = false;
		for (int i = 0; i < N; i++) {
			double best = 1e100;
			int best_k = -1;
			for (int k = 0; k < K; k++) {
				double dx = pts[i].first - centroid[k].first;
				double dy = pts[i].second - centroid[k].second;
				double d = dx * dx + dy * dy;
				if (d < best) {
					best = d;
					best_k = k;
				}
			}
			if (cluster_id[i] != best_k) {
				cluster_id[i] = best_k;
				changed = true;
			}
		}

		if (!changed) break;
	}
}
template <class T>
void kMeansWithSizes(						//kmeans法でクラスタリング クラスタサイズを指定できる
	const vector<pair<T, T>>& pts,			//座標
	vector<int>& cluster_id,				//クラスタ番号　予め割り振りたい数だけ割り振る
	int K,									//クラスタ数
	int max_iterations = 100				//最大反復（繰り返し）回数 数百程度で十分
) {
	int N = pts.size();
	assert((int)cluster_id.size() == N);

	vector<pair<double, double>> centroid(K);
	vector<int> cnt(K);

	for (int iter = 0; iter < max_iterations; iter++) {
		// --- 重心計算（そのまま） ---
		fill(centroid.begin(), centroid.end(), make_pair(0.0, 0.0));
		fill(cnt.begin(), cnt.end(), 0);

		for (int i = 0; i < N; i++) {
			int c = cluster_id[i];
			centroid[c].first += pts[i].first;
			centroid[c].second += pts[i].second;
			cnt[c]++;
		}
		for (int k = 0; k < K; k++) {
			centroid[k].first /= cnt[k];
			centroid[k].second /= cnt[k];
		}

		// --- サイズ不変 swap ---
		bool changed = false;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				int ci = cluster_id[i];
				int cj = cluster_id[j];
				if (ci == cj) continue;

				auto dist = [&](int p, int c) {
					double dx = pts[p].first - centroid[c].first;
					double dy = pts[p].second - centroid[c].second;
					return dx * dx + dy * dy;
				};

				double delta =
					dist(i, cj) + dist(j, ci)
					- dist(i, ci) - dist(j, cj);

				if (delta < 0) {
					swap(cluster_id[i], cluster_id[j]);
					changed = true;
				}
			}
		}

		if (!changed) break;
	}
}
