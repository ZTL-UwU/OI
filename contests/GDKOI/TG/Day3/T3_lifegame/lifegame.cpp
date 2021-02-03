#include <iostream>
#include <cstdio>
#include <vector>

const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int INF = 0x7fffffff;
const int BORDER_MAX = 1e4;
const int MOD = 998244353;
const int MAX_N = 20;

std::pair<int, int> input[MAX_N];
bool map[BORDER_MAX][BORDER_MAX];

bool check_alive(std::pair<int, int> p)
{
	int living = 0;

	for (int i = 0; i < 4; i++)
	{
		int xx = p.first + DIR[i][0];
		int yy = p.second + DIR[i][1];

		if (map[xx][yy])
			living++;
	}

	if (living % 2 == 1)
		return true;

	map[p.first][p.second] = false;
	return false;
}

int main()
{
	std::freopen("lifegame.in", "r", stdin);
	std::freopen("lifegame.out", "w", stdout);

	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	int n, l, r, type;
	std::cin >> n >> l >> r >> type;

	int min_x = INF;
	int max_x = -INF;
	int min_y = INF;
	int max_y = -INF;

	for (int i = 0; i < n; i++)
	{
		int x, y;
		std::cin >> x >> y;

		min_x = std::min(x, min_x);
		max_x = std::max(x, max_x);
		min_y = std::min(y, min_y);
		max_y = std::max(y, max_y);

		input[i] = std::pair<int , int>(x, y);
	}

	int delta_x = (BORDER_MAX - (max_x - min_x)) / 2;
	int delta_y = (BORDER_MAX - (max_y - min_y)) / 2;

	for (int i = 0; i < n; i++)
	{
		input[i].first += delta_x;
		input[i].second += delta_y;
		map[input[i].first][input[i].second] = true;
	}

	std::vector<std::pair<int, int> > alive;
	std::vector<std::pair<int, int> > new_alive;
	for (int i = 0; i < n; i++)
		alive.push_back(input[i]);

	long long int log_alive = 0;
	for (int time_stamp = 0; time_stamp <= r; time_stamp++)
	{
		if (time_stamp >= l)
			log_alive = (log_alive + alive.size()) % MOD;

		for (std::size_t i = 0; i < alive.size(); i++)
			if (check_alive(alive[i]))
				new_alive.push_back(alive[i]);

		for (std::size_t i = 0; i < alive.size(); i++)
		{
			std::pair<int, int> p = alive[i];

			for (int j = 0; j < 4; j++)
			{
				int xx = p.first + DIR[i][0];
				int yy = p.second + DIR[i][1];

				if ((not map[xx][yy]) and check_alive(std::pair<int, int>(xx, yy)))
				{
					new_alive.push_back(std::pair<int, int>(xx, yy));
					map[xx][yy] = true;
				}
			}
		}

		alive.clear();
		for (std::size_t i = 0; i < new_alive.size(); i++)
			alive.push_back(new_alive[i]);
		new_alive.clear();
	}

	log_alive = (log_alive + alive.size()) % MOD;
	std::cout << log_alive;
	return 0;
}
