#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;
int nextt[MAXN];
void get_next(string str)
{
    nextt[0] = -1;
    int i = 0, k = -1;
    while (i < str.size())
    {
        if (k == -1 || str[i] == str[k])
            nextt[++i] = ++k;
        else
            k = nextt[k];
    }
}
void kmp(string str, string ptr)
{
    int i = 0, j = 0;
    get_next(ptr);
    while (i < str.size())
    {
        if (j == -1 || str[i] == ptr[j])
            i++, j++;
        else
            j = nextt[j];
        if (j == ptr.size())
            cout << i - j + 1 << "\n";
    }
}
int main()
{
    string str, ptr;
    cin >> str >> ptr;
    kmp(str, ptr);
    for (int i = 1; i <= ptr.size(); i++)
        cout << nextt[i] << " ";
    cout << "\n";
    return 0;
}