#include<bits/stdc++.h>
using namespace std;

vector<int> g[51000];
int siz[51000],fa[51000],son[51000],dep[51000];
int top[51000],dfn[51000],pdfn[51000],dck;
int n;
int firstcol[51000],firstval[51000];
void dfs1(int u,int f)
{
	fa[u]=f;
	dep[u]=dep[f]+1;
	siz[u]=1;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==f)
		{
			continue;
		}
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
		{
			son[u]=v;
		}
	}
}
void dfs2(int u)
{
	dfn[u]=++dck;
	pdfn[dfn[u]]=u;
	if(son[fa[u]]==u)
	{
		top[u]=top[fa[u]];
	}
	else
	{
		top[u]=u;
	}
	if(son[u])
	{
		dfs2(son[u]);
	}
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==son[u]||v==fa[u])
		{
			continue;
		}
		dfs2(v);
	}
}

struct treenode
{
	int val;
	int lson;
	int rson;
};
treenode t[2100000];
int rt[20];
int ncnt;
void pushup(int u)
{
	t[u].val=t[t[u].lson].val+t[t[u].rson].val;
}
void update(int &u,int l,int r,int p,int v)
{
	if(!u)
	{
		u=++ncnt;
		t[u].val=t[u].lson=t[u].rson=0;
	}
	if(l==r&&l==p)
	{
		t[u].val=v;
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid)
	{
		update(t[u].lson,l,mid,p,v);
	}
	if(p>mid)
	{
		update(t[u].rson,mid+1,r,p,v);
	}
	pushup(u);
}
void exchange(int &u,int &v,int l,int r,int a,int b)
{
	// cout<<"Exchange "<<u<<" "<<v<<" "<<l<<" "<<r<<" "<<a<<" "<<b<<endl;
	if(!u)
	{
		u=++ncnt;
		t[u].lson=t[u].rson=t[u].val=0;
	}
	if(!v)
	{
		v=++ncnt;
		t[v].lson=t[v].rson=t[v].val=0;
	}
	if(a<=l&&r<=b)
	{
		int tmp;
		tmp=u;
		u=v;
		v=tmp;
		return;
	}
	int mid=(l+r)>>1;
	if(a<=mid)
	{
		exchange(t[u].lson,t[v].lson,l,mid,a,b);
	}
	if(b>mid)
	{
		exchange(t[u].rson,t[v].rson,mid+1,r,a,b);
	}
	pushup(u);
	pushup(v);
}
int query(int u,int l,int r,int a,int b)
{
	if(!u)
	{
		return 0;
	}
	if(a<=l&&r<=b)
	{
		return t[u].val;
	}
	int mid=(l+r)>>1;
	int ans=0;
	if(a<=mid)
	{
		ans+=query(t[u].lson,l,mid,a,b);
	}
	if(b>mid)
	{
		ans+=query(t[u].rson,mid+1,r,a,b);
	}
	return ans;
}

void qchange(int u,int x,int y)
{
	// cout<<"Change"<<endl;
	exchange(rt[x],rt[y],1,n,dfn[u],dfn[u]+siz[u]-1);
}
int qpathsum(int u,int v,int c)
{
	int ans=0;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])
		{
			swap(u,v);
		}
		ans+=query(rt[c],1,n,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v])
	{
		swap(u,v);
	}
	ans+=query(rt[c],1,n,dfn[v],dfn[u]);
	return ans;
}
void qsetnode(int u,int c,int v)
{
	// cout<<"Set"<<endl;
	int nowcol=0,nowval=0;
	for(int i=0;i<=10;i++)
	{
		nowval=query(rt[i],1,n,dfn[u],dfn[u]);
		if(nowval!=0)
		{
			nowcol=i;
			break;
		}
	}
	// cout<<"Point "<<u<<" : "<<"color="<<nowcol<<" ,value="<<nowval<<endl;
	update(rt[nowcol],1,n,dfn[u],0);
	update(rt[c],1,n,dfn[u],v);
}

void init()
{
	dck=ncnt=0;
	memset(g,0,sizeof(g));
	memset(fa,0,sizeof(fa));
	memset(rt,0,sizeof(rt));
	memset(dep,0,sizeof(dep));
	memset(dfn,0,sizeof(dfn));
	memset(siz,0,sizeof(siz));
	memset(son,0,sizeof(son));
	memset(top,0,sizeof(top));
	memset(pdfn,0,sizeof(pdfn));
	memset(firstcol,0,sizeof(firstcol));
	memset(firstval,0,sizeof(firstval));
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	init();
	int q;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>firstcol[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>firstval[i];
	}
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		cin>>u>>v;
		u++;
		v++;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1);
	// cout<<"DFN:"<<endl;
	// for(int i=1;i<=n;i++)
	// {
	// 	cout<<dfn[i]<<" ";
	// }
	// cout<<endl;
	for(int i=1;i<=n;i++)
	{
		update(rt[firstcol[i]],1,n,dfn[i],firstval[i]);
	}
	// for(int i=0;i<=2;i++)
	// {
	// 	cout<<"RT["<<i<<"]="<<rt[i]<<endl;
	// }
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		string ty;
		int a,b,c;
		cin>>ty>>a>>b>>c;
		if(ty=="Change")
		{
			a++;
			qchange(a,b,c);
		}
		if(ty=="Ask")
		{
			a++;
			b++;
			cout<<qpathsum(a,b,c)<<endl;
		}
		if(ty=="Set")
		{
			a++;
			qsetnode(a,b,c);
		}
	}
}
/*
5
0 1 0 2 2
1 2 4 8 16
0 1
0 3
1 2
1 4
100
Change 1 0 2
Set 0 2 32
Ask 2 3 2
*/