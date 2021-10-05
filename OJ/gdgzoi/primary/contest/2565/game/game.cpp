#include <unordered_map>
#include <iostream>
#include <cstring>
#include <vector>

const int MAX_N = 4e3 + 50;

using pii = std::pair<int, int>;

std::unordered_map<std::string, int> id;
int id_cnt;

std::vector<int> g[MAX_N];
std::vector<int> nums;
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

pii dfs(int u)
{
    pii res{0, 0};
    if (color[u] == -1)
        res.first = 1;
    else
        res.second = 1;

    for (auto v : g[u])
    {
        if (color[v] == 0)
        {
            color[v] = (color[u] == 1 ? -1 : 1);
            const auto ret = dfs(v);
            res.first += ret.first;
            res.second += ret.second;
        }
    }

    return res;
}

bool dfs2(std::size_t step, std::size_t last, int sum, const std::size_t size)
{
    if (step == size / 2)
        return 2 * sum == tot;

    for (std::size_t i = last + 1; i < size; i++)
    {
        const bool ret = dfs2(step + 1, i, sum + nums[i], size);
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
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        int n, m;
        std::cin >> n >> m;

        init();

        for (int _i = 0; _i < m; _i++)
        {
            std::string u, v;
            std::cin >> u >> v;

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

            g[id[u]].emplace_back(id[v]);
            g[id[v]].emplace_back(id[u]);
        }

        if (2 * n - id_cnt >= 2)
        {
            std::cout << "NO\n";
            continue;
        }

        for (int i = 1; i <= id_cnt; i++)
        {
            if (color[i] == 0)
            {
                color[i] = 1;
                const auto ret = dfs(i);
                tot += ret.first + ret.second;
                nums.emplace_back(ret.first);
                nums.emplace_back(ret.second);
            }
        }

        const bool ret = dfs2(0, -1, 0, nums.size());
        std::cout << (ret ? "YES" : "NO") << "\n";
    }

    return 0;
}
