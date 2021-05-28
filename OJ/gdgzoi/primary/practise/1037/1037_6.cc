#include <iostream>
using namespace std;
long long dis(long long x, long long y) { return max(x, y) - min(x, y); }
long long v[20010];
long long place[20010];
int main()
{
    long long n;
    cin >> n;
    for (long long i = 0; i < n; i++)
        cin >> v[i] >> place[i];
    long long ans = 0;
    for (long long i = 0; i < n; i++)
        for (long long j = i + 1; j < n; j++)
            ans += max(v[i], v[j]) * dis(place[i], place[j]);
    cout << ans;
    return 0;
}