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
 
 10/31/2018
 
 21:58-22:30 give up
 
 Two blockers to solve this problem
  - how to manage k<=10 different digits (# of used digit doesn' work?)
  - how to connect counting with sum of final numbers. Way of left and right matters?
 
 K<=10 is small. Use bit mask to manage what is used
 
 https://codeforces.com/blog/entry/62742
 http://kmjp.hatenablog.jp/entry/2018/10/27/0930
 
 11/1/2018
 
 15:50-17:20 read editorials and add solution
 
 How to solve it?
  - Here is a problem related to yours and solved before. Could you use it? Could you use its result? Could you use its method? Should you introduce some auxiliary element in order to make its use possible?
   - Digit dp is definitely related problem. However I needed to solve auxiliary problem to connect counting problem with summation
   - Bitmask is a typical way to manage state of a set
 
 Summary:
  - I was aware of two dots (summation and counting). I should try more to connect them
  - Many implementation bugs
   - Leading zero is always headache in digit dp
    - if `0` affects state change, we should initiate dp table with dp[i][i>0]=1 (i=0..N-1)
    - if `0` does not affect state, dp[0][0]=1 suffices
   - Lower bound and upper bound of digits
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const LL MOD=998244353;
LL dp[19][1<<10][2],dps[19][1<<10][2];
LL L,R;
int K;
LL P[20];

LL f(LL AA) {
  VI A;
  while(AA>0) A.push_back(AA%10),AA/=10LL;
  reverse(ALL(A));
//  dumpAR(A);
  ZERO(dp),ZERO(dps);
  int N=SZ(A);
  REP(i,N) dp[i][0][i>0]=1;
  REP(i,N)REP(mask,1<<10)REP(less,2) {
    int ld=mask>0?0:1;
    int ud=less?10:A[i]+1;
    FOR(d,ld,ud) {
      int mask2=mask|(1<<d),less2=less|(d<A[i]);
      (dp[i+1][mask2][less2]+=dp[i][mask][less])%=MOD;
      (dps[i+1][mask2][less2]+=dps[i][mask][less]+dp[i][mask][less]*P[N-i-1]%MOD*d%MOD)%=MOD;
    }
  }
  LL res=0;
  REP(mask,1<<10)REP(less,2)if(__builtin_popcount(mask)<=K) {
    (res+=dps[N][mask][less])%=MOD;
  }
  return res;
}

void solve() {
  P[0]=1;
  REP(i,18)P[i+1]=(P[i]*10)%MOD;
  LL r=f(R),l=f(L-1);
//  dump2(r,l);
  cout<<(MOD+r-l)%MOD<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>L>>R>>K;
  solve();
  
  return 0;
}
