#include <iostream>
const int MAXN = 1e3 + 10;
bool attracted[MAXN];
int r[MAXN];
int main()
{
    int n, l, k;
    std::cin >> n >> l >> k;
    for (int i = 0; i < n; i++)
        std::cin >> r[i];

    int ans = 0;
    while (true)
    {
        bool found = false;
        
        for (int i = 0; i < n; i++)
        {
            if (!attracted[i] && r[i] <= l)
            {
                found = true;
                attracted[i] = true;
                l += k;
                ans++;
                break;
            }
        }

        if (!found)
            break;
    }

    std::cout << ans;
    return 0;
}