#include <iostream>
#include <cstring>

const int MAX_N = 1e5 + 10;

int diff[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    while (std::cin >> n)
    {
        if (n == 0)
            return 0;

        for (int i = 0; i < n; i++)
        {
            int l, r;
            std::cin >> l >> r;
            l--;
            r--;

            diff[l]++;
            diff[r + 1]--;
        }

        int num = 0;
        for (int i = 0; i < n; i++)
        {
            num += diff[i];
            std::cout << num << " ";
        }

        std::cout << "\n";
        std::memset(diff, 0, sizeof(diff));
    }
    return 0;
}
