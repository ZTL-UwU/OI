/**********************************************************
* @Author: 			   Kirito
* @Date:   			   2020-04-12 15:40:43
* @Last Modified by:   Kirito
* @Last Modified time: 2020-04-12 17:08:04
* @Remark: 
**********************************************************/
#include <bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define CSE(x,y) memset(x,y,sizeof(x))
#define INF 0x3f3f3f3f
#define Abs(x) (x>=0?x:(-x))
#define FAST ios::sync_with_stdio(false);cin.tie(0);
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll , ll> pll;

const int maxn=35;
int cnt[maxn][maxn], digit[maxn];
int x, y, b, k;

void ini()
{
	CSE(cnt, 0);
	cnt[0][0] = 1;
	for(int i = 1; i <= 32; i++)
	{
		cnt[i][0] = cnt[i - 1][0];
		for(int j = 1; j <= i; j++)
		{
			cnt[i][j] = cnt[i - 1][j] + cnt[i - 1][j - 1];
		}
	}
	return;
}

int get_ans(int x, int k)
{
	int pos = 1;
	while(x)
	{
		digit[pos++] = x % b;
		x /= b;
	}
	int ans = 0; pos -= 1;
	while(pos >= 1)//因为会用到pos - 1，所以这里用从1开始的下标
	{
		if(digit[pos] > 1){//如果该位大于1，则比此位数小的所有含有k个1的均成立，直接计算
			ans += cnt[pos - 1][k] + cnt[pos - 1][k -1];
			break;
		}
		else if(digit[pos] == 1)//此位为1，那么考虑下一位含有k - 1个1的情况
		{
			ans += cnt[pos - 1][k];
			k--;
		}
		if(k < 0)//已经找到k个1则直接退出
			break;
		pos--;
	}
	return ans;
}

int main()
{
	FAST;
	ini();
	while(cin >> x >> y >> k >> b)
	{
		cout << get_ans(y + 1, k) - get_ans(x, k) << endl;
	}
	return 0;
}
