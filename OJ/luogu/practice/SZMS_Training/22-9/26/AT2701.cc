#include <iostream>

const int MAX_N = 2e5 + 10;
long long cnt[MAX_N];

int main()
{
    std::string str;
    std::cin >> str;

    for (char c : str)
        cnt[c - 'a']++;

    long long ans = str.size() * (str.size() - 1) / 2 + 1;
    for (char c = 'a'; c <= 'z'; c++)
        ans -= cnt[c - 'a'] * (cnt[c - 'a'] - 1) / 2;
    std::cout << ans;
    return 0;
}