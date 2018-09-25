#include <iostream>
#include <iomanip>
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
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
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
 
 9/20/2018
 
 8:49-9:33 AC
 
 http://codeforces.com/blog/entry/61969
 http://betrue12.hateblo.jp/entry/2018/09/23/191155
 
 */

// 9:33 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
int N,K;
LL dp[MAX_N][2*MAX_N][4];
const LL MOD=998244353;
void solve() {
  ZERO(dp);
  REP(i,4)dp[0][(i==1||i==2)?2:1][i]=1;
  FOR(i,1,N)REPE(k,2*N) REP(pre,4) REP(cur,4) {
    int dif=__builtin_popcount(pre^cur);
    if(dif==1) dif=(pre==0||pre==3)?1:0;
    else if(dif==2) dif=(cur==0)||(cur==3)?1:2;
//    if(k+dif==3&&dp[i-1][k][pre]>0) dump4(k,pre,cur,dif);
//    if(k+dif==3)assert(dp[i-1][k][pre]==0);
    (dp[i][k+dif][cur]+=dp[i-1][k][pre])%=MOD;
  }
  LL res=0;
  REP(m,4) res+=dp[N-1][K][m],res%=MOD;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  solve();
  return 0;
}
