#include <iostream>
#include <cstdio>

int main()
{
    std::freopen("stone.in", "r", stdin);
    std::freopen("stone.out", "w", stdout);

    int n;
    std::cin >> n;

    int num;
    std::cin >> num;

    if (num % 2 == 1)
        std::cout << (num + 1) / 2;
    else
        std::cout << num / 2 - 1;
    return 0;
}
