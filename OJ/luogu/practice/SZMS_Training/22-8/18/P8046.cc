#include <iostream>
#include <cmath>

using ll = long long;
ll n, k, q;

int get_depth(ll x)
{
    int pow = 0;
    while (x > 0)
    {
        x -= std::pow(k, pow);
        pow++;
    }

    return pow;
}

ll fa(ll x) { return (x - 2) / k + 1; }

int main()
{
    std::freopen("chewbacca.in.6", "r", stdin);
    std::freopen("chewbacca.my.6", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> k >> q;

    for (int _i = 0; _i < q; _i++)
    {
        ll x, y;
        std::cin >> x >> y;

        if (get_depth(x) > get_depth(y))
            std::swap(x, y);

        ll len = 0;
        while (get_depth(y) > get_depth(x))
        {
            y = fa(y);
            len++;
        }

        while (x != y)
        {
            x = fa(x);
            y = fa(y);
            len += 2;
        }

        std::cout << len << "\n";
    }
    return 0;
}