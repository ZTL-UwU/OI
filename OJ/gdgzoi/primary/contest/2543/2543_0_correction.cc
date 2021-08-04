#include <iostream>

const int MAX_N = 1e6 + 10;

int pos[MAX_N];

int main()
{
    int n;
    std::string s, t;
    std::cin >> n >> s >> t;
    s = "#" + s;
    t = "#" + t;

    int p2 = n;
    int ans = 0;
    int height = 0;
    pos[n + 1] = n + 1;
    int p3 = n + 1;
    for (int p1 = n; p1 >= 1; p1--)
    {
        p2 = std::min(p1, p2);
        if (t[p1] == t[p1 - 1])
            continue;

        while (p2 >= 1 && t[p1] != s[p2])
            p2--;

        if (p2 <= 0)
        {
            std::cout << -1;
            return 0;
        }

        pos[p1] = p2;
        if (pos[p3] > p1)
            height = (p1 == p2) ? 0 : 2;
        else
            height++;

        p3 = p1;
        ans = std::max(ans, height);
    }

    std::cout << ans;
    return 0;
}
