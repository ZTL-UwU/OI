#include <cstdio>

int main()
{
    std::freopen("cake.in", "r", stdin);
    std::freopen("cake.out", "w", stdout);

    int t;
    std::scanf("%d", &t);

    for (int _i = 0; _i < t; _i++)
    {
        int a, b, c;
        std::scanf("%d %d %d", &a, &b, &c);

        int zero_count = 0;
        if (a == 0)
            zero_count++;
        if (b == 0)
            zero_count++;
        if (c == 0)
            zero_count++;

        if (zero_count == 2)
        {
            std::printf("%d\n", 0);
        }
        else if (zero_count == 1)
        {
            if (a == b or b == c or c == a)
                std::printf("%d\n", 1);
            else
                std::printf("%d\n", 2);
        }
        else
        {
            if (a + b == c or b + c == a or c + a == b)
                std::printf("%d\n", 2);
            else if (a == b or b == c or c == a)
                std::printf("%d\n", 2);
            else
                std::printf("%d\n", 3);
        }
    }
    return 0;
}