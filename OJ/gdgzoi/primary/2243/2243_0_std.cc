#include <cstdio>
#define MAXN 200005
struct SBT
{
    int v, sz, ch[2], cnt;
} t[MAXN];
int n, m, cnt, root;
#define Upd(k)                                                    \
    {                                                             \
        t[k].sz = t[t[k].ch[0]].sz + t[t[k].ch[1]].sz + t[k].cnt; \
    }
void rot(int &k, bool f)
{
    int p = t[k].ch[f];
    t[k].ch[f] = t[p].ch[!f];
    t[p].ch[!f] = k;
    Upd(k);
    Upd(p);
    k = p;
}
inline void mt(int &k, bool f)
{
    if (!k)
        return;
    if (t[t[k].ch[f ^ 1]].sz < t[t[t[k].ch[f]].ch[f]].sz)
        rot(k, f);
    else if (t[t[k].ch[f ^ 1]].sz < t[t[t[k].ch[f]].ch[f ^ 1]].sz)
    {
        rot(t[k].ch[f], f ^ 1);
        rot(k, f);
    }
    else
        return;
    mt(t[k].ch[f], f);
    mt(k, f);
}
void Ins(int &k, int x)
{
    if (!k)
    {
        k = ++cnt;
        t[k].sz = t[k].cnt = 1;
        t[k].v = x;
        return;
    }
    ++t[k].sz;
    if (t[k].v == x)
    {
        ++t[k].cnt;
        return;
    }
    Ins(t[k].ch[t[k].v < x], x);
    mt(k, t[k].v < x);
}
int Del(int &k, int x)
{
    if (!k)
        return k;
    int tmp;
    if (t[k].v == x)
    {
        if (t[k].cnt > 1)
        {
            --t[k].cnt;
            --t[k].sz;
            return k;
        }
        else if (!(t[k].ch[0] * t[k].ch[1]))
        {
            k = t[k].ch[0] + t[k].ch[1];
        }
        else
        {
            tmp = Del(t[k].ch[0], x + 1);
            t[k].cnt = t[tmp].cnt;
            t[k].v = t[tmp].v;
            Upd(k);
            return k;
        }
    }
    else if ((t[k].v < x && !t[k].ch[1]) || (t[k].v > x && !t[k].ch[0]))
    {
        tmp = k;
        k = t[k].ch[0];
        Upd(k);
        return tmp;
    }
    else
        tmp = Del(t[k].ch[t[k].v < x], x);
    Upd(k);
    return tmp;
}
int Kth(int k, int x)
{ //查询第k大
    if (x <= t[t[k].ch[1]].sz)
        return Kth(t[k].ch[1], x);
    else if (x > t[t[k].ch[1]].sz + t[k].cnt)
        return Kth(t[k].ch[0], x - t[t[k].ch[1]].sz - t[k].cnt);
    else
        return t[k].v;
}
char c, f;
inline void GET(int &n)
{
    n = 0;
    f = 1;
    do
    {
        c = getchar();
        if (c == '-')
            f = -1;
    } while (c > '9' || c < '0');
    while (c >= '0' && c <= '9')
    {
        n = n * 10 + c - '0';
        c = getchar();
    }
    n *= f;
}
/**********************并查集相关********************/
int fa[MAXN], num[MAXN];
int Q(int x)
{
    return x == fa[x] ? x : (fa[x] = Q(fa[x]));
}
void Union(int a, int b)
{
    int af = Q(a), bf = Q(b);
    if (af == bf)
        return;
    Del(root, num[af]);
    Del(root, num[bf]);
    fa[bf] = af;
    num[af] += num[bf];
    Ins(root, num[af]);
}
/***************************************************/
int main()
{
    GET(n);
    GET(m);
    int t1, t2, t3;
    Ins(root, 0x7f7f7f7f);
    Ins(root, -0x7f7f7f7f);
    for (int i = 1; i <= n; ++i)
        fa[i] = i, num[i] = 1, Ins(root, 1);
    while (m--)
    {
        GET(t1);
        GET(t2);
        if (t1)
            printf("%d\n", Kth(root, t2 + 1));
        else
        {
            GET(t3);
            Union(t2, t3);
        }
    }
}