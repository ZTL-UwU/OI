#include <iostream>
#include <vector>
#include <cstdio>

const int MAX_N = 1e6 + 10;

std::vector<bool> s_bin[MAX_N];
int s[MAX_N];

std::vector<bool> dec2bin(int n)
{
	std::vector<bool> res;

	while (n)
	{
		res.push_back(n % 2);
		n /= 2;
	}

	return res;
}

int bin2dec(const std::vector<bool> &bin)
{
	int res = 0;
	int bit_num = 1;
	for (std::size_t i = 0; i < bin.size(); i++)
	{
		res += bin[i] * bit_num;
		bit_num *= 2;
	}

	return res;
}

int main()
{
	std::freopen("ihp.in", "r", stdin);
	std::freopen("ihp.out", "w", stdout);

	int n, k;
	std::scanf("%d %d", &n, &k);

	int max = -1;
	for (int i = 0; i < n; i++)
	{
		std::scanf("%d", &s[i]);
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

		std::vector<bool> bin;
		bin.resize(bit_cnt.size());
		std::fill(bin.begin(), bin.end(), false);
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

		std::vector<bool> bin;
		bin.resize(bit_cnt.size());
		std::fill(bin.begin(), bin.end(), false);
		for (std::size_t j = 0; j < bit_cnt.size(); j++)
			if (bit_cnt[j] == k)
				bin[j] = true;

		ans = std::max(ans, bin2dec(bin));
	}

	std::cout << max << " " << ans;
	return 0;
}