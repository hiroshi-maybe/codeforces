#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
template<class T> using VV=vector<vector<T>>;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 10/10/2018
 
 21:42-22:12 pause
 
 10/12/2018
 
 15:35-16:05 analsysis
 17:00 1WA. Figured out that my condition is not sufficient...
 
 My conditions:
  - parity of ∑ B[l..r] is even
  - ∑ B[l..r] >= 2*B[l]
 
 18:20-19:18 read editorial and got AC
 
 The second one is wrong because XOR 0 cannot be made from [1,3].
 It should be modified as ∑ B[l..r] >= 2*max{ B[l..r] }
 
 Correct condition:
  - parity of ∑ B[l..r] is even
  - ∑ B[l..r] >= 2*B[l]

 I couldn't figure out how to query second condition for B[i] (i=0..N-1).
 I read editorial http://codeforces.com/blog/entry/62013
 
 => we use leverage the fact that maximum ON bit is 60.
 Since A[i]>0, upper-bound of falsy right border <=i+61
 
 l
 1,1,1,60,1,...,1,1
   ✓,✓ x,x,...,x,✓
 
 Principal part:
  - swap of bit
  - Number of ranges A[l..r]
  - XOR {A[i] } = 0 <=> even number of ON bit
 
 Key:
  - XOR A[i] = 0 <=> parity of ON bit is even
  - Condition of bit manipulation <=> Upper-bounded by lg max{A[i]}
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3e5+1;
LL A[MAX_N];
int N;
int cum[MAX_N];
int par[2][MAX_N];

int f(LL n) {
  int res=0;
  for(int i=62; i>=0; --i) res+=(n>>i)&1;
  return res;
}
LL solve_wrong() {
  ZERO(cum); ZERO(par);
  REP(i,N) {
    int a=f(A[i]);
    cum[i+1]=cum[i]+a;
    int p=cum[i+1]&1;
    par[0][i+1]=par[0][i]+(p==0);
    par[1][i+1]=par[1][i]+p;
  }
  LL res=0;
  REP(i,N) {
    int cur=cum[i+1],a=f(A[i]),t=cur+a;
    int j=lower_bound(cum+i+1,cum+N+1,t)-cum-1;
    dump4(i,cur,a,t);
    if(j>=N) {
      if(A[i]==0) ++res;
      continue;
    }
    assert(j>i);
    int p=cum[i]%2;
    LL cnt=par[p][N]-par[p][j];
    dump4(i,j,p,cnt);
    res+=cnt;
  }
  return res;
}

LL solve() {
  ZERO(cum); ZERO(par);
  REP(i,N) {
    int a=f(A[i]);
    cum[i+1]=cum[i]+a;
    int p=cum[i+1]&1;
    par[0][i+1]=par[0][i]+(p==0);
    par[1][i+1]=par[1][i]+p;
  }
  LL res=0;
  REP(i,N) {
//    int a=f(A[i]);
    int p=cum[i]%2;
    LL cnt=par[p][N]-par[p][i];
    LL ng=0;
    int cur=0,maxx=0;
//    dump4(i,p,par[p][i],par[p][N]);
    FOR(j,i,min(i+61,N)) {
      int b=f(A[j]);
      cur+=b;
      SMAX(maxx,b);
      int pp=(cum[j+1])&1;
      if(cur<2*maxx&&pp==p) ++ng;
    }
//    dump3(i,cnt,ng);
    res+=cnt-ng;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
