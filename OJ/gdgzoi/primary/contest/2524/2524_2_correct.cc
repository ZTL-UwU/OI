#include <cstddef>
#include <unordered_map>
#include <iostream>
#include <vector>

const int INF = 0x7fffffff;
const int MAX_N = 5e5 + 10;

std::unordered_map<int, int> map;
std::vector<int> pos[MAX_N];
int tot = 0;
int ans = INF;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    int a;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a;

        if (!map[a])
        {
            map[a] = ++tot;
            pos[tot].push_back(i);
        }
        else
        {
            const int key = map[a];
            ans = std::min(ans, i - pos[key].back());
            pos[key].push_back(i);
        }
    }

    for (int _i = 0; _i < m; _i++)
    {
        int x, y;
        std::cin >> x >> y;

        const int key_x = map[x];
        const int key_y = map[y];

        if (ans == 1 || x == y)
            std::cout << ans << '\n';
        else if (map[x] && pos[key_x].size() && (!map[y] || !pos[key_y].size()))
        {
            map[y] = key_x;
            map[x] = ++tot;
            std::cout << ans << '\n';
        }
        else
        {
            std::size_t p1 = 0;
            std::size_t p2 = 0;

            std::vector<int> tmp;
            for (std::size_t i = 0; i < pos[key_x].size() + pos[key_y].size(); i++)
            {
                if (p1 == pos[key_x].size())
                    tmp.push_back(pos[key_y][p2++]);
                else if (p2 == pos[key_y].size())
                    tmp.push_back(pos[key_x][p1++]);
                else if (pos[key_x][p1] < pos[key_y][p2])
                    tmp.push_back(pos[key_x][p1++]);
                else if (pos[key_x][p1] > pos[key_y][p2])
                    tmp.push_back(pos[key_y][p2++]);
                if (i != 0)
                    ans = std::min(ans, tmp[i] - tmp[i - 1]);
            }

            pos[key_y] = tmp;
            pos[key_x].clear();
            std::cout << ans << "\n";
        }
    }
    return 0;
}
