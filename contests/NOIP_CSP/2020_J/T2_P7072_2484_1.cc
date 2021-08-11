#include <algorithm>
#include <iostream>
#include <cstdio>

const int MAX_MARK = 7e2;

int mark_hash[MAX_MARK];

int main()
{
    int n, w;
    std::scanf("%d %d", &n, &w);

    for (int p = 1; p <= n; p++)
    {
        int mark;
        std::scanf("%d", &mark);

        mark_hash[mark]++;
        int plan = std::max(1, (p * w) / 100);
        int tmp = 0;

        for (int i = 600; i >= 0; i--)
        {
            tmp += mark_hash[i];
            if (tmp >= plan)
            {
                std::printf("%d ", i);
                break;
            }
        }
    }
    return 0;
}