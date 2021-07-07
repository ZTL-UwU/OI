#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

const int STEP[4] = {0, 1, 12, 720};
const int INF = 0x7fffffff;
const int MAX_NODE = 43200;

bool is_prime[MAX_NODE + 10];
std::vector<int> prime;

int dis(const int p, const int tar, const int step, const bool dir)
{
    if ((int)std::abs(p - tar) % step != 0)
        return -1;

    const int tmp_dis = dir ? tar - p : p - tar;
    return (tmp_dis < 0 ? MAX_NODE + tmp_dis : tmp_dis) / step;
}

void get_prime()
{
    for (int i = 0; i <= MAX_NODE + 9000; i++)
        is_prime[i] = true;

    for (int i = 2; i <= MAX_NODE; i++)
    {
        if (is_prime[i])
            prime.push_back(i);

        for (int j = 2; j <= MAX_NODE / i; j++)
            is_prime[i * j] = false;
    }
}

int factor1[MAX_NODE + 10000];
int factor2[MAX_NODE + 10000];
int factor3[MAX_NODE + 10000];

void get_fac(int dis, int num)
{
    int last = 0;
    while (dis > 1)
    {
        for (std::size_t i = last; i < prime.size(); i++)
        {
            if (dis % prime[i] == 0)
            {
                dis /= prime[i];

                if (num == 1)
                    factor1[prime[i]]++;
                if (num == 2)
                    factor2[prime[i]]++;
                if (num == 3)
                    factor3[prime[i]]++;

                last = i;
                break;
            }
        }
    }
}

long long int common(int dis1, int dis2, int dis3)
{
    get_fac(dis1, 1);
    get_fac(dis2, 2);
    get_fac(dis3, 3);

    long long int res = 1;
    for (int i = 0; i < prime.size(); i++)
    {
        if (prime[i] > dis1 && prime[i] > dis2 && prime[i] > dis3)
            break;

        res *= std::pow(prime[i], std::max(std::max(factor1[prime[i]], factor2[prime[i]]), factor3[prime[i]]));
    }

    if (res < 0)
        return INF;
    return res;
}

int main()
{
    std::freopen("rescue.in", "r", stdin);
    std::freopen("rescue.out", "w", stdout);

    get_prime();

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        int p1, p2, p3, tar1, tar2, tar3;
        std::cin >> p1 >> p2 >> p3 >> tar1 >> tar2 >> tar3;

        bool flag = true;
        long long int min = INF;
        for (int i = 0; i < MAX_NODE; i++)
        {
            const int tar1_new = (tar1 + i) % MAX_NODE;
            const int tar2_new = (tar2 + i) % MAX_NODE;
            const int tar3_new = (tar3 + i) % MAX_NODE;

            const int dis_c1 = dis(p1, tar1_new, STEP[1], true);
            const int dis_c2 = dis(p2, tar2_new, STEP[2], true);
            const int dis_c3 = dis(p3, tar3_new, STEP[3], true);

            const int dis_rev_c1 = dis(p1, tar1_new, STEP[1], false);
            const int dis_rev_c2 = dis(p2, tar2_new, STEP[2], false);
            const int dis_rev_c3 = dis(p3, tar3_new, STEP[3], false);

            if ((dis_c1 != -1 && dis_c2 != -1 && dis_c3 != -1)
                || (dis_rev_c1 != -1 && dis_rev_c2 != -1 && dis_rev_c3 != -1))
            {
                flag = false;

                if (dis_c1 != -1 && dis_c2 != -1 && dis_c3 != -1)
                    min = std::min(min, common(dis_c1, dis_c2, dis_c3));
                if (dis_rev_c1 != -1 && dis_rev_c2 != -1 && dis_rev_c3 != -1)
                    min = std::min(min, common(dis_rev_c1, dis_rev_c2, dis_rev_c3));
            }
        }

        if (flag)
            std::cout << "ERROR\n";
        else
            std::cout << min << "\n";
    }
    return 0;
}