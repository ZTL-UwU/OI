#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_N = 5e5 + 10;
std::vector<int> g[MAX_N];
int a[MAX_N];
int d[MAX_N];
int n, m;
int ans;

// m == 1
void task2(int u, int fa)
{
	for (int v : g[u])
	{
		if (v != fa)
		{
			if (a[u] != 0 && a[v] != 0)
				ans++;
			task2(v, u);
		}
	}
}

// 链
void task3(int u, int fa)
{
	for (int v : g[u])
	{
		if (v != fa)
		{
			ans += std::min(a[u], a[v]);
			task3(v, u);
		}
	}
}

// 菊花
std::vector<int> t4_son;
void task4(int u)
{
	for (int v : g[u])
		t4_son.push_back(a[v]);
	std::sort(t4_son.begin(), t4_son.end(), std::greater<int>());
	for (int i = 0; i < n - 1; i++)
	{
		if (i < (n - 1) / 2 && t4_son[i] > a[u])
			ans += t4_son[i];
		else
			ans += std::min(t4_son[i], a[u]);
	}
}

int main()
{
	std::cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
		
	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		std::cin >> u >> v;

		g[u].push_back(v);
		g[v].push_back(u);
		d[u]++;
		d[v]++;
	}
	
	bool is_task4 = false;
	int task4_root;
	int is_task3 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (d[i] == n - 1)
		{
			is_task4 = true;
			task4_root = i;
			break;
		}
		if (d[i] == 2)
			is_task3++;
	}

	if (m == 0)
		ans = 0;
	else if (m == 1)
		task2(1, 0);
	else if (is_task3 == n - 2)
		task3(1, 0);
	else if (task4)
		task4(task4_root);
	
	std::cout << ans;
	return 0;
}