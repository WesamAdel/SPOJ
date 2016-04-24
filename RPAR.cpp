#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define lop(i,N)		for(int i=0;i<N;++i)
#define Read            freopen("in.txt", "r", stdin)
#define Write           freopen("out.txt", "w", stdout)

#define clr(a)          memset(a,0,sizeof a)

#define sc	            scanf
#define pf				printf

/**********************************************************/

#define MAX 300005
#define MOD 10007
#define inv2 5004
#define inv6 1668

int N, M;
int st_a[MAX], st_b[MAX], st_c[MAX], lazy_a[MAX], lazy_b[MAX], lazy_c[MAX];

int sum_n(int n){
	return (((n % MOD) * ((n+1) % MOD))%MOD * inv2) % MOD;
}

int sum_n2(int n){
	return ( ( ((n % MOD) *((n+1) % MOD))%MOD * (((2*n+1) % MOD))) %MOD * inv6) % MOD;
}

void upd_a(int id,int l,int r,int v){
	v %= MOD;
	lazy_a[id] += v;
	lazy_a[id] %= MOD;
	st_a[id] += (v * ((sum_n2(r-1) % MOD - sum_n2(l-1) %MOD  + MOD) % MOD)) % MOD ;
	st_a[id] %= MOD;
}

void upd_b(int id, int l, int r, int v){
	v %= MOD;
	lazy_b[id] += v;
	lazy_b[id] %= MOD;
	st_b[id] += v * ((sum_n(r-1)% MOD  - sum_n(l-1) % MOD + MOD ) % MOD);
	st_b[id] %= MOD;
}

void upd_c(int id, int l, int r, int v){
	v %= MOD;
	lazy_c[id] += v;
	lazy_c[id] %= MOD;
	st_c[id] += (((r - l) % MOD) * v) % MOD;
	st_c[id] %= MOD;
}


void shift(int lazy [MAX], int id,int l,int r, char s){//pass update information to the children
	int mid = (l+r)/2;
	if(s == 'a'){
		upd_a(id * 2, l, mid, lazy[id]);
		upd_a(id * 2 + 1, mid, r, lazy[id]);
	}else
		if(s == 'b'){
			upd_b(id * 2, l, mid, lazy[id]);
			upd_b(id * 2 + 1, mid, r, lazy[id]);
		}else{
			upd_c(id * 2, l, mid, lazy[id]);
			upd_c(id * 2 + 1, mid, r, lazy[id]);
		}

	lazy[id] = 0;// passing is done
}


void increase( char s, int st[MAX], int lazy[MAX], int x,int y,int v,int id = 1,int l = 0,int r = N){

	if((x >= r or l >= y)) return;
	if(x <= l && r <= y){

		if(s == 'a')
			upd_a(id, l, r, v);
		else
			if(s == 'b')
				upd_b(id, l, r, v);
			else
				upd_c(id, l, r, v);
		return ;
	}
	shift(lazy, id, l, r, s);
	int mid = (l+r)/2;
	increase(s, st, lazy, x, y, v, id * 2, l, mid);
	increase(s, st, lazy, x, y, v, id*2+1, mid, r);
	st[id] = ((st[id * 2] % MOD) + (st[id * 2 + 1] % MOD)) % MOD;
}


int sum(char s, int st[MAX], int lazy[MAX], int x,int y,int id = 1,int l = 0,int r = N){
	if((x >= r or l >= y)) return 0;
	if(x <= l && r <= y)	return st[id];

	shift(lazy, id, l, r, s);
	int mid = (l+r)/2;
	return ( ( sum(s, st, lazy, x, y, id * 2, l, mid) % MOD +
	       sum(s, st, lazy, x, y, id * 2 + 1, mid, r) % MOD ) % MOD);
}


int main(){
#ifndef ONLINE_JUDGE
	Read;
#endif

	int a,b,c, x0, x1, t;

	while(sc("%d %d",&N,&M) == 2){
		clr(st_a);
		clr(st_b);
		clr(st_c);
		clr(lazy_a);
		clr(lazy_b);
		clr(lazy_c);

		while(M--){
			sc("%d",&t);
			if(t == 0){
				sc("%d %d %d %d %d",&x0, &x1, &a, &b, &c);
				increase('a', st_a, lazy_a, x0, x1+1, a);
				increase('b', st_b, lazy_b, x0, x1+1, b);
				increase('c', st_c, lazy_c, x0, x1+1, c);
			}else{
				sc("%d %d", &x0, &x1);
				int ans = ( sum('a', st_a, lazy_a, x0, x1+1) % MOD + sum('b', st_b, lazy_b, x0,x1+1) % MOD
				+ sum('c', st_c, lazy_c, x0, x1+1) % MOD ) % MOD;
				pf("%d\n", ans);
			}
		}
	}

	return 0;
}

















