#include <bits/stdc++.h>
using namespace std;
int nxt[1002], l_a, l_b;
char a[10002], b[10002];
void Next()
{
    int j = 0;
    nxt[1] = 0;
    for (int i = 1; i < l_b; i++)
    {
        while (j > 0 && b[j + 1] != b[i + 1])
        {
            j = nxt[j];
        }
        if (b[j + 1] == b[i + 1])
        {
            j++;
        }
        nxt[i + 1] = j;
    }
}
int kmp()
{
    int num, j;
    j = num = 0;
    for (int i = 0; i < l_a; i++)
    {
        while (j > 0 && b[j + 1] != a[i + 1])
        {
            j = nxt[j];
        }
        if (b[j + 1] == a[i + 1])
        {
            j++;
        }
        if (j == l_b)
        {
            num++;
            j = 0;
        }
    }
    return num;
}
int main()
{
    while (cin >> a + 1)
    {
        if (a[1] == '#' && strlen(a + 1) == 1)
        {
            return 0;
        }
        cin >> b + 1;
        l_a = strlen(a + 1);
        l_b = strlen(b + 1);
        Next();
        for (int i = 0; i <= l_b + 10; i ++)
            cout << nxt[i] << " ";
        cout << "\n";
        cout << kmp() << endl;
    }
    return 0;
}