#include <iostream>
#include <numeric>
#include <vector>

using bin = std::vector<bool>;

bin dec2bin(int num)
{
    bin res;
    while (num)
    {
        res.push_back(num % 2);
        num /= 2;
    }

    return res;
}

int bin2dec(const bin bin)
{
    int res = 0;
    int bit_num = 1;
    for (auto bit : bin)
    {
        res += bit * bit_num;
        bit_num *= 2;
    }

    return res;
}

int main()
{
    int n, k;
    std::cin >> n >> k;

    const bin n_bin = dec2bin(n);
    const int t_cnt = std::accumulate(n_bin.begin(), n_bin.end(), 0);

    if (t_cnt <= k)
    {
        std::cout << 0;
        return 0;
    }

    for (std::size_t i = 0; i < n_bin.size(); i++)
    {
        if (!n_bin[i] && std::accumulate(n_bin.begin() + i + 1, n_bin.end(), 0) + 1 <= k)
        {
            bin org;
            for (std::size_t j = 0; j <= i; j++)
                org.push_back(n_bin[j]);

            std::cout << (1 << i) - bin2dec(org);
            return 0;
        }
    }

    std::cout << (1 << n_bin.size()) - n;

    return 0;
}