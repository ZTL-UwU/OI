#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

std::vector<int> a;
std::vector<int> b;
std::vector<int> c;
std::vector<int> d;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int tmp;
        std::cin >> tmp;
        if (tmp < 0)
            a.push_back(-tmp);
        else
            b.push_back(tmp);
    }
    for (int i = 0; i < n; ++i)
    {
        int tmp;
        std::cin >> tmp;
        if (tmp < 0)
            c.push_back(-tmp);
        else
            d.push_back(tmp);
    }

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::sort(c.begin(), c.end());
    std::sort(d.begin(), d.end());

    int ans = 0;
    unsigned int x = 0;
    for (auto i : d)
    {
        while (x < a.size() and i >= a[x])
            ++x;

        if (x < a.size())
            ++ans;
        else
            break;
        ++x;
    }

    x = 0;
    for (auto i : b)
    {
        while (x < c.size() and i >= c[x])
            ++x;

        if (x < c.size())
            ++ans;
        else
            break;
        ++x;
    }
    std::cout << ans;
    return 0;
}