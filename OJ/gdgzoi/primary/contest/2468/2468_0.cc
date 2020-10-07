#include <iostream>
#include <cstdio>

const int MAXN = 1e6 + 10;
int w[MAXN];
int d[MAXN];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int l, n, m;
    std::cin >> l >> n >> m;

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        std::cin >> w[i];
        sum += w[i];
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> d[i];
        sum += d[i];
    }

    std::cout << sum;
    return 0;
}