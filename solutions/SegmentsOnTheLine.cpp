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
 
 11/12/2018
 
 20:20-21:20 give up
 
 possible approaches
  - dp
  - sort and greedy <= interval
  - res >= K-th in A. keep removing S[i]?. range query? how to check each segment?
 
 11/14/2018
 
 15:00-18:20 read editorial and submit code by @kmjp and @LHiC
 
 https://codeforces.com/blog/entry/63099
 
 I completely missed binary search approach, which is typical to find k-th.
 It's pretty hard to understand optimality of dp part. I spent 2 hours. However I couldn't.
 
       i  i'
 <--a-->
   <--b-->
   i''
 
 dp transition happens from i to i' regardless of interval `a` was taken or not.
 
 1) both a and b are taken => dp[i'][j+2]=max(_,dp[i][j+1]+cum[i,i'])
 2) neither a nor b was taken but cum[i,i'] is added => dp[i'][j+1]=max(_,dp[i][j]+cum[i,i'])
 3) only b was taken => dp[i'][j+1]=max(_,dp[i''][j]+cum[i'',i'])
 
 It would be possible to prove that case #3 always beats case #2 even if dp[i]+cum[i,i'] transition happens.
 
 cum[i'',i']>=cum[i,i']
 
 However I'm still not sure if the proof is really sufficient.
 
 Key:
  - find K-th <=> binary search
  - segment choice <=> greedy
 
 Summary:
  - if redundant transition always loses, we can do it. However proof is necessary.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e3+1;
LL A[MAX_N];
int L[MAX_N],R[MAX_N];
int J[MAX_N];
int N,M,S,K;
int dp[MAX_N][MAX_N];
bool ok(int x) {
  VI cum(N+1,0);
  REP(i,N) cum[i+1]=cum[i]+(A[i]<=x);
  ZERO(dp);
  REP(i,N)REPE(j,S) {
    SMAX(dp[i+1][j],dp[i][j]);
    if(j<S&&J[i]>i) SMAX(dp[J[i]][j+1],dp[i][j]+cum[J[i]]-cum[i]);
  }
  return dp[N][M]>=K;
}

void solve() {
  MINUS(J);
  REP(i,S) {
    FOR(j,L[i],R[i]) SMAX(J[j],R[i]);
  }
  
  const int Inf=1e9+1;
  int bad=0,good=Inf;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    (ok(m)?good:bad)=m;
  }
  if(good>=Inf) cout<<-1<<endl;
  else cout<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>S>>M>>K;
  REP(i,N) cin>>A[i];
  REP(i,S) {
    cin>>L[i]>>R[i];
    L[i]--;
  }
  
  solve();
  
  return 0;
}
