#include <iostream>
#include <cstring>

const int MAX_N = 1e4 + 10;

int a[MAX_N];
bool used[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int i = 0; i < n - 1; i++)
        std::cin >> a[i];

    for (int i = 1; i < a[0]; i++)
    {
        std::memset(used, 0, sizeof(used));
        int last = i;
        used[last] = true;
        bool flag = true;

        for (int j = 1; j < n; j++)
        {
            if (a[j - 1] - last <= 0 or used[a[j - 1] - last])
            {
                flag = false;
                break;
            }
            else
            {
                used[a[j - 1] - last] = true;
                last = a[j - 1] - last;
            }
        }

        if (flag)
        {
            last = i;
            std::cout << last << " ";

            for (int j = 1; j < n; j++)
            {
                std::cout << a[j - 1] - last << " ";
                last = a[j - 1] - last;
            }

            return 0;
        }
    }
    return 0;
}