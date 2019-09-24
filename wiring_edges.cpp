/*
	author: aviral0807 and anay2102
	IIT (BHU) Varanasi
*/

#include<bits/stdc++.h>

#define int         long long
#define pb          push_back
#define	endl        '\n'
#define pi          pair<int, int>
#define pii         pair<int, pi>
#define vi          vector<int>
#define vpi         vector<pi>
#define all(a)      (a).begin(),(a).end()
#define F           first
#define S           second
#define sz(x)       (int)x.size()
#define hell        1000000007
#define rep(i,a,b)  for(int i=a;i<b;i++)
#define inv(i,a,b)  for(int i=a;i>=b;i--)
#define tr(it, a)   for(auto it=a.begin();it!=a.end();it++)
#define lbnd        lower_bound
#define ubnd        upper_bound

using namespace std;

#define N  1005

int p, n[N], q[N][N], v[N], no_nodes, adj[N][N];

vi generate_b(int m, int h)
{
	vi b(m, 1);
	int rest = h-m;
	rep(i,0,m-1)
	{
		int x = rand()%(rest+1);
		b[i]+=x;
		rest-=x;
	}
	b[m-1]+=rest;
	return b;
}

void input()
{
	cin >> p;
	rep(i,0,p) rep(j,0,p) cin >> q[i][j];
	rep(i,0,p) cin >> n[i];	
}

void pre_process()
{
	rep(i,1,p+1) v[i]=v[i-1]+n[i-1];
	no_nodes = v[p];
}

void intra_cluster_pair()
{
	rep(k,0,p) if(q[k][k]!=0)
	{
		rep(i,0,n[k]) rep(j,1,(q[k][k]/2)+1)
		{
			adj[v[k]+i][v[k]+((i+j)%n[k])] = 1;
			adj[v[k]+((i+j)%n[k])][v[k]+i] = 1;
		}
	
		if(q[k][k]&1)
		{
			rep(i,0,n[k])
			{
				adj[v[k]+i][v[k]+(i+(n[k]/2))%n[k]]=1;
			}
		}
	}
}

void inter_cluster_pair()
{
	rep(l,0,p) rep(k,0,l) if(q[l][k]!=0)
	{
		int h = __gcd(n[l],n[k]), c=h;
		int dl = n[l]/h, dk = n[k]/h;
		int m = (q[l][k]*h)/n[k];	

		vi b = generate_b(m,h), pre=b;

		rep(i,1,m) pre[i]+=pre[i-1];

		rep(i,0,n[k]) rep(r1,0,dl) rep(r2,1,m+1)
		{
			int f = (i + r1*c + pre[r2-1])%n[l];
			adj[v[k]+i][v[l]+f] = 1;
			adj[v[l]+f][v[k]+i] = 1;
		}
	}
}

void output()
{
	int ans=0;
	rep(i,0,no_nodes)
	{
		rep(j,0,no_nodes)
		{
			ans += adj[i][j];
			cout << adj[i][j] << " ";
		}
		cout << endl;
	}

	// cout << "No of edges: " << ans/2;
}
void solve()
{
	input();
	pre_process();
	intra_cluster_pair();
	inter_cluster_pair();
	output();
}

int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t=1;
	// cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}