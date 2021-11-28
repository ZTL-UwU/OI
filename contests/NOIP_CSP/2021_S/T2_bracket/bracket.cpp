#include <iostream>
#include <cstdio>

using u64 = unsigned long long;

const u64 MOD = 1e9 + 7;
const int MAX_N = 1e3;

u64 mem[MAX_N][MAX_N];
std::string str;
int n, k;

u64 dfs(int l, int r)
{
    if (r - l + 1 < 2)
        return 0;
    if (mem[l][r] != 0)
        return mem[l][r];

	u64 res = 0;
	if ((str[l] == '(' || str[l] == '?') && (str[r] == ')' || str[r] == '?'))
    {
        // ()
        if (r - l + 1 == 2)
            res += 1;

        // (S)
        if (r - l + 1 <= k + 2 && r - l + 1 >= 3)
        {
            bool flag = true;
            for (int i = l + 1; i <= r - 1; i++)
            {
                if (str[i] != '*' && str[i] != '?')
                {
                    flag = false;
                    break;
                }
            }

            if (flag)
                res++;
        }

        // (A)
        if (r - l + 1 >= 4)
            res = (res + dfs(l + 1, r - 1)) % MOD;

        // (SA)
        if (r - l + 1 >= 5)
        {
            for (int i = 1; i <= k; i++)
            {
                if (l + i >= r - 2 || str[l + i] != '*' && str[l + i] != '?')
                    break;
                res = (res + dfs(l + 1 + i, r - 1)) % MOD;
            }
        }

        // (AS)
        if (r - l + 1 >= 5)
        {
            for (int i = 1; i <= k; i++)
            {
                if (l + i >= r - 2 || str[r - i] != '*' && str[r - i] != '?')
                    break;
                res = (res + dfs(l + 1, r - i - 1)) % MOD;
            }
        }
    }

    // AA
    for (int i = l + 1; i <= r - 2; i++)
        res = (res + dfs(l, i) * dfs(i + 1, r) % MOD) % MOD;

    // ASA
    for (int i = l + 1; i <= r - 3; i++)
    {
        for (int j = i + 1; j <= std::min(i + k, r - 2); j++)
        {
            if (str[j] != '*' && str[j] != '?')
                break;
            res = (res + dfs(l, i) * dfs(j + 1, r) % MOD) % MOD;
        }
    }

    return mem[l][r] = res;
}

int main()
{
	std::freopen("bracket.in", "r", stdin);
	std::freopen("bracket.out", "w", stdout);

	std::cin >> n >> k >> str;
    std::cout << dfs(0, n - 1);
	return 0;
}