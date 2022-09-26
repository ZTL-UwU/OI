#include <algorithm>
#include <iostream>
#include <queue>

const int MAX_N = 2.5e5 + 10;
using i64 = long long;
using pii = std::pair<i64, int>;

std::priority_queue<pii> pq;
bool used[MAX_N];
i64 a[MAX_N];
i64 b[MAX_N];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    for (int i = 0; i < n; i++)
        std::cin >> b[i];

    i64 tot = 0;
    i64 ans = 0;
    pii top;
    for (int i = 0; i < n; i++)
    {
        tot += a[i];
        if (!pq.empty())
            top = pq.top();
        if (tot < b[i] && !pq.empty() && top.first > b[i])
        {
            used[top.second] = false;
            tot += top.first;
            pq.pop();
            ans--;
        }
        if (tot >= b[i])
        {
            tot -= b[i];
            pq.push({b[i], i});
            used[i] = true;
            ans++;
        }
    }

    std::cout << ans << "\n";
    for (int i = 0; i < n; i++)
        if (used[i])
            std::cout << i + 1 << " ";
    return 0;
}