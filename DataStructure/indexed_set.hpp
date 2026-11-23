#pragma once
#include "../Template/template.hpp"

class IndexedSet {
public:
	IndexedSet(int N) {
		index.assign(N, -1);
	}

	bool add(int a) {
		if (index[a] != -1) return false;

		index[a] = arr.size();
		arr.push_back(a);
		return true;
	}
	bool remove(int a) {
		if (index[a] == -1) return false;

		int pos = index[a];
		int last = arr.back();

		arr[pos] = last;
		index[last] = pos;

		arr.pop_back();
		index[a] = -1;
		return true;
	}
	bool contains(int a) const {
		return index[a] != -1;
	}

	int position(int a) const {
		return index[a];
	}

	int operator[](int i) const {
		return arr[i];
	}

	int size() const {
		return arr.size();
	}

private:
	vector<int> arr;    // 実体（順序付き）
	vector<int> index;  // 値 → arr 内の位置
};
