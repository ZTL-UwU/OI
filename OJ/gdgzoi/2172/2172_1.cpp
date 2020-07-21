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
int fa[50000];
int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	fa[fx] = fy;
}
int main()
{
	for (int i = 0; i < 50000; i ++) fa[i] = i;
	int n, m;
	cin >> n >> m;
	int u, v, w;
	for (int i = 0; i < m; i ++)
	{
		cin >> u >> v >> w;
		e.push_back((edge){u, v, w});
	}
	int num, maxn;
	sort(e.begin(), e.end(), cmp);
	for (int i = 0; i < e.size(); i ++)
	{
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (find(u) != find(v))
		{
			maxn = w;
			num ++;
			merge(u, v);
		}
	}
	cout << num << " " << maxn;
	return 0;
}
