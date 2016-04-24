#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

typedef long long       ll;

#define Read            freopen("in.txt", "r", stdin)
#define Write           freopen("out.txt", "w", stdout)

#define oo 							1e9
#define OO							1e18
#define clr(a)          memset(a,0,sizeof a)
#define all(v)          v.begin(),v.end()
#define sz(v)           (int) v.size()
#define rev(v)					reverse(all(v))

#define pb              push_back
#define fi              first
#define se              second
#define mp              make_pair
#define mt							make_tuple
#define elm(t,indx)			get<indx>(t)

#define lop(i,n)        for(int i=0;i<n;++i)

#define sc	           	scanf
#define pf							printf
#define pfn							printf("\n")

ll gcd(ll a, ll b){ return((b == 0)?a:gcd(b,a%b));  }
ll lcm(ll a, ll b){ return (a*b)/gcd(a,b); }


struct node{
	ll best, pre, suf, total;
	node(){};
	node(ll _best, ll _pre, ll _suf, ll _total){
		best = _best;
		pre = _pre;
		suf = _suf;
		total = _total;
	}
};

ll N, M,  A[10305], dp[10305], x1, x2;
ll y_1, y_2, t, max_st[40305], min_st[40305];

node max_sum[40305];

node merge(node lnode, node rnode){
	return node(max(lnode.suf + rnode.pre, max(lnode.best, rnode.best))
				 ,max(lnode.pre, lnode.total + rnode.pre)
				 ,max(rnode.suf, rnode.total + lnode.suf)
				 ,lnode.total +rnode.total);
}

void build(int id = 1, int l = 0, int r = N){
	if(r - l < 2){
		max_st[id] = dp[l];
		min_st[id] = dp[l];
		max_sum[id].pre = max_sum[id].suf = max_sum[id].best = max_sum[id].total = A[l];
		return ;
	}

	int mid = (l+r)/2;
	build(2*id, l, mid);
	build(2*id+1, mid, r);
	max_st[id] = max(max_st[2*id], max_st[2*id+1]);
	min_st[id] = min(min_st[2*id], min_st[2*id+1]);

	max_sum[id] = merge(max_sum[2*id], max_sum[2*id+1]);
}

node query_max_sum(int x, int y, int id =1, int l = 0, int r = N){
	if(x>=r||y<=l)
		return node(-oo, -oo, -oo, -oo);

	if(x<=l && y>= r)
		return max_sum[id];

	int mid = (l+r)/2;
	node lnode, rnode;

	lnode = query_max_sum(x, y, 2*id, l, mid);
	rnode = query_max_sum(x, y, 2*id+1, mid, r);
	return merge(lnode, rnode);
}

int query(bool q, int x, int y, int id =1, int l = 0, int r = N){// q = 1 max, q = 0 min
	if(x >= r || y <= l)
		return (q?-oo:oo);
	if( x <= l && y >= r)
		return (q?max_st[id]:min_st[id]);

	int mid = (l+r)/2;
	return (q?max ( query(1, x, y, 2*id, l, mid), query(1, x, y, 2*id +1, mid, r)) :
			  min ( query(0, x, y, 2*id, l, mid), query(0, x, y, 2*id +1, mid, r)));
}


int main(){
#ifndef ONLINE_JUDGE
	Read;
#endif
	cin >> t;

	while(t--){
		cin >> N;
		++N;
		A[0] = -oo;

		for(int i=1;i<N;++i)
			cin >> A[i];

		dp[0] = 0;
		dp[1]= A[1];

		for(int i=2;i<N;++i)
			dp[i] = A[i]+ dp[i-1];

		build();

		cin >> M;

		while(M--){
			cin >> x1 >> y_1 >> x2 >> y_2;
			ll ans, mid;

			if(y_1 >= x2){
				mid = max(x2,y_1);
				ll a = query(1, mid, y_2 + 1) - query(0, x1-1, mid);
				mid = min(x2,y_1);
				ll b = query(1, mid, y_2 + 1) - query(0, x1-1, mid);
				ll c = query_max_sum(x2,y_1+1).best;
				ans = max(max(a,b), c);
			}else
				ans = query(1, x2, y_2+1) - query(0, x1-1, y_1);

			cout << ans <<  endl;
		}
	}


	return 0;
}
