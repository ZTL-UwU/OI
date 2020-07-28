#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAXN = 2e6 + 10;
int nextt[MAXN];
char str[MAXN];
int cnt[MAXN];
int main()
{
    int t = 0;
    while (1)
    {
        memset(str, 0, sizeof(str));
        memset(cnt, 0, sizeof(cnt));
        if (scanf("%s", str + 1) == EOF)
            return 0;
        int n = strlen(str + 1);
        int n2 = n * 2;
        for (int i = 1; i <= n; ++i)
            str[i + n] = str[i];
        ++t;
        for (int i = 1; i <= n2; ++i)
        {
            int start = i - 1;
            int end = i;
            while (end + 1 <= n2 && str[end] != str[end + 1])
                ++end;
            int len = end - start;
            nextt[1] = 0;
            int y = 0;
            for (int x = 2; x <= len; ++x)
            {
                while (y && str[start + x] != str[start + y + 1])
                    y = nextt[y];
                if (str[start + x] == str[start + y + 1])
                    ++y;
                nextt[x] = y;
            }
            for (int j = 1; j <= len; ++j)
                ++cnt[j];
            for (int j = len; nextt[j] > 0; j = nextt[j])
                --cnt[len - nextt[j] + 1];
            i = end;
            memset(nextt, 0, sizeof(nextt[0]) * len);
        }
        printf("Case %d: ", t);
        for (int i = 0; i < n; ++i)
            if (cnt[n - i])
                putchar('1');
            else
                putchar('0');
        puts("");
    }
    return 0;
}