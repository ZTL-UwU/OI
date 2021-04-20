#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int lit[10];
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++)
            scanf("%d", &lit[i]);
        if (n == 2)
        {
            puts("-1");
            continue;
        }
        if (m == 3)
            printf("%d\n", lit[1]);
        else if (m == 2)
        {
            if (lit[0] == 1)
                puts("-1");
            else
                printf("%d\n", lit[1]);
        }
        else
            printf("%d\n", lit[0]);
    }
    return 0;
}