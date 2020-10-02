#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>

class huge_int
{
private:
    std::string bits;

    inline void flip(std::string &str)
    {
        for (size_t i = 0; i < str.size() / 2; i++)
            std::swap(str[i], str[str.size() - i - 1]);
    }

public:
    friend std::ostream &operator<<(std::ostream &os, const huge_int &x)
    {
        os << x.bits;
        return os;
    }

    inline void operator=(int x)
    {
        while (x)
        {
            std::string tmp = "#";
            tmp[0] = x % 10 + '0';
            this->bits = tmp + this->bits;
            x /= 10;
        }
    }

    inline huge_int operator+(const huge_int x)
    {
        std::string a_str = this->bits;
        std::string b_str = x.bits;

        if (b_str.size() > a_str.size())
            std::swap(a_str, b_str);

        std::string c = a_str;
        while (a_str.size() - b_str.size() > 0)
            b_str = "0" + b_str;
        flip(a_str);
        flip(b_str);

        int carry = 0;
        for (size_t i = 0; i < a_str.size(); i++)
        {
            int tmp = a_str[i] - '0' + b_str[i] - '0' + carry;
            c[i] = (tmp % 10) + '0';
            carry = tmp / 10;
        }

        if (carry)
            c += (carry + '0');
        flip(c);

        huge_int res;
        res.bits = c;
        return res;
    }
};

const int MAXN = 1e3 + 10;
huge_int mp[2][MAXN];

inline void init_mp()
{
    mp[0][0] = 1;
    mp[1][0] = 1;

    for (int i = 1; i < MAXN; i++)
    {
        mp[0][i] = mp[0][i - 1] + mp[1][i - 1];
        mp[1][i] = mp[0][i] + mp[1][i - 1];
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int start, end;
    std::cin >> start >> end;

    init_mp();
    if (start % 2 == end % 2)
        std::cout << mp[0][end / 2 - start / 2];
    else if (start % 2 == 0)
        std::cout << mp[1][end / 2 - start / 2];
    else
        std::cout << mp[1][end / 2 - start / 2 - 1];
    return 0;
}