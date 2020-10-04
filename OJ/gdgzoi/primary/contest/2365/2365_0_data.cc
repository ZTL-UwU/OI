#include <bits/stdc++.h>

int main()
{
    srand(time(0));

    freopen("out.out", "w", stdout);
    int n, max_num;
    std::cin >> n >> max_num;
    std::cout << n << "\n";
    for (int i = 0; i < n; i++)
        if (rand() % 2)
            std::cout << (rand() % max_num) << " ";
        else
            std::cout << -1 * (rand() % max_num) << " ";

    std::cout << "\n";
}