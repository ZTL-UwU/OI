#include <iostream>

const int MAX_N = 1e6 + 10;
int a[MAX_N];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    
    long long int ans = 0;
    for (int i = 1; i < n; i++)
        ans += std::max(a[i - 1], a[i]);
    std::cout << ans;
    return 0;
}