#include <algorithm>
#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 1e5 + 10;
int a[MAXN];
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    int same = 0;
    for (int i = 0; i < n; i++)
        if (a[i] == a[i + 1])
            same++;
    if (same >= k)
        cout << n - same;
    else
        cout << n - k;
    return 0;
}