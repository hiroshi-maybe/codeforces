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
 
 11/19/2018
 
 14:45-15:43 WA, 15:50 RE, 15:54 AC
 
 https://codeforces.com/blog/entry/63324
 
 Weights are deterministic in the query(K,M) <=> One way to make M total mass with K weights
 
 If there are only two kinds of masses, all the weights can be figured out.
 
 @scott_wu's code is counting ways regardless of ordering by sort. Then combinatorics is not necessary.
 
 */

// 14:45-15:43 WA, 15:50 RE, 15:54 AC
// 1. missing analysis of complement, set 2. zero division.
// $ ../batch TheUnbearableLightnessOfWeights | diff TheUnbearableLightnessOfWeights.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheUnbearableLightnessOfWeights.cpp && ./a.out
const int MAX_N=1e2+1;
int A[MAX_N];
int N;

const LL MOD=1e9+7;
LL C[101][101];
LL dp[MAX_N*MAX_N][MAX_N];
void solve() {
  ZERO(dp); ZERO(C);
  REPE(i,100) {
    C[i][0]=1;
    FORE(j,1,i) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
  }
  int sum=accumulate(A,A+N,0);
  
  dp[0][0]=1;
  REP(i,N)for(int j=N; j>=1; --j) for(int w=1e4; w-A[i]>=0; --w) {
    dp[w][j]=(dp[w][j]+dp[w-A[i]][j-1])%MOD;
  }
  int res=0;
  map<int,int> M;
  REP(i,N)M[A[i]]++;
  FORR(kvp,M) {
    int cnt=kvp.second,w=kvp.first;
//    dump2(cnt,w);
    FORE(x,1,cnt) if(dp[x*w][x]==C[cnt][x]) {
      SMAX(res,x);
//      dump3(cnt,w,x);
      int remw=sum-x*w,remcnt=N-x;
//      dump4(cnt,w,remw,remcnt);
      if(remcnt>0&&remw%remcnt==0&&M[remw/remcnt]==remcnt) SMAX(res,N);
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  
  solve();
  
  return 0;
}
