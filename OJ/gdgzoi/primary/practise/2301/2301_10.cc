#include <iostream>
#include <vector>

std::vector<int> v;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    v.reserve(n);

    int a;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a;
        v.push_back(a);
    }

    for (int i = 0; i < n; i++)
    {
        int op, l, r, c;
        std::cin >> op >> l >> r >> c;

        if (op == 0)
            v.insert(v.begin() + l - 1, r);
        else
            std::cout << v[r - 1] << "\n";
    }

    return 0;
}
