#include <iostream>
#include <vector>

const int INF = 0x7fffffff;
const int MAX_N = 2e3;

int map[MAX_N][MAX_N];
std::vector<int> l[MAX_N];
std::vector<int> r[MAX_N];
int l_id[MAX_N];
int r_id[MAX_N];
int length[MAX_N];

int minn = INF;
int dis[MAX_N];
int fa[MAX_N];

inline int find(int x)
{
    if (fa[x] == x)
        return x;

    int last = fa[x];
    fa[x] = find(fa[x]);
    dis[x] += dis[last];
    return fa[x];
}

inline void check(int x, int y)
{
    int fa_x = find(x);
    int fa_y = find(y);

    if (fa_x != fa_y)
    {
        fa[fa_x] = fa_y;
        dis[x] = dis[y] + map[x][y];
    }
    else
        minn = std::min(minn, dis[x] + dis[y] + map[x][y]);
}

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < MAX_N; i++)
        for (int j = 0; j < MAX_N; j++)
            map[i][j] = INF;

    for (int i = 0; i < n; i++)
    {
        int id, n1, n2;
        std::cin >> id;
        std::cin >> length[id] >> n1 >> n2;
        for (int j = 0; j < n1; j++)
        {
            int id1;
            std::cin >> id1;
            l[id].push_back(id1);
        }
        for (int j = 0; j < n2; j++)
        {
            int id1;
            std::cin >> id1;
            r[id].push_back(id1);
        }
    }

    int node_id = 0;
    for (int i = 1; i <= n; i++)
    {
        if (l_id[i] == 0)
            l_id[i] = ++node_id;
        if (r_id[i] == 0)
            r_id[i] = ++node_id;
        map[l_id[i]][r_id[i]] = std::min(map[l_id[i]][r_id[i]], length[i]);
        map[r_id[i]][l_id[i]] = std::min(map[r_id[i]][l_id[i]], length[i]);

        for (auto v : l[i])
        {
            bool flag = false;
            for (auto vv : l[v])
            {
                if (vv == i)
                {
                    l_id[v] = l_id[i];
                    flag = true;
                    break;
                }
            }

            if (not flag)
            {
                for (auto vv : r[v])
                {
                    if (vv == i)
                    {
                        r_id[v] = l_id[i];
                        break;
                    }
                }
            }
        }

        for (auto v : r[i])
        {
            bool flag = false;
            for (auto vv : l[v])
            {
                if (vv == i)
                {
                    l_id[v] = r_id[i];
                    flag = true;
                    break;
                }
            }

            if (not flag)
            {
                for (auto vv : r[v])
                {
                    if (vv == i)
                    {
                        r_id[v] = r_id[i];
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < MAX_N; i++)
        fa[i] = i;

    for (int i = 1; i <= node_id; i++)
        for (int j = 1; j <= i; j++)
            if (map[i][j] != INF)
                check(i, j);

    std::cout << minn;
    return 0;
}