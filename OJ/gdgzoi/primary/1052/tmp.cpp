#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAXN = 1e6 + 10;
int old_rnk[MAXN * 2];
int rnk[MAXN * 2];
int bsk[MAXN];
int suf[MAXN];
int sot[MAXN];
int tmp[MAXN];
string s;
string str;
int n, m, i, w, k;
//binary search
int check_bin()
{
    int size = s.size() - 1;
    for (int i = 0; i < size; i++)
    {
        if (s[i + 1] > str[i + 1])
            return 1;
        else if (s[i + 1] < str[i + 1])
            return 0;
    }
    return 2;
}
int main()
{
    cin >> str;
    str = "#" + str;
    int t;
    scanf("%d", &t);
    while (t--)
    {
        cin >> s;
        s = "#" + s;
        printf("%d ", check_bin());
    }
    return 0;
}