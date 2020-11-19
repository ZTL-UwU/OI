#include <iostream>
#include <cstdio>

const int MAX_N = 1e3 + 10;
const int MOD = 1e3;

class huge_int
{
private:
    void flip(std::string &str)
    {
        for (int i = 0; i < str.size() / 2; i++)
            std::swap(str[i], str[str.size() - i - 1]);
    }

public:
    std::string bits;
    huge_int operator+(const huge_int x)
    {
        huge_int res;

        std::string a;
        std::string b;
        a = this->bits;
        b = x.bits;

        if (b.size() > a.size())
            swap(a, b);
        std::string c = a;
        while (a.size() - b.size() > 0)
            b = "0" + b;

        this->flip(a);
        this->flip(b);
        int carry = 0;
        for (int i = 0; i < a.size(); i++)
        {
            int tmp = a[i] - '0' + b[i] - '0' + carry;
            c[i] = (tmp % 10) + '0';
            carry = tmp / 10;
        }

        if (carry)
            c += (carry + '0');
        this->flip(c);

        res.bits = c;
        return res;
    }

    void operator=(std::string x) { this->bits = x; }
    void operator=(huge_int x) { this->bits = x.bits; }
};

huge_int c[MAX_N][MAX_N];

int quick_power(long long int a, int n)
{
    long long int ans = 1;

    while (n != 0)
    {
        if (n % 2 == 1)
            ans = (ans * a) % MOD;

        a = (a * a) % MOD;
        n >>= 1;
    }

    return ans;
}

int main()
{
    int k, x;
    std::cin >> k >> x;

    x = quick_power(x, x);

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (j == 0 or i == j)
                c[i][j] = "1";

            else
                c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }

    std::cout << c[x - 1][k - 1].bits;
    return 0;
}
