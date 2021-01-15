#include <iostream>

inline int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int b, n;
    std::cin >> b >> n;

    for (int i = 1; i <= n; i++)
        std::cout << gcd(i, b) << "\n";
}