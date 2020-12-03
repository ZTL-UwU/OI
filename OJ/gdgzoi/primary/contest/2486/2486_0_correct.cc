#include <algorithm>
#include <iostream>
#include <string>

const int MAX_N = 5e3 + 10;
const int MOD = 1e9 + 7;

struct data
{
    int id;
    long long int dec;
    std::string str;
};

std::string num_bin[MAX_N];
data column[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;

    for (int i = 0; i < n; i++)
        std::cin >> num_bin[i];

    for (int i = 0; i < m; i++)
    {
        column[i].id = i;

        for (int j = n - 1; j >= 0; j--)
        {
            column[i].str.push_back(num_bin[j][i]);
            column[i].dec = (column[i].dec * 2 + (num_bin[j][i] - '0')) % MOD;
        }
    }

    column[m].id = m;
    column[m + 1].id = m + 1;

    for (int i = 0; i < n; i++)
    {
        column[m].dec = (column[m].dec * 2 + 1) % MOD;
        column[m].str.push_back('1');
    }
    column[m].dec++;

    std::sort(column, column + m + 1, [](data x, data y) {
        if (x.str != y.str)
            return x.str > y.str;
        return x.id < y.id;
    });

    for (int i = 0; i < q; i++)
    {
        std::string q_str;
        std::cin >> q_str;

        int x = 0;
        int y = m + 1;

        for (int j = m; j >= 1; j--)
        {
            if (q_str[column[j].id] == '1')
            {
                x = j;
                break;
            }
        }

        for (int j = 1; j <= m; j++)
        {
            if (q_str[column[j].id] == '0')
            {
                y = j;
                break;
            }
        }

        std::cout << (y > x ? (column[x].dec - column[y].dec + MOD) % MOD : 0) << '\n';
    }
    return 0;
}