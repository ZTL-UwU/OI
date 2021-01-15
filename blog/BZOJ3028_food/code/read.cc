#include <iostream>

const int MOD = 10007;

template <typename T>
void read(T &n)
{
    n = 0;
    char ch = getchar();

    while (ch >= '0' and ch <= '9')
    {
        n = (n * 10 + ch - '0') % MOD;
        ch = getchar();
    }
}

int main()
{
    int n;
    int m;
    read(n);
    std::cin >> m;

    std::cout << n << "\n";
    std::cout << m % MOD;
    return 0;
}