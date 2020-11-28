#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <stack>

const int MAX_N = 1e4;

int q_dec[MAX_N];
int ans[MAX_N];
int num[MAX_N];

inline int bin_to_dec(std::string str)
{
    int res = 0;

    int k = 1;
    for (int i = str.size() - 1; i >= 0; i--)
    {
        res += (str[i] - '0') * k;
        k *= 2;
    }

    return res;
}

inline std::string dec_to_bin(int num)
{
    std::stack<char> tmp;

    while (num)
    {
        tmp.push(num % 2 + '0');
        num /= 2;
    }

    std::string res;
    while (!tmp.empty())
    {
        std::string t;
        t.resize(1);
        t[0] = tmp.top();
        tmp.pop();

        res += t;
    }

    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;

    for (int i = 0; i < n; i++)
    {
        std::string tmp;
        std::cin >> tmp;

        num[i] = bin_to_dec(tmp);
    }

    for (int i = 0; i < q; i++)
    {
        std::string tmp;
        std::cin >> tmp;
        q_dec[i] = bin_to_dec(tmp);
    }

    for (int i = 0; i <= 1 << n; i++)
    {
        std::string t = dec_to_bin(i);

        std::stringstream ss;
        ss << std::setw(n) << std::setfill('0') << t;
        ss >> t;

        int res = 0;
        for (size_t j = 0; j < t.size(); j++)
        {
            char c = t[j];
            if (c == '0')
                res = res | num[j];
            else
                res = res & num[j];
        }

        for (int j = 0; j < q; j++)
            if (res == q_dec[j])
                ans[j]++;
    }

    for (int i = 0; i < q; i++)
        std::cout << ans[i] << "\n";
    return 0;
}