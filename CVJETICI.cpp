#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

#define Read            freopen("in.txt", "r", stdin)
#define Write           freopen("out.txt", "w", stdout)

#define clr(a)          memset(a,0,sizeof a)

#define sc	            scanf
#define pf				printf


#define MAX 100005
int tree[MAX], N;

void update(int p, int v){
	while(p <= MAX){
		tree[p] += v;
		p += (p & -p);
	}
}

void update_range(int a, int b, int v){
	update(a,v);
	update(b+1,-v);
}

int read(int p){
	int sum = 0;
	while(p){
		sum += tree[p];
		p -= (p & -p);
	}
	return sum;
}


int main(){
#ifndef ONLINE_JUDGE
	Read;
#endif
	int l, r;
	while(sc("%d", &N) == 1){
		clr(tree);
		while(N--){
			sc("%d %d",&l,&r);
			// check if l, r intersects, update [(l+1), (r-1)]
			pf("%d\n",read(l) + read(r));
			update_range(l+1, r-1, 1);
			update_range(l, l, -read(l));
			update_range(r, r, -read(r));
		}
	}
	return 0;
}
