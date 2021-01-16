#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> a_pos;
std::vector<int> a_neg;

std::vector<int> b_pos;
std::vector<int> b_neg;

std::vector<int> a_remaining;
std::vector<int> b_remaining;

long long int ans;

inline bool cmp1(int a, int b) { return a > b; }
inline bool cmp2(int a, int b) { return a < b; }

inline void input(int max, std::vector<int> &v1, std::vector<int> &v2)
{
    for (int i = 0; i < max; i++)
    {
        int tmp;
        std::cin >> tmp;

        if (tmp >= 0)
            v1.push_back(tmp);
        else
            v2.push_back(tmp);
    }
}

inline void solve_part(std::vector<int> &v1, std::vector<int> &v2, int &flag)
{
    for (std::size_t i = 0; i < std::min(v1.size(), v2.size()); i++)
        ans += (long long int)v1[i] * v2[i];
    while (v1.size() > v2.size())
    {
        flag = 1;
        a_remaining.push_back(v1.back());
        v1.pop_back();
    }
    while (v2.size() > v1.size())
    {
        flag = 0;
        b_remaining.push_back(v2.back());
        v2.pop_back();
    }
}

inline void solve_remaining(std::vector<int> &v1, std::vector<int> &v2)
{
    std::sort(v1.begin(), v1.end(), cmp2);
    std::sort(v2.begin(), v2.end(), cmp1);

    for (std::size_t i = 0; i < std::min(v1.size(), v2.size()); i++)
        ans += (long long int)v1[i] * v2[i];
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    input(n, a_pos, a_neg);
    input(m, b_pos, b_neg);

    std::sort(a_pos.begin(), a_pos.end(), cmp1);
    std::sort(a_neg.begin(), a_neg.end(), cmp2);

    std::sort(b_pos.begin(), b_pos.end(), cmp1);
    std::sort(b_neg.begin(), b_neg.end(), cmp2);

    int flag1 = -1;
    int flag2 = -1;
    solve_part(a_pos, b_pos, flag1);
    solve_part(a_neg, b_neg, flag2);

    if (flag1 == 1 and flag2 == 0)
        solve_remaining(a_remaining, b_remaining);
    else if (flag1 == 0 and flag2 == 1)
        solve_remaining(b_remaining, a_remaining);

    std::cout << ans;
    return 0;
}