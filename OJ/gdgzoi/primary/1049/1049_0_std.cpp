//题解
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define F(i, a, b) for (int i = (a); i <= (b); i++)
const int N = 2097152;
const int INF = 0x7fffffff;
int n, n2;
char s[N];
int v[N];
int len;
int nx[N];
char ans[N];
int main(void)
{
    F(c, 1, INF)
    {
        memset(s, 0, sizeof s);
        if (scanf("%s", s + 1) == EOF)
            break;
        n = strlen(s + 1);
        n2 = n + n;
        F(i, n + 1, n2)
            s[i] = s[i - n];
        memset(v, 0, sizeof v);
        F(x, 1, n2)
        {
            int d = x - 1;
            int y = x;
            while (y + 1 <= n2 && s[y] != s[y + 1])
                y++;
            len = y - x + 1;
            int j = nx[1] = 0;
            F(i, 2, len)
            {
                while (j > 0 && s[d + j + 1] != s[d + i])
                    j = nx[j];
                if (s[d + j + 1] == s[d + i])
                    j++;
                nx[i] = j;
            }
            for (int i = 1; i <= len + 10; i ++)
            {
                cout << nx[i] << " ";
            }
            cout << "\n";
            F(i, 1, len)
                v[i]++;
            for (int i = len; nx[i] > 0; i = nx[i])
                v[(len - nx[i]) + 1]--;
            x = y;
            memset(nx, 0, sizeof(nx[0]) * len);
            len = 0;
        }
        memset(ans, 0, sizeof ans);
        F(i, 0, n - 1)
            if (v[n - i] > 0)
                ans[i] = '1';
            else
                ans[i] = '0';
        ans[n] = '\n';
        printf("Case %d: %s", c, ans);
    }
    return 0;
}