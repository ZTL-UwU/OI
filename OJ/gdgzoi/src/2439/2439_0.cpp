#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MOD = 49999;
// Huge int
class huge_int
{
public:
    string bits;
    void flip(string &a)
    {
        for (int i = 0; i < a.size() / 2; i++)
            swap(a[i], a[a.size() - i - 1]);
    }
    huge_int operator+(huge_int x)
    {
        huge_int res;
        string a = this->bits, b = x.bits;
        if (b.size() > a.size())
            swap(a, b);
        res.bits = a;
        while (a.size() - b.size())
            b = "0" + b;
        flip(a), flip(b);
        int carry = 0;
        for (int i = 0; i < a.size(); i++)
        {
            int bit = a[i] + b[i] - 2 * '0' + carry;
            res.bits[i] = (bit % 10) + '0';
            carry = bit / 10;
        }
        if (carry)
            res.bits += (carry + '0');
        flip(res.bits);
        return res;
    }
    int operator[](int x)
    {
        return this->bits[x] - '0';
    }
    friend ostream &operator<<(ostream &os, const huge_int &x)
    {
        os << x.bits;
        return os;
    }
};
// Link hash
class link_hash
{
public:
    struct data
    {
        int sta;
        huge_int val;
    };
    vector<data> v[MOD];
    int size = 0;
    huge_int &operator[](const int sta)
    {
        int key = sta % MOD;
        for (int i = 0; i < v[key].size(); i++)
        {
            if (v[key][i].sta == sta)
                return v[key][i].val;
            if (i == v[key].size() - 1)
            {
                huge_int tmp;
                tmp.bits = "0";
                v[key].push_back((data){sta, tmp});
                size++;
                i = 0;
            }
        }
    }
};
link_hash dp[2];
// DP transfer
void transfer(int x, int y)
{
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            transfer(i, j);
        if ()
    }
    return 0;
}