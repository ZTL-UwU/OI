#include <iostream>

const int MAX_N = 1e6 + 10;
int cnt[MAX_N];

int main()
{
    std::string a, b;
    std::cin >> a >> b;

    for (char i : a)
        cnt[i - 'a']++;
    long long ans = 0;
    for (char i : b)
        ans += a.size() - cnt[i - 'a'] + 1;

    std::cout << ans + b.size() + 1;
    return 0;
}