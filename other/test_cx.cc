#include <bits/stdc++.h>
using namespace std;

const int inf = 2139062143;
int p;

int ufs[210000], siz[210000];
void initufs(int n)
{
	for (int i = 1; i <= n; i++)
	{
		ufs[i] = i;
		siz[i] = 1;
	}
}
int findf(int u)
{
	return ufs[u] == u ? u : (ufs[u] = findf(ufs[u]));
}
void merge(int u, int v)
{
	u = findf(u);
	v = findf(v);
	if (v > u)
	{
		swap(u, v);
	}
	ufs[u] = v;
	siz[v] += siz[u];
	siz[u] = 0;
}
// void printufs(int n)
// {
// 	cout<<"UFS-----------------------------------"<<endl;
// 	for(int i=1;i<=n;i++)
// 	{
// 		cout<<findf(i)<<" ";
// 	}
// 	cout<<endl;
// 	cout<<"UFS END-------------------------------"<<endl;
// }

struct node
{
	int val;
	int cnt;
	int siz;
	int lson;
	int rson;
	int rnd;
};
vector<node> t;
int rt;
void printtree()
{
	// cout << "TREE----------------------------------" << endl;
	// cout << "rt=" << rt << endl;
	// for (int i = 0; i < t.size(); i++)
	// {
	// 	printf("%d: v=%d c=%d s=%d l=%d r=%d d=%d\n", i, t[i].val, t[i].cnt, t[i].siz, t[i].lson, t[i].rson, t[i].rnd);
	// }
	// cout << "END TREE------------------------------" << endl;
}
int randx()
{
	// return (rand() * RAND_MAX + rand()) * (rand() % 2 == (0 ? -1 : 1));
	return rand();
}
void inittree()
{
	t.clear();
	rt = 0;
	t.push_back((node){0, 0, 0, 0, 0, -2147483646});
}
int create(int val, int cnt)
{
	t.push_back((node){val, cnt, cnt, 0, 0, randx()});
	return t.size() - 1;
}
void pushup(int u)
{
	t[u].siz = t[t[u].lson].siz + t[t[u].rson].siz + t[u].cnt;
}
void lrotate(int &u)
{
	int v = t[u].rson;
	t[u].rson = t[v].lson;
	t[v].lson = u;
	u = v;
	pushup(t[u].lson);
	pushup(u);
}
void rrotate(int &u)
{
	int v = t[u].lson;
	t[u].lson = t[v].rson;
	t[v].rson = u;
	u = v;
	pushup(t[u].rson);
	pushup(u);
}
void build()
{
	rt = create(-inf, 0);
	p = create(inf, 0);
	t[rt].rson = p;
	if (t[t[rt].rson].rnd > t[rt].rnd)
	{
		lrotate(rt);
	}
	pushup(rt);
}
int insert(int u, int val, int cnt)
{
	if (!u)
	{
		u = create(val, cnt);
		return u;
	}
	if (t[u].val == val)
	{
		t[u].cnt += cnt;
	}
	else if (t[u].val < val)
	{
		p = insert(t[u].lson, val, cnt);
		t[u].lson = p;
		if (t[t[u].lson].rnd < t[u].rnd)
		{
			rrotate(u);
		}
	}
	else if (t[u].val > val)
	{
		p = insert(t[u].rson, val, cnt);
		t[u].rson = p;
		if (t[t[u].rson].rnd < t[u].rnd)
		{
			lrotate(u);
		}
	}
	pushup(u);
	return u;
}
int erase(int u, int val)
{
	if (!u)
	{
		return 0;
	}
	if (t[u].val == val)
	{
		if (t[u].cnt > 1)
		{
			t[u].cnt--;
			pushup(u);
			return u;
		}
		else
		{
			if (t[u].lson || t[u].rson)
			{
				if (!t[u].lson || t[t[u].lson].rnd > t[t[u].rson].rnd)
				{
					lrotate(u);
					p = erase(t[u].lson, val);
					t[u].lson = p;
				}
				else
				{
					rrotate(u);
					p = erase(t[u].rson, val);
					t[u].rson = p;
				}
				pushup(u);
			}
			else
			{
				return 0;
			}
		}
		return u;
	}
	if (t[u].val < val)
	{
		p = erase(t[u].lson, val);
		t[u].lson = p;
		pushup(u);
		return u;
	}
	if (t[u].val > val)
	{
		p = erase(t[u].rson, val);
		t[u].rson = p;
		pushup(u);
		return u;
	}
}
int getval(int u, int rk)
{
	if (!u)
	{
		return inf;
	}
	if (t[t[u].lson].siz + 1 <= rk && rk <= t[t[u].lson].siz + t[u].cnt)
	{
		return t[u].val;
	}
	if (rk <= t[t[u].lson].siz)
	{
		return getval(t[u].lson, rk);
	}
	if (rk > t[t[u].lson].siz + t[u].cnt)
	{
		return getval(t[u].rson, rk - t[t[u].lson].siz - t[u].cnt);
	}
}

int main()
{
	inittree();
	build();
	// printtree();
	int n, q;
	cin >> n >> q;
	initufs(n);
	// cout<<"INSERT "<<n<<" "<<1<<endl;
	p = insert(rt, 1, n);
	rt = p;
	for (int i = 1; i <= n; i++)
	{
		int ty;
		cin >> ty;
		if (ty == 0)
		{
			int a, b;
			cin >> a >> b;
			// cout<<"ERASE "<<siz[findf(a)]<<endl;
			p = erase(rt, siz[findf(a)]);
			rt = p;
			// printtree();
			// cout<<"ERASE "<<siz[findf(b)]<<endl;
			p = erase(rt, siz[findf(b)]);
			rt = p;
			// printtree();
			merge(a, b);
			// cout<<"INSERT "<<1<<" "<<siz[findf(a)]<<endl;
			p = insert(rt, siz[findf(a)], 1);
			rt = p;
			printtree();
			// printufs(n);
		}
		if (ty == 1)
		{
			int rk;
			cin >> rk;
			cout << getval(rt, rk) << endl;
		}
	}
}
/*
10 10
0 1 2
1 4
0 3 4
1 2
0 5 6
1 1
0 7 8
1 1
0 9 10
1 1
*/
