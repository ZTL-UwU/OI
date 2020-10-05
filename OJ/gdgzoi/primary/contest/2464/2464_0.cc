#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

struct data
{
    int to;
    int val;
};

const int INF = 0x7fffffff;
const int MAXN = 1e4;
std::vector<data> g[MAXN];
bool used[MAXN][MAXN];
bool flag;

inline void dfs(int u, int end, int end_val, int val)
{
    if (!flag)
        return;

    if (u == end)
    {
        if (val != end_val)
            flag = false;
        return;
    }

    u++;
    for (auto v : g[u])
        if (v.to <= end)
            dfs(v.to, end, end_val, val + v.val);
}

int main()
{
    freopen("./2464_0_large.in", "r", stdin);

    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;
    while (T--)
    {
        for (int i = 0; i < MAXN; i++)
            g[i].clear();
        std::memset(used, 0, sizeof(used));

        int n, m;
        std::cin >> n >> m;

        flag = true;
        for (int i = 0; i < m; i++)
        {
            int start, end, val;
            std::cin >> start >> end >> val;
            if (used[start][end])
                flag = false;
            used[start][end] = true;

            g[start].push_back((data){end, val});
        }

        if (flag)
        {
            for (int i = 1; i <= n; i++)
            {
                int max_len = -1;
                int end_val;
                for (auto v : g[i])
                {
                    if (v.to > max_len)
                    {
                        max_len = v.to;
                        end_val = v.val;
                    }
                }

                flag = true;
                dfs(i - 1, max_len, end_val, 0);

                if (!flag)
                    break;
            }
        }

        std::cout << std::boolalpha << flag << "\n";
    }
    return 0;
}