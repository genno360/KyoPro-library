#pragma once
#include "../Template/template.hpp"

//https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/union-find

class UNIONFIND
{
public:

	UNIONFIND() = default;

	explicit UNIONFIND(size_t n)
		: m_parents(n)
		, m_sizes(n, 1)
	{
		std::iota(m_parents.begin(), m_parents.end(), 0);
	}

	int find(int i) {
		if (m_parents[i] == i)
		{
			return i;
		}
		return (m_parents[i] = find(m_parents[i]));
	}
	void merge(int a, int b) {
		a = find(a);
		b = find(b);

		if (a != b)
		{
			if (m_sizes[a] < m_sizes[b])
			{
				std::swap(a, b);
			}

			m_sizes[a] += m_sizes[b];
			m_parents[b] = a;
		}
	}

	bool connected(int a, int b) {
		return (find(a) == find(b));
	}

	int size(int i) {
		return m_sizes[find(i)];
	}

private:

	std::vector<int> m_parents;
	std::vector<int> m_sizes;
};
