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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

/*
 
 11/14/2018
 
 11:20-11:50, 16:55-18:30 give up.
 20:10-22:00 gave up AC without reading editorial. My analysis is not sufficient (4WA)
 
 My analysis toward dp[N][2] with minimal rightmost segment was correct.
 However optimality analysis was completely wrong. K,1,K,1 is one of optimal cases.
 
 22:00-24:00 read editorial and got AC
 
 https://codeforces.com/blog/entry/63151
 
 My analysis was missing a deep analysis when separator's length is too much.
 Possible # of separators is in some rage. I should have analyzed maximal case too.
 
 ceil(tot/K)-1 <= # of separator <= X[c]
 
 Possible number of opposite color can be computed from # of separators.
 
 ceil(tot/K)-1 * 1 <= X[1-c] <= K*X[c]
 
 This is applied to the case where the color of the last segment is the same.
 
 Also another confusion was updating state of opposite color.
 This is totally wrong because condition of opposite color is not fully satisfied.
 
 Summary:
  - My analysis is not still sufficient at all!!!!
   - keep in mind sufficiency
   - keep in mind exhaustivity
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3e5+1;
LL X[MAX_N][2];
int N;
LL K;

const LL Inf=1e7;
LL dp[MAX_N][2];
void solve() {
  REPE(i,N)REP(c,2)dp[i][c]=Inf;
  dp[0][0]=dp[0][1]=0;
  
  REP(i,N)REP(c,2) {
    if(dp[i][c]<=K) {
      LL tot=dp[i][c]+X[i][c];
      LL minsep=(tot+K-1)/K-1;
      if(X[i][1-c]==minsep) {
        SMIN(dp[i+1][c],tot-K*X[i][1-c]);
      } else if(X[i][1-c]>minsep&&X[i][1-c]<=K*X[i][c]) {
        SMIN(dp[i+1][c],1LL);
      }
    }
    if(dp[i][1-c]<=K) {
      LL minsep=(X[i][c]+K-1)/K-1;
      if(X[i][1-c]==minsep) {
        SMIN(dp[i+1][c],X[i][c]-K*X[i][1-c]);
      } else if(X[i][1-c]>minsep&&X[i][1-c]<=K-dp[i][1-c]+(X[i][c]-1)*K) {
        SMIN(dp[i+1][c],1LL);
      }
    }
  }
  
  if(dp[N][0]<=K||dp[N][1]<=K) cout<<"YES"<<endl;
  else cout<<"NO"<<endl;
}

void solve_wrong2() {
  REPE(i,N)REP(c,2)dp[i][c]=Inf;
  dp[0][0]=dp[0][1]=0;
  REP(i,N)REP(c,2) if(X[i][c]>=X[i][1-c] /* Completely wrong condition. This is not exhausitive AT ALL 👎 */ ) {
    if(dp[i][c]<=K) {
      LL rem=max(X[i][c]-(K-dp[i][c])-K*(X[i][1-c]-1),0LL);
      dump4(i,c,dp[i][c],rem);
      if(rem==1) {
        SMIN(dp[i+1][c],1LL);
        // This zero case for opposite color is unnecessary
        // Each color should focus on the length of the last segment of its own color
        // Otherwise condition of opposite color is not fully verified.
        dp[i+1][1-c]=0;
      } else if(rem==0) {
        dp[i+1][c]=0;
        dp[i+1][1-c]=X[i][1-c]==X[i][c]&&(K==1||X[i][1-c]==1)?1:0;
      } else {
        SMIN(dp[i+1][c],rem);
        if(rem<=K) dp[i+1][1-c]=0;
      }
    }
  }
  dump2(dp[N][0],dp[N][1]);
  if(dp[N][0]<=K||dp[N][1]<=K) cout<<"YES"<<endl;
  else cout<<"NO"<<endl;
}

void solve_wrong() {
  REPE(i,N)REP(c,2)dp[i][c]=Inf;
  dp[0][0]=dp[0][1]=0;
  REP(i,N)REP(c,2) {
    LL cycle=min(X[i][c]/K,X[i][1-c]/K);
    LL rem[2]={};
    rem[c]=X[i][c]-K*cycle,rem[1-c]=X[i][1-c]-K*cycle;
    if(dp[i][c]<=K) {
      dump4(i,c,cycle,dp[i][c]);
      LL a=rem[c]-(K-dp[i][c]);
      if(a<=0) SMIN(dp[i+1][1-c],rem[1-c]);
      else if(rem[1-c]<=K) SMIN(dp[i+1][c],a);
      else if(a<=K) SMIN(dp[i+1][1-c],rem[1-c]-K);
      
      if(rem[1-c]<=K) SMIN(dp[i+1][c],rem[c]);
      else if(rem[c]<=K) SMIN(dp[i+1][1-c],rem[1-c]-K);
    }
  }
  dump2(dp[N][0],dp[N][1]);
  if(dp[N][0]<=K||dp[N][1]<=K) cout<<"YES"<<endl;
  else cout<<"NO"<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>X[i][0];
  REP(i,N) cin>>X[i][1];
  solve();
  
  return 0;
}
