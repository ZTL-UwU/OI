#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 1e6 + 10;
char st[MAXN];
char a[MAXN];
char b[MAXN];
int top;
int ans;
int main()
{
    int sa, sb;
    sa = sb = 0;
    while (1)
    {
        char tmp = getchar();
        if (tmp == '\n') break;
        b[sb ++] = tmp;
    }
    while (1)
    {
        char tmp = getchar();
        if (tmp == '\n') break;
        a[sa ++] = tmp;
    }
    for (int i = 0; i < sb; ++ i)
    {
        st[++ top] = b[i];
        if (top >= sa)
        {
            bool flag = true;
            for (int i = 0; i < sa; ++ i)
            {
                if (a[i] != st[top + i - sa + 1])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                top -= sa;
        }
    }
    for (int i = 1; i <= top; ++ i)
    {
        char tmp = st[i];
        putchar(tmp);
    }
    return 0;
}