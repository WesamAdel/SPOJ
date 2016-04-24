#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

typedef long long       ll;

#define Read            freopen("in.txt", "r", stdin)
#define Write           freopen("out.txt", "w", stdout)

#define clr(a)          memset(a,0,sizeof a)
#define all(v)          v.begin(),v.end()
#define sz(v)           (int) v.size()
#define rev(v)			reverse(all(v))

#define pb              push_back
#define fi              first
#define se              second
#define mp              make_pair
#define mt				make_tuple
#define elm(t,indx)		get<indx>(t)

#define lop(i,n)        for(int i=0;i<n;++i)

#define sc	            scanf
#define pf				printf
#define pfn				printf("\n")

#define debug(args...)  {dbg,args; cerr << endl;}
struct debugger{
    template<typename T> debugger& operator , (const T& v){
        cerr<<v<<" ";
        return *this;
    }
} dbg;

ll gcd(ll a, ll b){ return((b == 0)?a:gcd(b,a%b));  }
ll lcm(ll a, ll b){ return (a*b)/gcd(a,b); }

/*
    -sqrt decomposition
    -build sqrt(n)*n table, table[i][j] is the sumamtion of elements in segment i whose last occurance is before index j.
*/

int n, a[30006], q, l, r, len, table[175][30006], last[30005], cur[1000005];

int main(){
#ifndef ONLINE_JUDGE
	Read;
#endif

    while(sc("%d", &n) == 1){
        clr(table);
        clr(last);
        clr(cur);
        len = (int) sqrt(n) +1;

        for(int i=1; i<=n; ++i){
            sc("%d", &a[i]);
            last[i] = cur[a[i]];
            cur[a[i]] = i;
        }

        for(int i= 1; i<=n; ++i)
            ++ table[i/len][last[i]];

        lop(i,len)
            for(int j=1;j<=n;++j)
                table[i][j] += table[i][j-1];

        sc("%d", &q);

        while(q--){
            sc("%d %d",&l, &r);
            int ans = 0;

            int c_l = l / len,   c_r = r / len;
            if (c_l == c_r)
	           for (int i=l; i<=r; ++i)
                   ans += (last[i] < l)?1:0;
            else{
                for (int i=l, end=(c_l+1)*len-1; i<=end; ++i)
                    ans += (last[i] < l)?1:0;
            	for (int i=c_l+1; i<=c_r-1; ++i)
                    ans += table[i][l-1];
            	for (int i=c_r*len; i<=r; ++i)
                    ans += (last[i] < l)?1:0;
            }

            pf("%d\n", ans);
        }
    }

	return 0;
}






















