#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAXN = 1010;
int nxt[MAXN];
void get_nxt(string str)
{
    int j = 0;
    nxt[1] = 0;
    for (int i = 1; i < str.size() - 1; i++)
    {
        while (j && str[i + 1] != str[j + 1])
            j = nxt[j];
        if (str[i + 1] == str[j + 1])
            j++;
        nxt[i + 1] = j;
    }
}
int kmp(string str, string ptr)
{
    get_nxt(ptr);
    int j = 0, res = 0;
    for (int i = 0; i < str.size() - 1; i++)
    {
        while (j && str[i + 1] != ptr[j + 1])
            j = nxt[j];
        if (ptr[j + 1] == str[i + 1])
            j++;
        if (j == ptr.size() - 1)
            res++, j = 0;
    }
    return res;
}
int main()
{
    while (1)
    {
        string str, ptr;
        cin >> str;
        if (str == "#")
            return 0;
        cin >> ptr;
        str = "@" + str;
        ptr = "@" + ptr;
        cout << kmp(str, ptr) << "\n";
    }
    return 0;
}