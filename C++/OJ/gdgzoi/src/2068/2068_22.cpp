#include<iostream>
#include<vector>
using namespace std;
int n;
int cut;
vector<int> g[10000];
int get_sub_tree(int k, int last)
{
	int sum = 1;
	for (int i = 0; i < g[k].size(); i ++)
	{
		if (g[k][i] != last)
			sum += get_sub_tree(g[k][i], k);
	}
	return sum;
}
int get_minn()
{
	int maxn = -0x7fffffff;
	for (int i = 0; i < g[cut].size(); i ++)
		maxn = max(maxn, get_sub_tree(g[cut][i], cut));
	return maxn;
}
int main()
{
	cin >> n;
	for (int i = 0; i < n - 1; i ++)
	{
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int minn = 0x7fffffff;
	int minn_cut;
	for (int i = 1; i <= n; i ++)
	{
		cut = i;
		if (minn > get_minn())
		{
			minn = get_minn();
			minn_cut = cut;
		}
	}
	cout << minn_cut;
	return 0;
}
