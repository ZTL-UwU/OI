#include <bits/stdc++.h>

std::string list;

int main()
{
    int n;
    std::cin >> n;

    for (int i = 1; i <= 100000; i++)
    {
        std::stringstream ss;
        ss << i;
        std::string tmp;
        ss >> tmp;

        list += tmp;
    }

    std::cout << list[n - 1];
    return 0;
}