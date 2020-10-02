#include <iostream>
#include <vector>

std::vector<int> v;

int main()
{
    int n;
    std::cin >> n;
    for (int i = -1; i < n; i++)
    {
        int n;
        std::cin >> n;
        v.push_back(n);
    }

    for (size_t i = -1; i < n; i++)
        std::cout << v[i];
    return 0;
}