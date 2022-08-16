#include <iostream>

using i64 = long long;

i64 calc(i64 x) { return x * (x - 1) / 2; }

int main()
{
    i64 n, m, k;

    std::cin >> n >> m >> k;
    i64 ans = 0;
    i64 tmp_ans = 0;
    for (i64 i = 1; i <= m; i++)
    {
        if (k / i + (bool)(k % i) <= n)
        {
            tmp_ans = calc(k / i) * calc(i) + calc(k % i) * (k / i);
            ans = std::max(ans, tmp_ans);
        }
    }

    std::swap(n, m);
    if (n != m)
    {
        for (i64 i = 1; i <= m; i++)
        {
            if (k / i + (bool)(k % i) <= n)
            {
                tmp_ans = calc(k / i) * calc(i) + calc(k % i) * (k / i);
                ans = std::max(ans, tmp_ans);
            }
        }
    }

    std::cout << ans;
    return 0;
}