#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        double ans = 0;
        for (int i = 0; i < n; i++)
        {
            int b;
            double c;
            scanf("%d %lf", &b, &c);
            cout << (c + 0.0) / (b + c) << "\n";
            ans = max(ans, (c + 0.0) / (b + c + 0.0));
        }
        // printf("%lf\n", ans);
    }
    return 0;
}