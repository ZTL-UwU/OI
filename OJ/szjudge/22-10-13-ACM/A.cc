// 简单

#include <algorithm>
#include <iostream>
#include <vector>

using pii = std::pair<int, int>;
std::vector<pii> p;

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x, r;
        std::cin >> x >> r;
        p.push_back({x - r, x + r});
    }

    std::sort(p.begin(), p.end(), [](pii a, pii b) { return a.first < b.first; });
    int last = p.front().first;

    int ans = 0;
    for (pii i : p)
    {
        if (i.first > last)
            ans += i.first - last;
        last = std::max(last,i.second);
    }

    std::cout << ans;
    return 0;
}