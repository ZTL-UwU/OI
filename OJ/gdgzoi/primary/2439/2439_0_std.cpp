#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
const int cube = (int)1e9, mod = 2601;
int n, m;
// struct Data_Analysis
// {
//     int bit[6];
//     inline void Clear()
//     {
//         memset(bit, 0, sizeof(bit));
//     }
//     Data_Analysis()
//     {
//         Clear();
//     }
//     inline void Set(int t)
//     {
//         Clear();
//         while (t)
//             bit[++bit[0]] = t % cube, t /= cube;
//     }
//     inline int &operator[](int x)
//     {
//         return bit[x];
//     }
//     inline void Print()
//     {
//         printf("%d", bit[bit[0]]);
//         for (int i = bit[0] - 1; i > 0; i--)
//             printf("%09d", bit[i]);
//         printf("\n");
//     }
//     inline Data_Analysis operator+(Data_Analysis b)
//     {
//         Data_Analysis c;
//         c.Clear();
//         c[0] = max(bit[0], b[0]) + 1;
//         for (int i = 1; i <= c[0]; i++)
//             c[i] += bit[i] + b[i], c[i + 1] += c[i] / cube, c[i] %= cube;
//         while (!c[c[0]])
//             c[0]--;
//         return c;
//     }
//     inline void operator+=(Data_Analysis b)
//     {
//         *this = *this + b;
//     }
//     inline void operator=(int x)
//     {
//         Set(x);
//     }
// } Ans;


class huge_int
{
public:
    string bits;
    huge_int() { bits = "0"; }
    inline void flip(string &a)
    {
        for (int i = 0; i < a.size() / 2; i++)
            swap(a[i], a[a.size() - i - 1]);
    }
    inline huge_int operator+(const huge_int x)
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
        if (!res.bits.size())
            res.bits = "0";
        return res;
    }
    inline void operator=(const huge_int x) { this->bits = x.bits; }
    inline void operator+=(const huge_int x) { *this = (*this + x); }
    friend ostream &operator<<(ostream &os, const huge_int &x)
    {
        os << x.bits;
        return os;
    }
};

huge_int Ans;


// struct Hash_Sheet
// {
//     Data_Analysis val[mod];
//     int key[mod], size, hash[mod];
//     inline void Initialize()
//     {
//         memset(val, 0, sizeof(val)), memset(key, -1, sizeof(key));
//         size = 0, memset(hash, 0, sizeof(hash));
//     }
//     inline void Newhash(int id, int v)
//     {
//         hash[id] = ++size, key[size] = v;
//     }
//     Data_Analysis &operator[](const int State)
//     {
//         for (int i = State % mod;; i = (i + 1 == mod) ? 0 : i + 1)
//         {
//             if (!hash[i])
//                 Newhash(i, State);
//             if (key[hash[i]] == State)
//                 return val[hash[i]];
//         }
//     }
// } f[2];


const int MOD = 49999;
class link_hash
{
public:
    struct data
    {
        int key;
        huge_int val;
    };
    vector<data> v[MOD];
    inline huge_int &operator[](int sta)
    {
        int key = sta % MOD;
        for (int i = 0; i < v[key].size(); i++)
            if (v[key][i].key == sta)
                return v[key][i].val;
        huge_int tmp;
        v[key].push_back((data){sta, tmp});
        return v[key][v[key].size() - 1].val;
    }
    inline void init()
    {
        for (int i = 0; i < MOD; i++)
        {
            v[i].clear();
            v[i].shrink_to_fit();
        }
    }
};
link_hash f[2];

inline int Find(int sta, int x) { return (sta >> ((x - 1) << 1)) & 3; }
// inline int Find(int State, int id)
// {
//     return (State >> ((id - 1) << 1)) & 3;
// }
inline void Set(int &sta, int x, int val)
{
    x = (x - 1) << 1;
    sta |= 3 << x;
    sta ^= 3 << x;
    sta |= val << x;
}
// inline void Set(int &State, int bit, int val)
// {
//     bit = (bit - 1) << 1;
//     State |= 3 << bit, State ^= 3 << bit, State |= val << bit;
// }
inline int link(int sta, int x)
{
    int num = 0, delta = ((Find(sta, x) == 1) ? 1 : -1);
    for (int i = x; i && i <= m + 1; i += delta)
    {
        int y = Find(sta, i);
        if (y == 1)
            num++;
        else if (y == 2)
            num--;
        if (!num)
            return i;
    }
    return -1;
}
// inline int Link(int State, int pos)
// {
//     int cnt = 0, Delta = (Find(State, pos) == 1) ? 1 : -1;
//     for (int i = pos; i && i <= m + 1; i += Delta)
//     {
//         int plug = Find(State, i);
//         if (plug == 1)
//             cnt++;
//         else if (plug == 2)
//             cnt--;
//         if (cnt == 0)
//             return i;
//     }
//     return -1;
// }
inline void Execution(int x, int y)
{
    int now = ((x - 1) * m + y) & 1, last = now ^ 1;
    f[now].init();
    for (int i = 0; i < MOD; i++)
    {
        for (int j = 0; j < f[last].v[i].size(); j++)
        {
            int State = f[last].v[i][j].key;
            huge_int Val = f[last].v[i][j].val;
            int plug1 = Find(State, y), plug2 = Find(State, y + 1);
            if (link(State, y) == -1 || link(State, y + 1) == -1)
                continue;
            if (!plug1 && !plug2)
            {
                if (x != n && y != m)
                    Set(State, y, 1), Set(State, y + 1, 2), f[now][State] += Val;
            }
            else if (plug1 && !plug2)
            {
                if (x != n)
                    f[now][State] += Val;
                if (y != m)
                    Set(State, y, 0), Set(State, y + 1, plug1), f[now][State] += Val;
            }
            else if (!plug1 && plug2)
            {
                if (y != m)
                    f[now][State] += Val;
                if (x != n)
                    Set(State, y, plug2), Set(State, y + 1, 0), f[now][State] += Val;
            }
            else if (plug1 == 1 && plug2 == 1)
                Set(State, link(State, y + 1), 1), Set(State, y, 0), Set(State, y + 1, 0), f[now][State] += Val;
            else if (plug1 == 1 && plug2 == 2)
            {
                if (x == n && y == m)
                    Ans += Val;
            }
            else if (plug1 == 2 && plug2 == 1)
                Set(State, y, 0), Set(State, y + 1, 0), f[now][State] += Val;
            else if (plug1 == 2 && plug2 == 2)
                Set(State, link(State, y), 2), Set(State, y, 0), Set(State, y + 1, 0), f[now][State] += Val;
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    if (n == 1 || m == 1)
    {
        printf("1\n");
        return 0;
    }
    if (m > n)
        swap(n, m);
    f[0].init();
    huge_int tmp;
    tmp.bits = "1";
    f[0][0] = tmp;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            Execution(i, j);
        if (i != n)
        {
            int now = (i * m) & 1;
            for (int j = 0; j < MOD; j++)
                for (int k = 0; k < f[now].v[j].size(); k++)
                    f[now].v[j][k].key <<= 2;
        }
    }
    Ans += Ans;
    cout << Ans;
    return 0;
}