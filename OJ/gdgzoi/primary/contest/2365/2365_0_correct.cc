#include <iostream>
#include <cstdio>

const int MAXN = 5e4 + 10;
const int HASH = 4194303;
const int MAX_HASH = HASH * 3;
std::pair<int, int> hash[MAX_HASH];
int head[HASH + 1];
int value[MAXN];
int tot;
int ans;

inline void add(int key)
{
    ++tot;
    hash[tot].first = key;
    hash[tot].second = head[key & HASH];
    head[key & HASH] = tot;
}

inline bool check(int key)
{
    for (int i = head[key & HASH]; i != 0; i = hash[i].second)
        if (hash[i].first == key)
            return true;

    return false;
}

int main()
{
    int n;
    std::scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        std::scanf("%d", &value[i]);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            if (check(value[i] - value[j]))
            {
                ++ans;
                break;
            }
        }

        for (int j = 1; j <= i; ++j)
            add(value[i] + value[j]);
    }

    std::printf("%d", ans);
}