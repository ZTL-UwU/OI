#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>

const int MAXN = 1e4;
std::map<long long, int> card_id;
long long a[MAXN];
int ans;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        card_id[a[i]] = i;
    }

    for (int i = 1; i <= n - 1; ++i)
    {
        for (int j = i; j <= n - 1; ++j)
        {
            int k = j;
            for (k = j; k <= n - 1; ++k)
            {
                if (card_id[a[i] + a[j] + a[k]] > k)
                {
                    card_id[a[i] + a[j] + a[k]] = 0;
                    ++ans;
                }
            }
        }
    }

    std::cout << ans;
    return 0;
}