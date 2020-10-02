#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

struct data
{
    int val;
    int id;
};

const int MAXN = 1e6 + 10;
const int MAXS = 1e4 + 10;
data basket[MAXS + 10];
int s[MAXN];
int w[MAXN];

inline bool cmp(data a, data b)
{
    if (a.val == b.val)
        return a.id < b.id;
    return a.val > b.val;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; t++)
    {
        std::cout << "Case #" << t << ":\n";
        int n;
        std::cin >> n;

        std::memset(basket, 0, sizeof(basket));
        for (int i = 0; i < n; i++)
        {
            std::cin >> w[i];
            s[i] = 10000 - (100 - w[i]) * (100 - w[i]);
            basket[s[i]].id = s[i];
            basket[s[i]].val++;
        }

        bool bad = false;
        std::sort(basket, basket + MAXS, cmp);
        std::vector<int> ans;
        for (int i = 0; i < MAXS; i++)
        {
            if (i > 1 && basket[i].val == 0 && basket[i - 1].val == basket[0].val)
            {
                bad = true;
                break;
            }

            if (basket[i].val != basket[0].val)
                break;

            ans.push_back(basket[i].id);
        }

        if (bad)
            std::cout << "Bad Mushroom";
        else
            for (int i = 0; i < ans.size(); i++)
                std::cout << ans[i] << " ";

        std::cout << "\n";
    }
    return 0;
}