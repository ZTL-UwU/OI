#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>

std::vector<int> time_line;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    time_line.push_back(0);
    for (int i = 0; i < n; i++)
    {
        std::string op;
        int val;
        std::cin >> op >> val;

        if (op == "ADD")
            time_line.push_back(time_line.back() + val);
        if (op == "SUB")
            time_line.push_back(time_line.back() - val);
        if (op == "BACK")
            time_line.push_back(time_line[time_line.size() - val - 1]);
        if (op == "SET")
            time_line.push_back(val);

        std::cout << time_line.back() << " ";
    }
    return 0;
}