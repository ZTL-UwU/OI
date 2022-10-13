#include <unordered_map>
#include <iostream>

using i64 = long long;

const int MAX_LEFT = 136 - 13;
const int MOD = 1e9 + 7;

std::unordered_map<int, bool> map;
i64 f[13 + 10][MAX_LEFT + 10];

i64 pow(i64 a, int b)
{
    i64 res = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b /= 2;
    }

    return res;
}

void get_f()
{
    for (int i = 1; i <= MAX_LEFT; i++)
    {
        const int inv = pow(i, MOD - 2);
        f[1][i] = (1 + f[1][i - 1] * (i - 3) % MOD * inv) % MOD;
        for (int j = 2; j <= 13; j++)
            f[j][i] = (1 + f[j - 2][i - 1] * 3 * j % MOD * inv) % MOD + (f[j][i - 1] * (i - 3 * j) % MOD * inv) % MOD;
    }
}

int main()
{
    get_f();
    int t;
    std::cin >> t;

    for (int _i = 1; _i <= t; _i++)
    {
        map.clear();
        int s0 = 13;
        for (int i = 0; i < 13; i++)
        {
            char num, no;
            std::cin >> num >> no;
            if (!map[(int)(num * 1000 + no)])
                map[(int)(num * 1000 + no)] = true;
            else
                s0 -= 2;
        }

        std::cout << "Case #" << _i << ": " << f[s0][MAX_LEFT] % MOD << "\n";
    }
    return 0;
}