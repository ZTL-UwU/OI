#include <iostream>

const int MAX_N = 3e6 + 10;

long long int inv[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, p;
    std::cin >> n >> p;

    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;

    for (int i = 1; i <= n; i++)
        std::cout << inv[i] << "\n";
    return 0;
}