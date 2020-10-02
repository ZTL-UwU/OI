#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

const int MAXN = 50;
std::vector<int> choose;
std::vector<int> choose2;
bool used1[MAXN];
bool used2[MAXN];
int m[MAXN];
int m_sum;
int last1;
int last2;
int ans;
int sum;
int n;

inline void dfs2(int num, int now)
{
    if (now == num)
    {
        if (sum + sum == m_sum)
            ans++;
        return;
    }

    for (int i = last2 + 1; i < choose.size(); i++)
    {
        if (!used2[choose[i]])
        {
            used2[choose[i]] = true;
            sum += m[choose[i]];
            choose2.push_back(i);

            last2 = i;
            dfs2(num, now + 1);

            sum -= m[choose[i]];
            choose2.pop_back();
            used2[choose[i]] = false;
        }
    }
}

inline void dfs1(int num, int now)
{
    if (now == num)
    {
        for (int i = 1; i <= num - 1; i++)
        {
            last2 = 0;
            dfs2(i, 0);
        }
        return;
    }
    
    for (int i = last1; i < n; i++)
    {
        if (!used1[i])
        {
            used1[i] = true;
            choose.push_back(i);
            m_sum += m[i];

            last1 = i;
            dfs1(num, now + 1);

            m_sum -= m[i];
            choose.pop_back();
            used1[i] = false;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;
    for (int i = 0; i < n; i++)
        std::cin >> m[i];

    ans = 0;
    for (int i = n; i >= 2; i--)
    {
        last1 = 0;
        dfs1(i, 0);
    }

    std::cout << ans;
    return 0;
}