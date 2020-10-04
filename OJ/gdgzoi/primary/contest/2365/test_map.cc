#include <bits/stdc++.h>

int main()
{
    std::map<int, int> test;
    test[1] = 0;
    test[2] = 1;

    if (test[3] == test.end())
        std::cout << "hi";
    return 0;
}