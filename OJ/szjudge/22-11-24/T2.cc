#include <iostream>
#include <vector>

const int MAX_N = 1e3 + 10;

std::vector<int> ans;
int a[MAX_N];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    bool has_ans = true;
    while (true)
    {
        bool flag = false;
        for (int i = 2; i < n; i++)
        {
            if (a[i] < a[i - 2])
            {
                std::swap(a[i], a[i - 1]);
                std::swap(a[i - 1], a[i - 2]);
                ans.push_back(i - 1);
                flag = true;
            }
        }

        if (!flag)
        {
            for (int i = 1; i < n; i++)
            {
                if (a[i] < a[i - 1])
                {
                    has_ans = false;
                    break;
                }
            }

            break;
        }
    }

    if (!has_ans)
        std::cout << -1;
    else
    {
        std::cout << ans.size() << "\n";
        for (auto i : ans)
            std::cout << i << " ";
    }
    return 0;
}