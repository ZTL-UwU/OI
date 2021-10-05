#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

const int MAX_N = 4e3 + 50;

map<string, int> id;
int id_cnt;

vector<int> g[MAX_N];
vector<int> nums;
int tot;

int color[MAX_N];

void init()
{
    id.clear();
    id_cnt = 0;
    for (int _i = 0; _i < MAX_N; _i++)
        g[_i].clear();
    nums.clear();
    tot = 0;
    memset(color, 0, sizeof(color));
}

pair<int, int> dfs(int u)
{
    pair<int, int> res(0, 0);
    if (color[u] == -1)
        res.first = 1;
    else
        res.second = 1;

    for (size_t i = 0; i < g[u].size(); i++)
    {
        const int v = g[u][i];

        if (color[v] == 0)
        {
            color[v] = (color[u] == 1 ? -1 : 1);
            const pair<int, int> ret = dfs(v);
            res.first += ret.first;
            res.second += ret.second;
        }
    }

    return res;
}

bool dfs2(size_t step, size_t last, int sum, const size_t size, const bool diff)
{
    if (step == size / 2)
    {
        if (diff)
            return (2 * sum - 1 == tot || 2 * sum + 1 == tot);
        return 2 * sum == tot;
    }

    for (size_t i = last + 1; i < size; i++)
    {
        const bool ret = dfs2(step + 1, i, sum + nums[i], size, diff);
        if (ret)
            return true;
    }

    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        int n, m;
        cin >> n >> m;

        init();

        bool flag = true;
        for (int _i = 0; _i < m; _i++)
        {
            string u, v;
            cin >> u >> v;

            if (!id[u])
            {
                id_cnt++;
                id[u] = id_cnt;
            }
            if (!id[v])
            {
                id_cnt++;
                id[v] = id_cnt;
            }

            g[id[u]].push_back(id[v]);
            g[id[v]].push_back(id[u]);
        }

        if (2 * n - id_cnt >= 2)
        {
            cout << "NO\n";
            continue;
        }

        for (int i = 1; i <= id_cnt; i++)
        {
            if (color[i] == 0)
            {
                color[i] = 1;
                const pair<int, int> ret = dfs(i);
                tot += ret.first + ret.second;
                nums.push_back(ret.first);
                nums.push_back(ret.second);
            }
        }

        const bool ret = dfs2(0, -1, 0, nums.size(), 2 * n - id_cnt == 1 ? true : false);
        cout << (ret ? "YES" : "NO") << "\n";
    }

    return 0;
}
