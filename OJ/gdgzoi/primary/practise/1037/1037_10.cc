#include<iostream>
#include<stdio.h>
using namespace std;
long long Tree[2400100];
long long add[2400100];
void update(long long l, long long r, long long k, long long a, long long b, long long val)
{
	if (l >= a && r <= b)
	{
		Tree[k] += val;
		add[k] += val;
		return;
	}
	long long mid = (l + r) >> 1;
	long long ls = k << 1, rs = k << 1|1;
	if (a <= mid) update(l, mid, ls, a, b, val);
	if (b > mid) update(mid + 1, r, rs, a, b, val);
	Tree[k] = max(Tree[ls], Tree[rs]) + add[k];
}
inline long long query(long long l, long long r, long long k, long long a, long long b, long long addon)
{
	if (l >= a && r <= b) return Tree[k] + addon;
	long long mid = (l + r) >> 1;
	long long ls = k << 1, rs = k << 1|1;
	long long tmp = -0x7fffffff;
	if (a <= mid) tmp = max(tmp, query(l, mid, ls, a, b, addon + add[k]));
	if (b > mid) tmp = max(tmp, query(mid + 1, r, rs, a, b, addon + add[k]));
	return tmp;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long c, s, r;
	cin >> c >> s >> r;
	while (r --)
	{
		long long o, d, n;
		cin >> o >> d >> n;
		d --;
		if (query(1, c, 1, o, d, 0) + n <= s)
		{
			update(1, c, 1, o, d, n);
			cout << "YES\n";
		}
		else cout << "NO\n";
	}
	return 0;
}