#include<iostream>
#include<cstring>
using namespace std;
long long a[100010];
long long b[100010];
long long d[100010];
long long n, m, t;
int main()
{
    scanf("%lld", &t);
    while(t--)
    {
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        memset(d, 0, sizeof d);
        long long ans = 0;
        scanf("%lld%lld", &n, &m);
        for(long long i = 1; i <= n; i++)
        {
            scanf("%lld", &a[i]);
            b[a[i]]++;
        }
        for(long long i = 1; i <= 100009; i++)
        {
            b[i] += b[i - 1];
        }
        for(long long i = 1; i <= n; i++)
        {
            d[a[i]]++;
            ans = max(ans, i - b[a[i] - 1] - d[a[i]]);
        }
        printf("%lld\n", (ans + m - 2) / (m - 1));
    }
}