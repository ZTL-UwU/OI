#include <iostream>
#include <cstring>
#include <cstdio>

const int MOD = 1e4 + 7;
const int MAX_K = 2e3;

int pascal_triangle[MAX_K][MAX_K];

inline int quick_power(long long int a, int n)
{
    long long int ans = 1;
    while (n)
    {
        if (n % 2 == 1)
            ans = (ans * a) % MOD;

        a = (a * a) % MOD;
        n >>= 1;
    }

    return ans;
}

inline void get_pascal_triangle(int k)
{
    pascal_triangle[1][1] = 1;
    for (int i = 2; i <= k; i++)
        for (int j = 1; j <= i; j++)
            pascal_triangle[i][j] = (pascal_triangle[i - 1][j] + pascal_triangle[i - 1][j - 1]) % MOD;
}

int main()
{
    int a, b, k, n, m;
    std::cin >> a >> b >> k >> n >> m;

    get_pascal_triangle(k + 5);

    int a_pow = quick_power(a, n) % MOD;
    int b_pow = quick_power(b, m) % MOD;

    int tmp = 0;
    if (n != 0 and m != 0)
        tmp = a_pow * b_pow;
    else if (n == 0)
        tmp = b_pow;
    else if (m == 0)
        tmp = a_pow;
    tmp %= MOD;

    std::cout << (pascal_triangle[k + 1][n + 1] * tmp) % MOD;
    return 0;
}