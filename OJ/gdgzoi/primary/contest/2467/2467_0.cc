#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

const bool BOY = false;
const bool GIRL = true;

struct student
{
    bool gender;
    bool prefer_higher;
    int height;
};

std::vector<student> v;

inline bool cmp(student a, student b) { return a.height < b.height; }

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        int height;
        std::cin >> height;
        v.push_back((student){BOY, height > 0, std::abs(height)});
    }
    for (int i = 0; i < n; i++)
    {
        int height;
        std::cin >> height;
        v.push_back((student){GIRL, height > 0, std::abs(height)});
    }

    std::sort(v.begin(), v.end(), cmp);

    int p[2] = {0, 0};
    int ans = 0;
    for (size_t i = 0; i < v.size(); i++)
    {
        student u = v[i];

        if (!u.prefer_higher)
            continue;

        if (p[u.gender] < i)
            p[u.gender] = i;
        for (size_t j = p[u.gender] + 1; j < v.size(); j++)
        {
            if (!v[j].prefer_higher)
            {
                p[u.gender] = j;
                ans++;
                break;
            }
        }
    }

    std::cout << ans;
    return 0;
}