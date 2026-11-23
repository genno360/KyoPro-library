#pragma once
#include "../Template/template.hpp"

// 行動を復元する永続stack
//https://jetbead.github.io/AtCoderHeuristicContestMemo/Library/persistent_stack.html
template <class T>
class PersistentStack {
public:
	struct History {
		T v;
		shared_ptr<History> parent;
		History(const T& v, shared_ptr<History> parent) : v(v), parent(parent) {}
	};

	PersistentStack() : head(nullptr) {}
	PersistentStack(shared_ptr<History> head) : head(head) {}
	bool empty() const {
		return head == nullptr;
	}
	T top() {
		return head->v;
	}
	PersistentStack push(const T& v) {
		return PersistentStack(make_shared<History>(v, head));
	}
	PersistentStack pop() {
		return PersistentStack(head->parent);
	}
	std::vector<T> to_vector() const {
		std::vector<T> result;
		for (PersistentStack cur = *this; !cur.empty(); cur = cur.pop()) {
			result.push_back(cur.top());
		}
		std::reverse(result.begin(), result.end());
		return result;
	}
private:
	shared_ptr<History> head;
};
