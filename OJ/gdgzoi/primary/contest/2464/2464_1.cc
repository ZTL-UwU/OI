#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>

int main()
{
    srand(20201001);
    int T;
    std::cin >> T;
    for (int i = 0; i < T; i++)
    {
        if (rand() % 2 == 0)
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }
    return 0;
}