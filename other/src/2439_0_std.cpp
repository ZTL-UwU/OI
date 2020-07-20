#include <bits/stdc++.h>
using namespace std;
const int databit = 1e9;
const int MOD = 2601;

int n, m;

struct data
{
    int bit[6];

    inline void clear()
    {
        memset(bit, 0, sizeof(bit));
    }

    inline void set(int x)
    {
        clear();
        while (x)
        {
            bit[++bit[0]] = x % databit;
            x /= databit;
        }
    }

    inline int &operator[](int x)
    {
        return bit[x];
    }

    inline data operator+(data b)
    {
        data c;
        c.clear();
        c[0] = max(bit[0], b[0]) + 1;
        for (int i = 1; i <= c[0]; i++)
            c[i] += bit[i] + b[i], c[i + 1] += c[i] / databit, c[i] %= databit;
        while (!c[c[0]])
            c[0]--;
        return c;
    }

    inline void operator+=(data b)
    {
        *this = *this + b;
    }

    inline void operator=(int x)
    {
        set(x);
    }

    inline void print()
    {
        printf("%d", bit[bit[0]]);
        for (int i = bit[0] - 1; i >= 1; i--)
        {
            printf("%09d", bit[i]);
        }
        puts("");
    }

    data()
    {
        clear();
    }
};

data ans;

struct hashmp
{
    data val[MOD];
    int key[MOD], sz, hash[MOD];

    inline void init()
    {
        memset(val, 0, sizeof(val));
        memset(key, -1, sizeof(key));
        sz = 0;
        memset(hash, 0, sizeof(hash));
    }

    inline void newhash(int id, int v)
    {
        hash[id] = ++sz;
        key[sz] = v;
    }

    inline data &operator[](int state)
    {
        for (int i = state % MOD;; i = (i + 1 == MOD) ? 0 : i + 1)
        {
            if (!hash[i])
                newhash(i, state);
            if (key[hash[i]] == state)
                return val[hash[i]];
        }
    }
};

hashmp dp[2];

inline int find(int state, int id)
{
    return (state >> ((id - 1) << 1)) & 3;
}

inline void dpset(int &state, int bit, int val)
{
    bit = (bit - 1) << 1;
    state |= 3 << bit;
    state ^= 3 << bit;
    state |= val << bit;
}

inline int link(int state, int pos)
{
    int cnt = 0, delta = (find(state, pos) == 1) ? 1 : -1;
    for (int i = pos; i && i <= m + 1; i += delta)
    {
        int p = find(state, i);
        if (p == 1)
            cnt++;
        else if (p == 2)
            cnt--;
        if (cnt == 0)
            return i;
    }
    return -1;
}

inline void run(int x, int y)
{
    int now = ((x - 1) * m + y) & 1, last = now ^ 1, tot = dp[last].sz;
    dp[now].init();
    for (int i = 1; i <= tot; i++)
    {
        int state = dp[last].key[i];
        data val = dp[last].val[i];
        int p1 = find(state, y), p2 = find(state, y + 1);
        if (link(state, y) == -1 || link(state, y + 1) == -1)
            continue;
        if (!p1 && !p2 && x != n && y != m)
        {
            dpset(state, y, 1);
            dpset(state, y + 1, 2);
            dp[now][state] += val;
        }
        else if (p1 && !p2)
        {
            if (x != n)
                dp[now][state] += val;
            if (y != m)
            {
                dpset(state, y, 0);
                dpset(state, y + 1, p1);
                dp[now][state] += val;
            }
        }
        else if (!p1 && p2)
        {
            if (y != m)
                dp[now][state] += val;
            if (x != n)
            {
                dpset(state, y, p2);
                dpset(state, y + 1, 0);
                dp[now][state] += val;
            }
        }
        else if (p1 == 1 && p2 == 1)
        {
            dpset(state, link(state, y + 1), 1);
            dpset(state, y, 0);
            dpset(state, y + 1, 0);
            dp[now][state] += val;
        }
        else if (p1 == 1 && p2 == 2)
        {
            if (x == n && y == m)
                ans += val;
        }
        else if (p1 == 2 && p2 == 1)
        {
            dpset(state, y, 0);
            dpset(state, y + 1, 0);
            dp[now][state] += val;
        }
        else if (p1 == 2 && p2 == 2)
        {
            dpset(state, link(state, y), 2);
            dpset(state, y, 0);
            dpset(state, y + 1, 0);
            dp[now][state] += val;
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    if (n == 1 || m == 1)
    {
        puts("1");
        return 0;
    }
    if (m > n)
        swap(n, m);
    dp[0].init();
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            run(i, j);
        if (i != n)
        {
            int now = (i * m) & 1, tot = dp[now].sz;
            for (int j = 1; j <= tot; j++)
                dp[now].key[j] <<= 2;
        }
    }
    ans += ans;
    ans.print();
    return 0;
}