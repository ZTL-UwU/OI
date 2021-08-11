#include <iostream>
#include <vector>

const int MAX_N = 5e5 + 10;

std::vector<int> aggregate1[MAX_N];
std::vector<int> aggregate2[MAX_N];
int ans[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, q;
    std::cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        aggregate1[i].push_back(i);
        aggregate2[i].push_back(i);
    }

    for (int _i = 0; _i < q; _i++)
    {
        char op;
        std::cin >> op;

        if (op == 'U')
        {
            int x, y;
            std::cin >> x >> y;
            for (auto i : aggregate1[y])
                aggregate1[x].push_back(i);
        }
        else if (op == 'M')
        {
            int x, y;
            std::cin >> x >> y;
            for (auto i : aggregate2[y])
                aggregate2[x].push_back(i);
        }
        else if (op == 'A')
        {
            int x;
            std::cin >> x;
            for (auto i : aggregate1[x])
                ans[i] += aggregate1[x].size();
        }
        else if (op == 'Z')
        {
            int x;
            std::cin >> x;
            for (auto i : aggregate2[x])
                ans[i] = 0;
        }
        else if (op == 'Q')
        {
            int x;
            std::cin >> x;
            std::cout << ans[x] << "\n";
        }
    }
    return 0;
}