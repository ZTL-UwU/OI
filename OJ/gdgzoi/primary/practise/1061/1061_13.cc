#include <algorithm>
#include <iostream>
#include <cstring>
#include <sstream>

const int MAX_NUM_LEN = 4e4;

class huge_int
{
public:
    huge_int();

    huge_int operator*(const int val);
    huge_int operator/(const int val);

    int base[MAX_NUM_LEN];
    int size;
};

huge_int::huge_int()
{
    std::memset(this->base, 0, sizeof(this->base));
    this->size = 0;
}

huge_int huge_int::operator*(const int val)
{
    huge_int res;
    res.size = this->size;

    for (int i = 0; i < this->size; i++)
        res.base[i] = this->base[i] * val;

    for (int i = 0; i < res.size; i++)
    {
        if (res.base[i] >= 10)
        {
            res.base[i + 1] += res.base[i] / 10;
            res.base[i] %= 10;

            if (i == res.size - 1)
                res.size++;
        }
    }

    return res;
}

huge_int huge_int::operator/(const int val)
{
    huge_int res;

    int x = 0;
    for (int i = 0; i < this->size; i++)
    {
        x = x * 10 + this->base[i];

        if (x / val > 0)
        {
            res.base[res.size++] = x / val;
            x %= val;
        }
        else if (res.size != 0)
            res.size++;
    }

    return res;
}

std::ostream &put_huge_int(std::ostream &os, const huge_int &val)
{
    for (int i = 0; i < val.size; i++)
        os.put(val.base[i] + '0');

    return os;
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    huge_int ans;
    ans.base[0] = 1;
    ans.size = 1;

    for (int i = m + 1; i <= n + m; i++)
        ans = ans * i;
    ans = ans * (n + 1 - m);

    std::reverse(ans.base, ans.base + ans.size);

    for (int i = 1; i <= n + 1; i++)
        ans = ans / i;

    put_huge_int(std::cout, ans);
    return 0;
}