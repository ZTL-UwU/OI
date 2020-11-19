#include <iostream>
#include <cstring>
#include <cstdio>

const int MOD = 1e3;

inline int quick_power(long long int a, int n)
{
    long long int ans = 1;

    while (n != 0)
    {
        if (n % 2 == 1)
            ans = (ans * a) % MOD;

        a = (a * a) % MOD;
        n >>= 1;
    }

    return ans;
}

inline long long int c(int n, int m)
{
    long long int top = 1;
    for (int i = n; i >= n - m + 1; i--)
        top *= i;

    long long int bottom = 1;
    for (int i = m; i >= 1; i--)
        bottom *= i;

    return top / bottom;
}

int main()
{
    int k, x;
    std::cin >> k >> x;

    x = quick_power(x, x);

    std::cout << c(x - 1, k - 1);
    return 0;
}