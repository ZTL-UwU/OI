#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <map>

const int MAX_N = 1e5 + 10;

struct operation
{
	int op;
	int l;
	int r;
	int x;
};

std::map<std::pair<int, int>, std::size_t> memory_hash;
std::map<std::pair<int, int>, int> input_hash;
std::vector<std::vector<int> > memory;
std::vector<operation> input;
int a[MAX_N];

inline void sink(int x, int n, std::vector<int> &heap)
{
	while (x * 2 <= n)
	{
		int y = x * 2;

		if (y < n and heap[y + 1] < heap[y])
			++y;
		if (heap[y] > heap[x])
			break;

		std::swap(heap[x], heap[y]);
		x = y;
	}
}

inline void build_heap(int l, int r, std::vector<int> &heap)
{
	for (int i = 0; i < r - l + 1; ++i)
		heap[i + 1] = a[l + i];

	for (int i = r - l + 1; i >= 1; --i)
		sink(i, r - l + 1, heap);
}

int main()
{
	std::freopen("heap.in", "r", stdin);
	std::freopen("heap.out", "w", stdout);

	std::vector<int> nothing;
	memory.push_back(nothing);
	
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	int n, q;
	std::cin >> n >> q;

	for (int i = 1; i <= n; ++i)
		std::cin >> a[i];

	for (int t = 0; t < q; ++t)
	{
		int op, l, r, x;
		std::cin >> op >> l >> r >> x;

		input.push_back((operation){op, l, r, x});
		++input_hash[std::pair<int, int>(l, r)];
	}

	for (std::size_t i = 0; i < input.size(); ++i)
	{
		int op = input[i].op;
		int l = input[i].l;
		int r = input[i].r;
		std::pair<int, int> p = std::pair<int, int>(l, r);
		int x = input[i].x;

		std::vector<int> heap;
		heap.resize(r - l + 2);

		if (input_hash[p] != 0)
		{
			if (memory_hash[p] == 0)
			{
				build_heap(l, r, heap);
				memory.push_back(heap);
				memory_hash[p] = memory.size() - 1;
			}
			else
			{
				heap = memory[memory_hash[p]];
			}
		}
		else
		{
			build_heap(l, r, heap);
		}

		if (op == 1)
			std::cout << heap[x] << '\n';
		if (op == 2)
		{
			for (int j = 1; j <= r - l + 1; ++j)
			{
				if (heap[j] == x)
				{
					std::cout << j << '\n';
					break;
				}
			}
		}
	}

	return 0;
}
