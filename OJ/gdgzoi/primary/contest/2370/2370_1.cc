#include <iostream>
#include <cstring>
#include <cstdio>

#include <dbg.h>

const int MAXN = 5e1;
int a[MAXN];

inline bool check(int bob[4])
{
    for (int step = 0; step < 150; step++)
    {
        bool flag = false;
        for (int i = 0; i < 4; i++)
        {
            if (bob[i] == 1)
                flag = true;

            if (bob[i] != 0)
            {
                bob[i]--;
                if (bob[i] != 0)
                    for (int j = 0; j < 4; j++)
                        if (bob[j] == 0)
                            bob[j] = a[bob[i]];
            }
        }
        if (!flag)
            return false;
    }
    return true;
}

int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++)
        std::cin >> a[i];

    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            for (int k = 0; k <= n; k++)
            {
                for (int l = 0; l <= n; l++)
                {
                    int bob[4] = {i, j, k, l};
                    int bob1[4] = {i, j, k, l};
                    if (check(bob))
                    {
                        dbg(bob1);
                        ans++;
                    }
                }
            }
        }
    }

    std::cout << ans;
    return 0;
}