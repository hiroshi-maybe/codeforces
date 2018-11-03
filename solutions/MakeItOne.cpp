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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');

// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

/*
 
 11/2/2018
 
 15:56-16:34 analysis
 17:04 give up
 
 18:30-19:15, 20:50-22:20 read editorials and got AC
 
 http://codeforces.com/blog/entry/62797
 http://kmjp.hatenablog.jp/entry/2018/10/30/0930
 https://twitter.com/HIR180/status/1056601315139235840
 https://twitter.com/natsugir/status/1056628855220273152
 
 Size of subset is reduced to counting problem. Interesting...
 
 unknown: minimum size of subset
      <=> check if size `x` is possible where x=1..7 (`x` is small. it's possible to brute-force)
      <=> check if size `x` for gcd `g` is possible (`g` = 1..3e5)
 
 The most important observation is that range of possible result is very small [1,7].
 Then approach to solve decision problem enumerating [1..7] shows up.
 
 Key:
  - possible result is in small range. Reduction to decision problem is feasible
  - If state (size of subset, gcd) is defined, recurrence relation is found by inclusion-exclusion principle
  - Enumerating all the multiples is possible in O(N*ln N) time
 
 Summary:
  - My observation of unique prime factor was good 👍
  - Complexity of my algorithm was O(N^2*2^7) time 👎
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3e5+1;
int A[MAX_N];
int N;

const LL MOD=1e9+7;
LL C[MAX_N][11];
LL dp[MAX_N];
int cnt[MAX_N];
void solve() {
  REP(i,MAX_N) {
    C[i][0]=1;
    FORE(j,1,min(10,i)) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
  }
  REP(i,N) cnt[A[i]]++;
  FOR(n,1,MAX_N) for(int kn=2*n; kn<MAX_N; kn+=n) cnt[n]+=cnt[kn];
  
//  FOR(n,1,MAX_N) if(cnt[n]) dump2(n,cnt[n]);
//  dump3(cnt[10],C[cnt[10]][1],C[1][1]);
  FORE(x,1,8) {
    ZERO(dp);
    for(int g=MAX_N-1; g>=1; --g) {
      dp[g]=C[cnt[g]][x];
      for(int kg=2*g; kg<MAX_N; kg+=g) (dp[g]+=MOD-dp[kg])%=MOD;
//      if(dp[g]>0) dump3(x,g,dp[g]);
    }
    if(dp[1]>0) {
      cout<<x<<endl;
      exit(0);
    }
  }
  cout<<-1<<endl;
}

vector<LL> distinctPrimeFactors(LL n) {
  assert(n>=1);
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) if(n%p==0) {
    res.push_back(p);
    while(n%p==0) n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}
LL f[1<<10];
void ztransform_subset(int N) {
  for(int i=0; i<N; ++i) {
    for(int T=0; T<(1<<N); ++T) {
      if ((T>>i)&1) f[T]=min(f[T^(1<<i)]+f[1<<i],f[T]);
    }
  }
}
void solve_TLE() {
  const LL Inf=1e7;
  LL res=Inf;
  REP(i,N) {
    vector<LL> P=distinctPrimeFactors(A[i]);
//    dumpAR(P);
    int M=SZ(P);
    REP(mask,1<<M) f[mask]=Inf;
    REP(j,N) if(i!=j) {
      int mask=0;
      REP(k,M) {
        int p=(int)P[k];
        if(A[j]%p!=0) {
          mask|=1<<k;
          f[1<<k]=1;
        }
      }
      SMIN(f[mask],1LL);
    }
    ztransform_subset(M);
    int full=(1<<M)-1;
//    dump2(i,f[full]);
    SMIN(res,f[full]+1);
  }
  if(res>=Inf) res=-1;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  scanf("%d",&N);
  REP(i,N) {
    scanf("%d",&A[i]);
    if(A[i]==1) {
      cout<<1<<endl;
      exit(0);
    }
  }
  solve();
  
  return 0;
}
