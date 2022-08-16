#include <iostream>
#include <vector>
#include <cstdio>

using vb = std::vector<bool>;
const int MAX_N = 1e6 + 10;

vb s_bin[MAX_N];
int s[MAX_N];

vb dec2bin(int n)
{
    vb res;
    while (n)
    {
        res.push_back(n % 2);
        n /= 2;
    }

    return res;
}

int bin2dec(const vb &bin)
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
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, k;
    std::cin >> n >> k;

    int max = -1;
    for (int i = 0; i < n; i++)
    {
        std::cin >> s[i];
        s_bin[i] = dec2bin(s[i]);
        max = std::max(max, s[i]);
    }

    int ans = 0;
    std::vector<int> bit_cnt;
    bit_cnt.resize(dec2bin(max).size());
    for (int i = 0; i < k; i++)
    {
        for (std::size_t j = 0; j < s_bin[i].size(); j++)
            bit_cnt[j] += s_bin[i][j];

        vb bin;
        bin.resize(bit_cnt.size());
        for (std::size_t j = 0; j < bit_cnt.size(); j++)
            if (bit_cnt[j] == k)
                bin[j] = true;

        ans = std::max(ans, bin2dec(bin));
    }

    for (int i = k; i < n; i++)
    {
        for (std::size_t j = 0; j < s_bin[i].size(); j++)
            bit_cnt[j] += s_bin[i][j];
        for (std::size_t j = 0; j < s_bin[i - k].size(); j++)
            bit_cnt[j] -= s_bin[i - k][j];

        vb bin;
        bin.resize(bit_cnt.size());
        for (std::size_t j = 0; j < bit_cnt.size(); j++)
            if (bit_cnt[j] == k)
                bin[j] = true;

        ans = std::max(ans, bin2dec(bin));
    }

    std::cout << max << " " << ans;
    return 0;
}