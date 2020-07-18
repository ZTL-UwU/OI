#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 1e8 + 10;
char st[MAXN];
int top;
int ans;
int main()
{
    string a, b;
    cin >> a >> b;
    for (int i = 0; i < b.size(); i ++)
    {
        st[++ top] = b[i];
        if (top >= a.size())
        {
            bool flag = true;
            for (int i = 0; i < a.size(); i ++)
            {
                if (a[i] != st[top + i - a.size() + 1])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                ans ++;
                top -= a.size();
            }
        }
    }
    cout << ans;
    return 0;
}