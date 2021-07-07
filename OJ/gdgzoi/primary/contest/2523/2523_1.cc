#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

const int MAX_N = 1e4 + 10;
const int INF = 0x7fffffff;

int n, m;
int point[MAX_N];
std::pair<int, int> building[MAX_N];
std::vector<std::pair<int, int>> building_new;

int check(int key)
{
    int res = 0;
    std::size_t p1 = 0;

    for (int p2 = 0; p2 < n; p2++)
    {
        while (p1 < building_new.size() && point[p2] > building_new[p1].first + key
               && point[p2] > building_new[p1].second + key)
            p1++;

        if (building_new[p1].first + key <= point[p2] && building_new[p1].second + key >= point[p2])
            res++;
    }

    return res;
}

int main()
{
    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
        std::cin >> point[i];
    for (int i = 0; i < m; i++)
        std::cin >> building[i].first >> building[i].second;

    std::sort(point, point + n);
    std::sort(building, building + m,
              [](std::pair<int, int> p1, std::pair<int, int> p2) -> bool
              {
                  if (p1.first == p2.first)
                      return p1.second < p2.second;
                  return p1.first < p2.first;
              });
    for (int i = 0; i < m; i++)
        if (i == m - 1 || building[i + 1].first != building[i].first)
            building_new.push_back(building[i]);

    const int l_border = point[0] - building[0].first;
    const int r_border = point[n - 1] - building[m - 1].second;

    int max_seen = -INF;
    int min_move = INF;
    for (int i = std::min(l_border, r_border); i <= std::max(l_border, r_border); i++)
    {
        const int res = check(i);
        if (res == max_seen)
            min_move = std::min(min_move, std::abs(i));
        else if (res > max_seen)
        {
            max_seen = res;
            min_move = std::abs(i);
        }
    }

    std::cout << min_move << " " << max_seen;
    return 0;
}