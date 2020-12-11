#include <iostream>

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

inline long long int gcd(int a, int b)
{
    if (b == 0)
        return a;

    return gcd(b, a % b);
}

int main()
{
    long long int n, m;
    std::cin >> n >> m;

    n++;
    m++;

    long long int tot = c(n * m, 3);
    long long int vertical = 0;
    long long int horizontal = 0;
    if (n >= 3)
        vertical = c(n, 3) * m;
    if (m >= 3)
        horizontal = c(m, 3) * n;

    long long int oblique = 0;
    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= m - 1; j++)
            oblique += (n - i) * (m - j) * (gcd(i, j) - 1) * 2;

    std::cout << tot - vertical - horizontal - oblique;
    return 0;
}