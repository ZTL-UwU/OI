#include <iostream>
#include <vector>
#include <cstdio>

const int MAX_M = 1e5 + 100;
const int MAX_T = 2e5 + 100;

std::vector<int> ans;

int noise[MAX_T];
int mix[MAX_T];
int key[MAX_M];

int t, m;
int a, b, c, d, e;

void get_noise()
{
    for (int i = 1; i <= t; i++)
    {
        if (i == 1)
            noise[i] = a;
        else
            noise[i] = ((noise[i - 1] << b) + (noise[i - 1] >> c) + d) % e;
    }
}

int main()
{
    std::freopen("noise.in", "r", stdin);
    std::freopen("noise.out", "w", stdout);

    std::scanf("%d %d", &t, &m);
    std::scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);

    if (e != 1)
        get_noise();

    for (int i = 1; i <= t; i++)
        std::scanf("%d", &mix[i]);
    for (int i = 0; i < m; i++)
        std::scanf("%d", &key[i]);

    for (int i = 1; i <= t - m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mix[i + j] != (noise[i + j] + key[j]) % 256)
                break;
            if (j == m - 1)
                ans.push_back(i);
        }
    }

    if (ans.size() == 0)
        std::printf("wrong");
    else
    {
        std::printf("%d\n", ans.size());
        for (std::size_t i = 0; i < ans.size(); i++)
            std::printf("%d ", ans[i]);
    }

    return 0;
}