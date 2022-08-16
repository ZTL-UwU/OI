#include <iostream>
#include <cstdio>

const int MAXN = 1e5;
int pos[MAXN];

int main()
{
    int ll, n, m;
    std::cin >> ll >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> pos[i];

    int l = 0;
    int r = ll;
    int ans = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;

        int remove = 0;
        int now = 0;
        for (int i = 1; i <= n; i++)
        {
            if (pos[i] - pos[now] < mid)
                remove++;
            else
                now = i;
        }

        if (remove <= m)
        {
            l = mid + 1;
            ans = mid;
        }
        else
            r = mid - 1;
    }

    std::cout << ans;
    return 0;
}