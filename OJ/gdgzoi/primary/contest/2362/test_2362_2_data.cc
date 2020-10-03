#include <bits/stdc++.h>

int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n * 2; i++)
    {
        int tmp;
        std::cin >> tmp;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        std::cin >> a >> b;
    }

    int m;
    std::cin >> m;
    std::cout << m << "\n";
    for (int i = 0; i < m; i++)
    {
        std::string str;
        std::getline(std::cin, str);
        std::cout << str << "\n";
    }
    return 0;
}