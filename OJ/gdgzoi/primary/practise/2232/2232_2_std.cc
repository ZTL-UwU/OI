#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;
#define register

const int N = 100010;
const ll inf = 9000000000000000000;
int n, m, tot, hed[N], ver[N << 1], nex[N << 1], d[N], f[N][25], son[N], siz[N], tp[N], cnt, id[N], root, T;
ll a[N], vid[N], lz[N << 2], mi[N << 2], p, q;

// inline char gc()
// {
//     static char buf[1000001], *p1 = buf, *p2 = buf;
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
// }

template <class T>
inline void re(T &x)
{
    x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = x * 10 + (ch ^ 48), ch = getchar();
}

inline void add(int x, int y)
{
    ver[++tot] = y;
    nex[tot] = hed[x];
    hed[x] = tot;
}

void dfs1(int x)
{
    int i, y, sonsiz = -1;
    siz[x] = 1;
    for (i = 1; i <= T; ++i) //处理倍增数组
    {
        f[x][i] = f[f[x][i - 1]][i - 1];
        if (!f[x][i])
            break;
    }
    for (i = hed[x]; i; i = nex[i])
    {
        y = ver[i];
        if (siz[y])
            continue;
        f[y][0] = x;
        d[y] = d[x] + 1;
        dfs1(y);
        siz[x] += siz[y]; //处理父节点f[][0]，深度d，子树大小siz，重儿子son
        if (siz[y] > sonsiz)
            sonsiz = siz[y], son[x] = y;
    }
}

void dfs2(int x, int thtp)
{
    tp[x] = thtp;    //记录所在重链链顶
    id[x] = ++cnt;   //记录再标号
    vid[cnt] = a[x]; //记录每个标号对应的值
    if (!son[x])
        return;
    dfs2(son[x], thtp); //先处理重儿子
    int i, y;
    for (i = hed[x]; i; i = nex[i])
    {
        y = ver[i];
        if (y == f[x][0] || y == son[x])
            continue;
        dfs2(y, y); //每个轻儿子都是一个重链的链顶
    }
}

inline void update(int rt) { mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]); }

void build(int l, int r, int rt)
{
    if (l == r)
    {
        mi[rt] = vid[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    update(rt);
}

inline void pushdown(int rt) //线段树下推懒标记
{
    mi[rt << 1] = mi[rt << 1 | 1] = lz[rt];
    lz[rt << 1] = lz[rt << 1 | 1] = lz[rt];
    lz[rt] = 0;
}

void modify(int l, int r, int L, int R, int k, int rt) //线段树区间修改
{
    if (R < l || r < L)
        return;
    if (L <= l && r <= R)
    {
        mi[rt] = k;
        lz[rt] = k;
        return;
    }
    int mid = (l + r) >> 1;
    if (lz[rt])
        pushdown(rt);
    modify(l, mid, L, R, k, rt << 1);
    modify(mid + 1, r, L, R, k, rt << 1 | 1);
    update(rt);
}

ll query(int l, int r, int L, int R, int rt) //线段树区间查询最小值
{
    if (R < l || r < L)
        return inf;
    if (L <= l && r <= R)
        return mi[rt];
    int mid = (l + r) >> 1;
    if (lz[rt])
        pushdown(rt);
    return min(query(l, mid, L, R, rt << 1), query(mid + 1, r, L, R, rt << 1 | 1));
}

inline void adl(int x, int y, int k)
{
    while (tp[x] != tp[y])
    {
        if (d[tp[x]] < d[tp[y]])
            swap(x, y);                       //每次更新链顶深度大的
        modify(1, n, id[tp[x]], id[x], k, 1); //更新当前点到链顶
        x = f[tp[x]][0];                      //跳到链顶的父亲
    }
    if (d[x] < d[y])
        swap(x, y);
    modify(1, n, id[y], id[x], k, 1); //最后在一条重链上了，直接更新
}

inline int getfa(int x, int k)
{
    for (int i = T; i >= 0; --i)
        if (k >= (1 << i))
        {

            x = f[x][i], k -= (1 << i);
        }
    return x;
}

int main()
{
    int i, x, y, k, opt;
    re(n);
    re(m);
    T = (int)log2(n) + 1;
    for (i = 1; i < n; ++i)
    {
        re(x);
        re(y);
        add(x, y);
        add(y, x);
    }
    for (i = 1; i <= n; ++i)
        re(a[i]);
    d[1] = 1; //直接以1为根跑树剖
    dfs1(1);
    dfs2(1, 1);
    re(root);       //读入当前根
    build(1, n, 1); //建树

    while (m--)
    {
        re(opt);
        switch (opt)
        {
            case 1:
                re(root); //读入新根
                break;
            case 2:
                re(x);
                re(y);
                re(k);
                adl(x, y, k); //链更改
                break;
            case 3:
                y = 0;
                re(x);
                if (x == root)
                    // printf("%lld\n", mi[1]); //是当前根节点，直接输出全局最小值
                    std::cout << "";
                else if (d[x] < d[root] && f[y = getfa(root, d[root] - d[x] - 1)][0] == x) //如果x是root的祖先的话
                { //先找到了root在的x的子树的那个根
                    // p = query(1, n, 1, id[y] - 1, 1); // 1~id[y]的部分
                    // if (id[y] + siz[y] <= n)
                    //     q = query(1, n, id[y] + siz[y], n, 1); // id[y]+siz[y]~n的部分
                    // else
                    //     q = inf;
                    // printf("%lld\n", min(p, q)); //取min
                    std::cout << "";
                }
                else //否则直接更改x子树
                    std::cout << "";
                // printf("%lld\n", query(1, n, id[x], id[x] + siz[x] - 1, 1));
                std::cout << " " << d[x] << " " << d[root] << " " << y << "\n";
                break;
        }
    }
    return 0;
}