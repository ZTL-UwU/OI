#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    long long n;
    std::cin >> n;

    if (n == 1)
    {
        std::cout << 0;
        return 0;
    }

    std::vector<long long> ans;
    ans.reserve(std::sqrt(std::sqrt(n)));
    for (int i = 1; i <= std::sqrt(n); i++)
    {
        if (n % i == 0)
        {
            if (i % 2 == 1 && i != 1)
                ans.emplace_back(n - n / i);
            if (n / i % 2 == 1)
                ans.emplace_back(n - i);
        }
    }

    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << " ";
    for (auto a : ans)
        std::cout << a << " ";
    return 0;
}