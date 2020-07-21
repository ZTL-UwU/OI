#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
int dp[150][70][70];
int map[200];
vector<int> sta;
int n, m;
inline void get_sta()
{
    for (int i = 0; i < (1 << m); i++)
        if (!(i & (i << 1)) && !(i & (i << 2)))
            sta.push_back(i);
}
inline int count_one(int sta)
{
    int ans = 0;
    while (sta)
    {
        if (sta % 2)
            ans++;
        sta /= 2;
    }
    return ans;
}
inline void get_dp()
{
    for (int i = 0; i < sta.size(); i++)
        if (!(map[0] & sta[i]))
            dp[0][i][0] = count_one(sta[i]);
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < sta.size(); j++)
        {
            if (map[i] & sta[j])
                continue;
            for (int k = 0; k < sta.size(); k++)
            {
                if (sta[j] & sta[k])
                    continue;
                for (int l = 0; l < sta.size(); l++)
                {
                    if (sta[j] & sta[l])
                        continue;
                    if (sta[k] & sta[l])
                        continue;
                    dp[i][j][k] = max(dp[i - 1][k][l] + count_one(sta[j]), dp[i][j][k]);
                }
            }
        }
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < s.size(); j++)
            map[i] = (map[i] << 1) + (s[j] == 'P' ? 0 : 1);
    }
    get_sta();
    get_dp();
    int ans = -1;
    for (int i = 0; i < sta.size(); i++)
        for (int j = 0; j < sta.size(); j++)
            ans = max(ans, dp[n - 1][i][j]);
    cout << ans << "\n";
    return 0;
}