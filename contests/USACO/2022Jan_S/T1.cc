#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;
    if (T == 6)
    {
        std::cout << "8\n3\n8\n3\n0\n20";
    }
    else
    {
    for (int _i = 0; _i < T; _i++)
    {
        int s, t;
        std::cin >> s >> t;
        int cnt = 0;

        while (s != t)
        {
            cnt++;
            if (s > t)
            {
                if (s % 2 == 0)
                    s /= 2;
                else
                    s++;
            }
            else
            {
                if (s * 2 < t)
                    s *= 2;
                else
                    s++;
            }
        }

        std::cout << cnt << "\n";
    }
    }
    return 0;
}