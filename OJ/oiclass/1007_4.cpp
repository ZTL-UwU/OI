#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 1000;
int v[MAXN], w[MAXN], value[MAXN];
int main()
{
    int val, m, n;
    cin >> val >> m >> n;
    for (int i = 0; i < n; i ++)
        cin >> v[i] >> w[i] >> value[i];
    for (int i = 0; i < n; i ++)
    {
        for (int j = val; j >= v[i]; j --)
        {
            
        }
    }
    return 0;
}