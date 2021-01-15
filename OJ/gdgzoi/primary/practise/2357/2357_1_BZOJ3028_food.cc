#include <iostream>
#include <cstdio>

const int MOD = 10007;

inline int read()
{
    char ch;
    int res = 0;

    ch = std::getchar();
    while (ch >= '0' and ch <= '9')
    {
        res = (res * 10 + ch - '0') % MOD;
        ch = std::getchar();
    }

    return res;
}

int main()
{
    int n;
    n = read();

    std::cout << ((n * (n + 1) % MOD) * (n + 2) % MOD) * 1668 % MOD;
    return 0;
}