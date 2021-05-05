#include <iostream>
#include <vector>
#include <queue>

const int INF = 0x7fffffff;
const int MAX_N = 1e2;

struct node
{
    int v, w;
};

struct queue_data
{
    int x, l;
};

std::vector<node> g[MAX_N];
int mod = INF;

void SPFA() {}

int main()
{
    int T;
    std::cin >> T;

    for (int _i = 0; _i < T; _i++)
    {
        int n, m, t;
        std::cin >> n >> m >> t;

        for (int __i = 0; __i < m; __i++)
        {
            int u, v, w;
            std::cin >> u >> v >> w;

            if (u == 0 || v == 0)
                mod = w * 2;
            if (u == 0 && v == 0)
                mod = w;

            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        if (mod == INF)
            std::cout << "Impossible";
        else
        {
            SPFA();
        }
    }
    return 0;
}
