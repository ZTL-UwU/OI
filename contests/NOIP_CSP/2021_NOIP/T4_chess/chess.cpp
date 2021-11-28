#include <iostream>
#include <cstring>
#include <cstdio>

const int MAX_N = 2e3 + 10;

struct piece
{
	int col;
	int lv = -1;
	int x;
	int y;
};

int n, m, q;
int up[MAX_N][MAX_N];
int down[MAX_N][MAX_N];
int left[MAX_N][MAX_N];
int right[MAX_N][MAX_N];
piece map[MAX_N][MAX_N];

bool vis[MAX_N][MAX_N];
int cnt;

void dfs_init(int x, int y)
{
	std::memset(vis, 0, sizeof(vis));
	vis[x][y] = true;
	cnt = 0;
}

void dfs(int x, int y)
{
	if (x < 0 || y < 0 || vis[x][y])
		return;
	cnt++;

	if (right[x][y] == 3 && (map[x][y + 1].lv == -1 || map[x][y + 1].col != map[x][y].col && map[x][y + 1].lv <= map[x][y].lv))
		dfs(x, y + 1);
	if (left[x][y] == 3 && (map[x][y - 1].lv == -1 || map[x][y - 1].col != map[x][y].col && map[x][y - 1].lv <= map[x][y].lv))
		dfs(x, y - 1);
	if (up[x][y] == 3 && (map[x - 1][y].lv == -1 || map[x - 1][y].col != map[x][y].col && map[x - 1][y].lv <= map[x][y].lv))
		dfs(x - 1, y);
	if (down[x][y] == 3 && (map[x + 1][y].lv == -1 || map[x + 1][y].col != map[x][y].col && map[x + 1][y].lv <= map[x][y].lv))
		dfs(x + 1, y);
}

int solve(piece p)
{
	int res = 0;
	if (right[p.x][p.y] == 1 && (map[p.x][p.y + 1].lv == -1 || map[p.x][p.y + 1].col != p.col && map[p.x][p.y + 1].lv <= p.lv))
		res++;
	if (right[p.x][p.y] == 2)
	{
		for (int i = p.y; i < m - 1; i++)
		{
			if (map[p.x][i].lv != -1 && (map[p.x][i + 1].col == p.col || map[p.x][i + 1].lv > p.lv))
				break;
			if (right[p.x][i] == 2)
				res++;
		}
	}
	if (right[p.x][p.y] == 3)
	{
		dfs_init(p.x, p.y);
		dfs(p.x, p.y);
		res += cnt;
	}

//=====================================================================================================================

	if (left[p.x][p.y] == 1 && (map[p.x][p.y - 1].lv == -1 || map[p.x][p.y - 1].col != p.col && map[p.x][p.y - 1].lv <= p.lv))
		res++;
	if (left[p.x][p.y] == 2)
	{
		for (int i = p.y; i < m - 1; i++)
		{
			if (map[p.x][i].lv != -1 && (map[p.x][i - 1].col == p.col || map[p.x][i - 1].lv > p.lv))
				break;
			if (left[p.x][i] == 2)
				res++;
		}
	}
	if (left[p.x][p.y] == 3)
	{
		dfs_init(p.x, p.y);
		dfs(p.x, p.y);
		res += cnt;
	}

//=====================================================================================================================

	if (up[p.x][p.y] == 1 && (map[p.x - 1][p.y].lv == -1 || map[p.x - 1][p.y].col != p.col && map[p.x - 1][p.y].lv <= p.lv))
		res++;
	if (up[p.x][p.y] == 2)
	{
		for (int i = p.y; i < m - 1; i++)
		{
			if (map[p.x][i].lv != -1 && (map[p.x - 1][i].col == p.col || map[p.x - 1][i].lv > p.lv))
				break;
			if (up[p.x][i] == 2)
				res++;
		}
	}
	if (up[p.x][p.y] == 3)
	{
		dfs_init(p.x, p.y);
		dfs(p.x, p.y);
		res += cnt;
	}

//=====================================================================================================================

	if (down[p.x][p.y] == 1 && (map[p.x + 1][p.y].lv == -1 || map[p.x + 1][p.y].col != p.col && map[p.x + 1][p.y].lv <= p.lv))
		res++;
	if (down[p.x][p.y] == 2)
	{
		for (int i = p.y; i < m - 1; i++)
		{
			if (map[p.x][i].lv != -1 && (map[p.x + 1][i].col == p.col || map[p.x + 1][i].lv > p.lv))
				break;
			if (down[p.x][i] == 2)
				res++;
		}
	}
	if (down[p.x][p.y] == 3)
	{
		dfs_init(p.x, p.y);
		dfs(p.x, p.y);
		res += cnt;
	}

	return res;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	std::freopen("chess.in", "r", stdin);
	std::freopen("chess.out", "w", stdout);

	int t;
	std::cin >> t;

	for (int _i = 0; _i < t; _i++)
	{
		std::cin >> n >> m >> q;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m - 1; j++)
			{
				std::cin >> right[i][j];
				left[i][j + 1] = right[i][j];
			}
		}

		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < m; j++)
			{
				std::cin >> down[i][j];
				up[i + 1][j] = down[i][j];
			}
		}

		for (int i = 0; i < q; i++)
		{
			piece p;
			std::cin >> p.col >> p.lv >> p.x >> p.y;
			std::cout << solve(p) << "\n";
			map[p.x][p.y] = p;
		}

		for (int i = 0; i < MAX_N; i++)
		{
			for (int j = 0; j < MAX_N; j++)
			{
				map[i][j].col = 0;
				map[i][j].lv = -1;
			}
		}
	}

	return 0;
}
