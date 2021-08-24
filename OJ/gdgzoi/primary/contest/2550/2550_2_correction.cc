#include <iostream>
#include <vector>

const int MAX_LEN = 4e5 + 10;

int next[MAX_LEN];

int main()
{
    std::string str;
    while (std::cin >> str)
    {
        std::fill(next, next + MAX_LEN, 0);
        next[0] = -1;

        int p1 = 0;
        int p2 = -1;

        while (p1 < str.size())
        {
            if (p2 == -1 || str[p1] == str[p2])
            {
                p1++;
                p2++;
                next[p1] = p2;
            }
            else
                p2 = next[p2];
        }

        std::vector<int> ans;
        ans.push_back(str.size());
        int p = next[str.size()];
        while(p > 0)
        {
            ans.push_back(p);
            p = next[p];
        }

        for (int i = ans.size() - 1; i >= 0; i--)
            std::cout << ans[i] << " ";
        std::cout << "\n";
    }
    return 0;
}