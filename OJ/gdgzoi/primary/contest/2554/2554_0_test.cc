#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_N = 2e5 + 10;
int a[MAX_N];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    std::vector<int> v;
    for (int i = 0; i < n; i++)
    {
        v.push_back(a[i]);
        std::reverse(v.begin(), v.end());
    }

    for (auto i : v)
        std::cout << i << " ";
    return 0;
}