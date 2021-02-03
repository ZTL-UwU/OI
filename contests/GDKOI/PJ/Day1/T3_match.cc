#include <algorithm>
#include <iostream>

const int MAX_N = 1e6 + 10;

int a[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, l, r;
    std::cin >> n >> l >> r;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    std::sort(a, a + n);

    int l_p = 0;
    int r_p = n - 1;
    int ans = 0;

    while (l_p < r_p)
    {
        if (a[l_p] + a[r_p] > r)
        {
            r_p--;
            ans++;
        }
        else if (a[l_p] + a[r_p] < l)
        {
            l_p++;
            ans++;
        }
        else
        {
            l_p++;
            r_p--;
        }
    }

    if ((r_p - l_p + 1) % 2 == 1)
        ans++;

    std::cout << ans;
    return 0;
}