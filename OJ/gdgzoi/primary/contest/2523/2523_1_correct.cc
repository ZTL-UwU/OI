#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

const int MAX_P = 1e6 + 10;
const int MAX_N = 1e4 + 10;
const int MAX_M = 1e3 + 10;

int point[MAX_N];
std::pair<int, int> segment[MAX_M];
int diff[2 * MAX_P + 100];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; i++)
        std::cin >> point[i];
    for (int i = 1; i <= m; i++)
        std::cin >> segment[i].first >> segment[i].second;
    std::sort(segment + 1, segment + m + 1,
              [](std::pair<int, int> p1, std::pair<int, int> p2) -> bool
              { return p1.first == p2.first ? p1.second < p2.second : p1.first < p2.first; });

    int size = 1;
    for (int i = 2; i <= m; i++)
    {
        if (segment[i].first <= segment[size].second)
            segment[size].second = std::max(segment[i].second, segment[size].second);
        else
            segment[++size] = segment[i];
    }

    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int l = segment[i].first - point[j];
            int r = segment[i].second - point[j];
            diff[l + MAX_P]++;
            diff[r + 1 + MAX_P]--;
        }
    }

    for (int i = -MAX_P + 1; i <= MAX_P; i++)
        diff[i + MAX_P] += diff[i - 1 + MAX_P];
    int ans = -MAX_P;
    for (int i = -MAX_P + 1; i <= MAX_P; i++)
    {
        if (diff[i + MAX_P] > diff[ans + MAX_P])
            ans = i;
        else if (diff[i + MAX_P] == diff[ans + MAX_P] && std::abs(ans) > std::abs(i))
            ans = i;
    }

    std::cout << std::abs(ans) << " " << diff[ans + MAX_P];
    return 0;
}