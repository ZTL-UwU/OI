#include <iostream>
#include <vector>
#include <queue>

const int MAX_N = 1e5 + 10;

int bin_table[] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144};
std::vector<int> g[MAX_N];
bool vis[MAX_N];
int ans;

inline int ceil_bin(int num)
{
    for (int i = 0; i < 20; i++)
        if (bin_table[i] >= num)
            return i >= 1 ? i - 1 : i;
    return 0;
}

inline void bfs(int S)
{
    std::queue<int> q;
    q.push(S);
    vis[S] = true;

    while (not q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = true;

        int son = 0;
        for (auto v : g[u])
        {
            if (!vis[v])
            {
                q.push(v);
                son++;
            }
        }

        ans += son + ceil_bin(son);
    }
}

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    bfs(1);

    std::cout << ans;
    return 0;
}