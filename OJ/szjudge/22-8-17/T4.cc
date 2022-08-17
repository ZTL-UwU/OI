#include <iostream>
#include <vector>
#include <map>

const int MAX_N = 1010;
std::map<std::vector<int>, int> no;
std::map<int, std::vector<int>> rev_no;
std::map<int, int> cnt;
int no_cnt;
int list[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
            std::cin >> list[j];
        for (int j = 0; j <= n - 1; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                std::vector<int> v;
                for (int l = 0; l < n - 1; l++)
                {
                    if (l == j)
                        v.push_back(k);
                    v.push_back(list[l] < k ? list[l] : list[l] + 1);
                    if (j == n - 1 && l == n - 2)
                        v.push_back(k);
                }

                if (!no[v])
                {
                    no[v] = ++no_cnt;
                    rev_no[no_cnt] = v;
                }
                cnt[no[v]]++;
            }
        }
    }

    for (int i = 1; i <= no_cnt; i++)
    {
        if (cnt[i] >= n)
        {
            for (auto j : rev_no[i])
                std::cout << j << " ";
            return 0;
        }
    }
    return 0;
}