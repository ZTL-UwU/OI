#include <iostream>

const int MAX_N = 1e6 + 10;

long long int inv[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    inv[1] = 1;
    for (int i = 2; i <= n - 1; i++)
        inv[i] = (n - n / i) * inv[n % i] % n;

    for (int i = 1; i <= n - 1; i++)
        std::cout << inv[i] << "\n";
    return 0;
}