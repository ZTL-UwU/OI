#include <algorithm>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <vector>

#include <dbg.h>

const int MAXN = 10;

std::vector<int> state;
int n, k;
int ans;

int max_k_form[MAXN] = {0, 1, 1, 4, 4, 9, 9, 16, 16, 25};

inline void get_state()
{
    for (int i = 0; i < (1 << n); i++)
        if (!(i & (i << 1))) // Last digit
            state.push_back(i);
}

inline int count_state(int sta)
{
    int res = 0;
    while (sta)
    {
        if (sta % 2 == 1)
            res++;
        sta /= 2;
    }

    return res;
}

inline void dfs(int u, int last_state, int selected)
{
    if (u > n)
        return;
    if (selected == k)
        ans++;
    if (selected >= k)
        return;

    for (auto i : state)
        if (!(i & last_state or i & (last_state << 1) or i & (last_state >> 1)))
            dfs(u + 1, i, selected + count_state(i));
}

int main()
{
    std::ofstream of("./2470_0_form4.out");
    for (int i = 8; i <= 9; i++)
    {
        n = i;
        state.clear();
        get_state();
        for (int j = 10; j <= i * i; j++)
        {
            k = j;
            std::cout << i << ":" << j << "\n";
            ans = 0;

            if (k > max_k_form[n])
            {
                of << "0\n";
                continue;
            }

            dfs(0, 0, 0);

            of << ans << '\n';
            of.flush();
        }
        of << "\n";
        of.flush();
    }
    return 0;
}