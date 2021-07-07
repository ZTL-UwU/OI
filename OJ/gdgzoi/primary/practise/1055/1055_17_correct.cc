#include <iostream>

const int MAX_N = 2e6 + 10;

int color[MAX_N];
int num[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, k, p;
    std::cin >> n >> k >> p;

    int closest = 0;
    long long int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int cost;
        std::cin >> color[i] >> cost;

        if (cost <= p)
        {
            for (int j = i; j > closest; j--)
                num[color[j]]++;

            closest = i;
            ans += num[color[i]] - 1;
        }
        else
            ans += num[color[i]];
    }

    std::cout << ans;
    return 0;
}
