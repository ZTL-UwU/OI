#include <iostream>
#include <cstdio>

const int MAX_N = 5e5 + 10;
const int FAKE_ROOT = -1;
const int ROOT = 0;

std::vector<int> tree[MAX_N];
int val[MAX_N];

int heavy_son[MAX_N];
int tree_size[MAX_N];
int chain_top[MAX_N];
int father[MAX_N];
int new_id[MAX_N];
int depth[MAX_N];
int time_stamp;

void dfs1(int u)
{
	tree_size[u] = 1;
	heavy_son[u] = tree[u][0];

	for (std::size_t i = 0; i < tree[u].size(); i++)
	{
		int v = tree[u][i];
		if (v != fa[u])
		{
			fa[v] = u;
			depth[v] = depth[u] + 1;
			dfs1(v);
			tree_size[u] += tree_size[v];

			if (tree_size[v] > tree_size[heavy_son[u]])
				heavy_son[u] = v;
		}
	}
}

void dfs2(int u)
{
	
}

int main()
{
	std::freopen("lazy.in", "r", stdin);
	std::freopen("lazy.out", "w", stdout);

	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	int n;
	std::cin >> n;

	for (int i = 0; i < n; i++)
		std::cin >> val[i];

	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		std::cin >> u >> v;

		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	fa[ROOT] = FAKE_ROOT;
	depth[ROOT] = 0;
	dfs1(ROOT);
	dfs2();
	return 0;
}