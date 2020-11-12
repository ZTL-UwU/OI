#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

const int MAX_N = 1e7 + 10;

int lg[MAX_N];
std::vector<int> ans;

int main()
{
    int n;
    std::cin >> n;

    lg[0] = -1;
    for (int i = 1; i <= n; i++)
        lg[i] = lg[i / 2] + 1;

    for (int i = lg[n]; i >= 1; i--)
    {
        int tmp = std::pow(2, i);
        if (n >= tmp)
        {
            n -= tmp;
            ans.push_back(tmp);
        }
    }

    if (n != 1)
        for (auto i : ans)
            std::cout << i << " ";
    else
        std::cout << "-1";
    return 0;
}