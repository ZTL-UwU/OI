#include <iostream>
#include <cmath>

using i64 = long long;

i64 low_bit(i64 x) { return x & -x; }

i64 pow(i64 a, int n)
{
    i64 ans = 1;
    for (int _i = 0; _i < n; _i++)
        ans *= a;

    return ans;
}

int main()
{
    i64 l, r;
    std::cin >> l >> r;
    if (l == r)
    {
        std::cout << low_bit(l);
        return 0;
    }

    i64 ans = 0;
    for (int i = 1; i < 52; i++)
    {
        const i64 p2i = pow(2, i);
        const i64 p2i1 = pow(2, i - 1);

        if (p2i1 > r)
            break;

        ans += ((r - p2i1) / p2i - (l - 1 - p2i1) / p2i + (l <= p2i1 ? 1 : 0)) * p2i1;
    }

    std::cout << ans;
    return 0;
}