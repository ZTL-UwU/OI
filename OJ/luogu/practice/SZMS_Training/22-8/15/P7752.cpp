#include <iostream>

const int MAX_N = 1e6 + 10;
const int MOD = 1e9 + 7;

int cycle[MAX_N];
int g[MAX_N];

int tot_cycle_size;
int n, k;

void get_cycle()
{
	cycle[0] = 1;
	cycle[1] = k;
	cycle[2] = (1LL * k * (k - 1)) % MOD;
	cycle[3] = (1LL * k * (k - 1) * (k - 2)) % MOD;

	for (int i = 4; i <= n; i++)
		cycle[i] = (1LL * cycle[i - 1] * (k - 2) + 1LL * cycle[i - 2] * (k - 1)) % MOD;
}

bool vis[MAX_N];
int size = 0;

int dfs(const int start, int u)
{
	if (u == start && size != 0)
		return size;

	if (!vis[g[u]])
	{
		vis[g[u]] = true;
		size++;
		const int res = dfs(start, g[u]);
		if (res)
			return res;
		vis[g[u]] = false;
		size--;
	}
	
	return 0;
}

int main()
{
//	std::freopen("paleta.in.8a", "r", stdin);

	std::cin >> n >> k;
	get_cycle();

	for (int i = 1; i <= n; i++)
		std::cin >> g[i];

	long long ans = 1;
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i])
		{
			size = 0;
			const int res = dfs(i, i);
			tot_cycle_size += res;
			ans = (ans * cycle[res]) % MOD;
		}
	}

	for (int i = 1; i <= n - tot_cycle_size; i++)
		ans = (ans * (k - 1)) % MOD;

	std::cout << ans;
	return 0;
}
