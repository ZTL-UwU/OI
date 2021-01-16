#include <algorithm>
#include <iostream>
#include <vector>

const int INF = 0x7fffffff;
const int MAX_N = 2e3 + 10;

struct e
{
    int u;
    int v;
    int w;
};

std::vector<e> edge;
int fa[MAX_N];

inline int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

inline void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);

    fa[fx] = fy;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        edge.push_back((e){u, v, w});
    }

    std::sort(edge.begin(), edge.end(), [](e a, e b) { return a.w < b.w; });

    int minn = INF;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < MAX_N; j++)
            fa[j] = j;

        for (int j = i; j < m; j++)
        {
            merge(edge[j].u, edge[j].v);

            if (find(1) == find(n))
            {
                minn = std::min(minn, edge[j].w - edge[i].w);
                break;
            }
        }
    }

    std::cout << minn;
    return 0;
}