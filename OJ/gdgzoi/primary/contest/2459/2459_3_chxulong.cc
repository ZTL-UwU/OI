#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int N;
vector<int> SL, SR;
vector<pair<int, int>> L, R, tmp;
vector<bool> ans;
int res;

vector<pair<int, int>> calc(const vector<int> &S)
{
    int M = S.size();
    tmp.clear();
    for (int i = 0; i < (1 << M); i++)
    {
        for (int j = i;; j = (j - 1) & i)
        {
            int sum = 0;
            for (int k = 0; k < M; k++)
            {
                if (j & (1 << k))
                    sum -= S[k];
                else if (i & (1 << k))
                    sum += S[k];
            }
            if (sum >= 0)
                tmp.push_back(make_pair(sum, i));
            if (j == 0)
                break;
        }
    }
    sort(tmp.begin(), tmp.end());
    tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
    return tmp;
}

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        int x;
        scanf("%d", &x);
        if (i & 1)
            SL.push_back(x);
        else
            SR.push_back(x);
    }

    L = calc(SL), R = calc(SR);
    int LC = L.size(), RC = R.size(), SLC = SL.size();
    int p = 0, q = 0;
    ans.resize(1 << N);
    while (p < LC && q < RC)
    {
        if (L[p].first < R[q].first)
            p++;
        else if (L[p].first > R[q].first)
            q++;
        else
        {
            int pp = p, qq = q;
            while (pp < LC && L[pp].first == L[p].first)
                pp++;
            while (qq < RC && R[qq].first == R[q].first)
                qq++;
            for (int i = p; i < pp; i++)
                for (int j = q; j < qq; j++)
                    ans[L[i].second | (R[j].second << SLC)] = true;
            p = pp, q = qq;
        }
    }
    res = count(ans.begin() + 1, ans.end(), true);

    printf("%d\n", res);

    return 0;
}