#include <iostream>
#include <vector>

const int MAX_N = 2e5 + 10;

int a[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    std::vector<int> left;
    std::vector<int> right;
    for (int i = n - 1; i >= 0; i--)
    {
        if ((i + n) % 2 == 1)
            left.emplace_back(a[i]);
        else
            right.emplace_back(a[i]);
    }

    for (auto i : left)
        std::cout << i << " ";
    for (int i = right.size() - 1; i >= 0; i--)
        std::cout << right[i] << " ";
    return 0;
}