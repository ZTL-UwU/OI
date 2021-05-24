#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <cmath>

const int MAX_N = 5e4 + 10;
const int MAX_LOG = 20;

int year[MAX_N];
int rain[MAX_N];
int n;

class RMQ
{
private:
    const int BASE = 0;
    int base[MAX_N][MAX_LOG];

public:
    void init(int key, int val) { base[key][BASE] = val; }

    void build()
    {
        for (int i = 1; i <= std::log2(n); i++)
            for (int j = 1; j + (1 << i) - 1 <= n; j++)
                base[j][i] = std::max(base[j][i - 1], base[j + (1 << (i - 1))][i - 1]);
    }

    int query(int l, int r)
    {
        const int k = std::log2(r - l + 1);
        return std::max(base[l][k], base[r - (1 << k) + 1][k]);
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    RMQ rmq;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> year[i] >> rain[i];

        rmq.init(i, rain[i]);
    }
    rmq.build();

    int q;
    std::cin >> q;
    for (int _i = 0; _i < q; _i++)
    {
        int year1, year2;
        std::cin >> year1 >> year2;
        if (year1 >= year2)
        {
            printf("false\n");
            continue;
        }

        int start = std::lower_bound(year + 1, year + n + 1, year1) - year;
        const int end = std::lower_bound(year + 1, year + n + 1, year2) - year;
        int max = 0;

        const bool start_exist = year[start] == year1;
        const bool end_exist = year[end] == year2;

        if (!start_exist)
            start--;
        if (start + 1 <= end - 1)
            max = rmq.query(start + 1, end - 1);

        if ((max >= rain[end] && end_exist) || (max >= rain[start] && start_exist)
            || (rain[start] < rain[end] && start_exist && end_exist))
            std::cout << "false\n";
        else if (end - start != year[end] - year[start] || !end_exist || !start_exist)
            std::cout << "maybe\n";
        else
            std::cout << "true\n";
    }
    return 0;
}
