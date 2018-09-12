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
 
 9/7/2018
 
 9:27-10:29 AC after contest ended
 
 http://codeforces.com/blog/entry/61727
 http://betrue12.hateblo.jp/entry/2018/09/08/101540
 https://www.hamayanhamayan.com/entry/2018/09/08/184514
 http://codeforces.com/contest/1036/submission/42627517 by @pekempey
 http://codeforces.com/contest/1036/submission/42627155 by @satanic0
 
 Digit dp:
  - https://pekempey.hatenablog.com/entry/2018/09/01/203543
  - https://pekempey.hatenablog.com/entry/2015/12/09/000603
 
 */

// 10:29 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e4+1;
int T;
LL L[MAX_N],R[MAX_N];
LL memo[63][4][2][2];
vector<int> D;
LL f(int p, int n, int any, int fst) {
  if(n>3) {
//    dump4(p,n,any,fst);
    return 0;
  }
  int N=SZ(D);
  if(p==N) return 1;
  LL &res=memo[p][n][any][fst];
  if(res>-1) return res;
  res=0;
  FOR(d,fst,10) {
    if(!any&&D[p]<d) continue;
    LL a=f(p+1,n+(d>0),any|(D[p]>d),0);
//    dump4(p,n,any,fst);
//    dump2(d,a);
    res+=a;
  }
  return res;
}
void mk(LL x) {
  D.clear();
  while(x>0) D.push_back(x%10),x/=10;
  reverse(D.begin(),D.end());
//  dumpAR(D);
}
LL solve_org(LL n) {
  MINUS(memo),mk(n);
  LL res=0;
  REP(i,SZ(D)) res+=f(i,0,i>0,1);
  dump2(n,res);
  return res;
}

LL dp[20][5][2];
LL solve(LL n) {
  ZERO(dp),mk(n);
  dp[0][0][0]=1;
  int N=SZ(D);
  REP(i,N)REP(j,4)REP(less,2) {
    int ub=less?9:D[i];
    REPE(d,ub) {
      dp[i+1][j+(d!=0)][less|(d<D[i])]+=dp[i][j][less];
    }
  }
  LL res=0;
  REP(j,4)REP(less,2)res+=dp[N][j][less];
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>T;
  REP(i,T) cin>>L[i]>>R[i];
  REP(i,T) cout<<solve(R[i])-solve(L[i]-1)<<endl;
  return 0;
}
