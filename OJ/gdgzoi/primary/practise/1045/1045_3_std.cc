#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 1050
#define MAXQ 20050
#define INF 999999
using namespace std;
int r, c, d, cnt = 0, acnt = 0, ans = 0;
int num[21][21]; //用来记录每个有石柱的点的编号；
int a[MAXQ];
int map[MAXN][MAXN], in[25][25]; // map是矩阵图，记录点与点联系；in是石柱高度；
int p[MAXQ], q[MAXQ];
void makePic(int x, int y) //搜索有直接联系的边建图
{
    int i, j;
    int now = num[x][y] + 1;
    for (i = 1; i <= r; i++)
        for (j = 1; j <= c; j++)
        {
            if ((i != x || j != y) && (in[i][j] > 0) && d * d >= (x - i) * (x - i) + (y - j) * (y - j))
                map[now][num[i][j]] = INF;
        }
}

void escape() //判断该石柱是否可以出逃
{
    int i, j;
    for (i = 1; i <= r; i++)
        for (j = 1; j <= c; j++)
            if (i - d < 1 || i + d > r || j - d < 1 || j + d > c)
            {
                int now = num[i][j] + 1;
                map[now][cnt] = INF;
            }
}

int Maxflow() //模板
{
    int flow = 0;
    for (;;)
    {
        queue<int> Q;
        memset(p, -1, sizeof(p));
        Q.push(0);
        while (!Q.empty())
        {
            int now = Q.front();
            Q.pop();
            for (int i = 1; i <= cnt; i++)
                if (p[i] < 0 && map[now][i] > 0)
                {
                    Q.push(i);
                    p[i] = now;
                }
            if (p[cnt] > 0)
                break;
        }
        if (p[cnt] < 0)
            break;
        int minFlow = INF;
        for (int i = cnt; i != 0; i = p[i])
            minFlow = min(minFlow, map[p[i]][i]);
        for (int i = cnt; i != 0; i = p[i])
        {
            map[p[i]][i] -= minFlow;
            map[i][p[i]] += minFlow;
        }
        flow += minFlow;
    }
    return flow;
}

void init()
{
    int i, j;
    char s;
    cin >> r >> c >> d;
    for (i = 1; i <= r; i++)
        for (j = 1; j <= c; j++)
        {
            cin >> s;
            in[i][j] = s - 48; //石柱高度（该点是否有石柱）
            if (s != '0')
            {
                num[i][j] = ++cnt;
                map[cnt][cnt + 1] = s - 48;
                cnt++;
            } //石柱拆成俩点
        }

    for (i = 1; i <= r; i++)
        for (j = 1; j <= c; j++)
        {
            cin >> s;
            if (s == 'L')
            {
                acnt++;
                map[0][num[i][j]] = 1; //有蜥蜴的与源点连接
            }
            if (in[i][j] > 0)
                makePic(i, j); //每个石柱遍历建图（数据小）
        }
}
int main()
{
    init();
    cnt++;
    escape();
    cout << acnt - Maxflow() << endl;
    return 0;
}