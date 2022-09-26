#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

const int MAX_N = 2e5 + 10;
const int INF = 0x7fffffff;

std::vector<int> g[MAX_N];
bool inque[MAX_N];
int dis1[MAX_N];
int dis2[MAX_N];
int s[MAX_N];

void spfa(int start)
{
    for (int i = 0; i < MAX_N; i++)
        start == 1 ? dis1[i] = INF : dis2[i] = INF;

    std::queue<int> q;
    q.push(start);
    inque[start] = true;
    start == 1 ? dis1[start] = 0 : dis2[start] = 0;

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();
        inque[u] = false;

        for (int v : g[u])
        {
            if (start == 1 ? dis1[v] > dis1[u] + 1 : dis2[v] > dis2[u] + 1)
            {
                start == 1 ? dis1[v] = dis1[u] + 1 : dis2[v] = dis2[u] + 1;
                if (!inque[v])
                {
                    q.push(v);
                    inque[v] = true;
                }
            }
        }
    }
}

int main()
{
    int n, m, k;
    std::cin >> n >> m >> k;

    for (int i = 0; i < k; i++)
        std::cin >> s[i];

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    spfa(1);
    spfa(n);

    std::sort(s, s + k, [](int a, int b) { return dis1[a] < dis1[b]; });

    int ans = -INF;
    for (int i = 0; i < k - 1; i++)
        ans = std::max(ans, dis1[s[i]] + dis2[s[i + 1]] + 1);
    ans = std::min(ans, dis1[n]);
    std::cout << ans;
    return 0;
}