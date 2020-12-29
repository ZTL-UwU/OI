#include <iostream>
#include <string>

const int MAX_N = 1e2;

class huge_int
{
public:
    void operator=(int val);
    friend huge_int operator+(const huge_int &val1, const huge_int &val2);
    friend huge_int operator+(const huge_int &val1, const int val2);

    std::string to_string();

private:
    std::string _base;
};

void flip(std::string &str)
{
    for (std::size_t i = 0; i < str.size() / 2; i++)
        std::swap(str[i], str[str.size() - i - 1]);
}

void huge_int::operator=(int val) { this->_base = std::to_string(val); }

huge_int operator+(const huge_int &val1, const huge_int &val2)
{
    std::string a = val1._base;
    std::string b = val2._base;

    if (b.size() > a.size())
        swap(a, b);

    std::string c = a;
    while (a.size() - b.size() > 0)
        b = "0" + b;

    flip(a);
    flip(b);

    int carry = 0;
    for (std::size_t i = 0; i < a.size(); i++)
    {
        int tmp = a[i] - '0' + b[i] - '0' + carry;
        c[i] = (tmp % 10) + '0';
        carry = tmp / 10;
    }
    if (carry)
        c += (carry + '0');

    flip(c);

    huge_int res;
    res._base = c;
    return res;
}

huge_int operator+(const huge_int &val1, const int val2)
{
    huge_int tmp;
    tmp = val2;

    return val1 + tmp;
}

std::string huge_int::to_string() { return this->_base; }

huge_int dp[MAX_N + 10][MAX_N + 10];

int main()
{
    for (int n = 1; n <= MAX_N; n++)
    {
        for (int m = 1; m <= MAX_N; m++)
        {
            if (n == 1 and m == 1)
                dp[n][m] = 1;
            else if (n < m)
                dp[n][m] = dp[n][n];
            else if (n == m)
                dp[n][m] = dp[n][m - 1] + 1;
            else if (n > m)
                dp[n][m] = dp[n - m][m] + dp[n][m - 1];
        }

        std::cout << dp[n][n].to_string() << " ";
    }
    return 0;
}