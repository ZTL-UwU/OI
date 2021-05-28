#include <unordered_map>
#include <iostream>
#include <utility>

const int MAX_N = 1e4 + 10;

std::unordered_map<long long int, bool> mp;
int diff[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, k, h, q;
    std::cin >> n >> k >> h >> q;

    for (int i = 0; i < q; i++)
    {
        int l, r;
        std::cin >> l >> r;
        l--;
        r--;

        if (l > r)
            std::swap(l, r);

        if (!mp[l * MAX_N + r])
        {
            mp[l * MAX_N + r] = true;
            diff[l + 1]++;
            diff[r]--;
        }
    }

    int num = 0;
    for (int i = 0; i < n; i++)
    {
        num += diff[i];
        std::cout << h - num << "\n";
    }
    return 0;
}
