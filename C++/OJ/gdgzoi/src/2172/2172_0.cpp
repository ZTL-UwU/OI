#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
struct edge
{
	int u, v, w;
};
vector<edge> e;
bool cmp(edge x, edge y)
{
	return x.w < y.w;
}
int fa[10000];
int find(int x)
{
	if (fa[x] == x) return x;
	return f[x] = find(f[x]);
}
void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	fa[fx] = fy;
}
int main()
{
	for (int i = 0; i < 10000; i ++) fa[i] = i;
	int n;
	cin >> n;
	for (int i = 0; i < n; i ++)
	{
		for (int j = 0; j < n; j ++)
		{
			int w;
			cin >> w;
			e.push_back((edge){u, v, w});
		}
	}
	int ans = 0;
	sort(e.begin(), e.end(), cmp);
	for (int i = 0; i < e.size(); i ++)
	{
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (find(u) != find(v))
		{
			ans += w;
			merge(u, v);
		}
	}
	cout << ans;
	return 0;
}