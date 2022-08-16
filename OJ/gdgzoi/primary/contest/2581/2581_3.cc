#include <functional>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>

const int DIR[4][2] = {{1, -2}, {2, -1}, {2, 1}, {1, 2}};
const int MOD = 998244353;

unsigned long long dp[100000];
std::string map;
int n, q;

int bfs(int s, int t)
{
    if (map[s] == '#')
        return 0;

    std::memset(dp, 0, sizeof(dp));
    dp[s] = 1;

    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    q.push(s);

    while (!q.empty())
    {
        const int u = q.top();
        q.pop();

        const int x = u / n;
        const int y = u % n;

        for (int i = 0; i < 4; i++)
        {
            const int xx = x + DIR[i][0];
            const int yy = y + DIR[i][1];
            const int v = xx * n + yy;

            if (xx >= 0 && yy >= 0 && yy < n && v < map.size() && map[v] != '#')
            {
                if (!dp[v])
                    q.push(v);
                dp[v] = (dp[u] + dp[v]) % MOD;
            }
        }
    }

    return dp[map.size() - n + t];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> q;

    for (int _i = 0; _i < q; _i++)
    {
        std::string op;
        std::cin >> op;

        if (op == "Add")
        {
            std::string map_line;
            std::cin >> map_line;

            map = map + map_line;
        }
        else if (op == "Del")
            map = map.substr(n);
        else if (op == "Que")
        {
            int s, t;
            std::cin >> s >> t;
            s--;
            t--;

            if (map.size() <= n)
                std::cout << "0\n";
            else
                std::cout << bfs(s, t) << "\n";
        }
    }

    return 0;
}
