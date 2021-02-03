#include <iostream>
#include <cstdio>

const int INF = 0x7fffffff;
const int MAX_N = 1e5 + 10;

int tree[MAX_N * 4];
int a[MAX_N];
int n, m;

void build(int l, int r, int k)
{
	if (l == r)
	{
		tree[k] = a[l];
		return;
	}

	int ls = k * 2;
	int rs = k * 2 + 1;
	int mid = (l + r) / 2;

	build(l, mid, ls);
	build(mid + 1, r, rs);
	
	tree[k] = std::min(tree[ls], tree[rs]);
}

void update(int l, int r, int k, int x, int val)
{
	if (l == x and r == x)
	{
		tree[k] = val;
		return;
	}

	int ls = k * 2;
	int rs = k * 2 + 1;
	int mid = (l + r) / 2;

	if (x <= mid)
		update(l, mid, ls, x, val);
	else
		update(mid + 1, r, rs, x, val);

	tree[k] = std::min(tree[ls], tree[rs]);
}

int query(int l, int r, int k, int x, int y)
{
	if (x <= l and r <= y)
		return tree[k];

	int ls = k * 2;
	int rs = k * 2 + 1;
	int mid = (l + r) / 2;

	int res1 = INF;
	int res2 = INF;
	if (x <= mid)
		res1 = query(l, mid, ls, x, y);
	if (y > mid)
		res2 = query(mid + 1, r, rs, x, y);

	return std::min(res1, res2);
}

int find_min(int x)
{
	int last_min = n;
	int min = x;

	while (true)
	{
		int new_min = query(1, n, 1, min, last_min);
		if (new_min >= min)
			return min;

		last_min = min;
		min = new_min;
	}
	
	return min;
}

int main()
{
	std::freopen("island.in", "r", stdin);
	std::freopen("island.out", "w", stdout);

	std::scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		std::scanf("%d", &a[i]);
	build(1, n, 1);

	for (int t = 0; t < m; t++)
	{
		int op;
		std::scanf("%d", &op);

		if (op == 1)
		{
			int x, y;
			std::scanf("%d %d", &x, &y);

			update(1, n, 1, x, y);
		}
		if (op == 2)
		{
			int x;
			std::scanf("%d", &x);

			int ans = find_min(x);
			std::printf("%d\n", ans);
		}
	}
	return 0;
}
