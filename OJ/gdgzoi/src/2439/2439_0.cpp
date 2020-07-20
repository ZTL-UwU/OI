#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MOD = 49999;
int n, m;
class huge_int
{
public:
    string bits;
    void flip(string &a) { for (int i = 0; i < a.size() / 2; i++) swap(a[i], a[a.size() - i - 1]); }
    huge_int operator+(huge_int x)
    {
        huge_int res;
        string a = this->bits, b = x.bits;
        if (b.size() > a.size()) swap(a, b);
        res.bits = a;
        while (a.size() - b.size()) b = "0" + b;
        flip(a), flip(b);
        int carry = 0;
        for (int i = 0; i < a.size(); i++)
        {
            int bit = a[i] + b[i] - 2 * '0' + carry;
            res.bits[i] = (bit % 10) + '0';
            carry = bit / 10;
        }
        if (carry) res.bits += (carry + '0');
        flip(res.bits);
        return res;
    }
    void operator=(huge_int x) { this->bits = x.bits; }
    void operator+=(huge_int x) { *this = *this + x; }
    int operator[](int x) { return this->bits[x] - '0'; }
    friend ostream &operator<<(ostream &os, const huge_int &x) { os << x.bits; return os; }
};
class link_hash
{
public:
    struct data { int key; huge_int val; };
    vector<data> v[MOD];
    int size = 0;
    huge_int &operator[](const int sta)
    {
        int key = sta % MOD;
        for (int i = 0; i < v[key].size(); i++)
        {
            if (v[key][i].key == sta) return v[key][i].val;
            if (i == v[key].size() - 1)
            {
                huge_int tmp;
                tmp.bits = "0";
                v[key].push_back((data){sta, tmp});
                size++;
            }
        }
    }
};
link_hash dp[2];
void set(int &sta, int x, int val) { x = (x - 1) << 1, sta |= (3 << x), sta ^= (3 << x), sta |= (val << x); }
int type(int sta, int x) { return (sta >> ((x - 1) << 1)) & 3; }
int link(int sta, int x)
{
    int num = 0, delta = (type(sta, x) == 1 ? 1 : -1);
    for (int i = x; i && i <= m + 1; i += delta)
    {
        int y = type(sta, i);
        if (y == 1) num++;
        else if (y == 2) num--;
        if (!num) return i;
    }
    return -1;
}
void transfer(int x, int y)
{
    int now = ((x - 1) * m + y) & 1;
    int last = !now;
    for (int i = 0; i < MOD; i++)
    {
        for (int j = 0; j < dp[now].v[i].size(); j++)
        {
            int sta = dp[now].v[i][j].key;
            huge_int val = dp[now].v[i][j].val;
            int left = type(sta, y), up = type(sta, y + 1);
            if (link(sta, y) == -1 || link(sta, y + 1) == -1) continue;
            if (!left && !up) // Case 1
                if (x != n && y != m) set(sta, y, 1), set(sta, y + 1, 2), dp[now][sta] += val;
            else if (left && !up)
            {
                if (x != n) dp[now][sta] += val;
                if (y != m) set(sta, y, 0), set(sta, y + 1, left), dp[now][sta] += val;
            }
            else if (!left && up)
            {
                if (x != n) set(sta, y, up), set(sta, y + 1, 0), dp[now][sta] += val;
                if (y != m) dp[now][sta] += val;
            }
            else if (left == 1 && up == 1)
                set(sta, link(sta, y + 1), 1), set(sta, y, 0), set(sta, y + 1, 0), dp[now][sta] += val;
            else if (left == 1 && up == 2) if (x == n && y == m) ans += val;
            else if (left == 2 && up == 1) set(sta, y, 0), set(sta, y + 1, 0), dp[now][sta] += val;
            else if (left == 2 && up == 2)
                set(sta, link(sta, y + 1), 2), set(sta, y, 0), set(sta, y + 1, 0), dp[now][sta] += val;
        }
    }
}
huge_int ans;
int main()
{
    cin >> n >> m;
    if (m > n) swap(n, m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            transfer(i, j);
        if (i != n)
        {
            int now = (i * m) & 1;
            for (int j = 0; j < MOD; j++
                for (int k = 0; k < dp[now].v[j].size(); k++)
                    dp[now].v[j][k].key <<= 2;
        }
    }
    ans = ans + ans;
    cout << ans;
    return 0;
}