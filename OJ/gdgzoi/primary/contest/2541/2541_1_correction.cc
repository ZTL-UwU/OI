#include <algorithm>
#include <iostream>
#include <cmath>

struct num
{
    int val;
    int org_id;

    bool operator<(const num x) const
    {
        if (this->val == x.val)
            return this->org_id < x.org_id; 
        return this->val < x.val;
    }
};

const int MAX_N = 1e5 + 10;

num a[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;
    for (int _i = 0; _i < t; _i++)
    {
        int n, k;
        std::cin >> n >> k;
        for (int i = 0; i < n; i++)
        {
            std::cin >> a[i].val;
            a[i].org_id = i;
        }

        std::sort(a, a + n);
        int max_shift = -1;
        for (int i = 0; i < n; i++)
            if (i < a[i].org_id)
                max_shift = std::max(max_shift, a[i].org_id - i);

        std::cout << std::ceil(max_shift / (k - 1.0)) << "\n";
    }
    return 0;
}
