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
 
 8/8/2018
 
 8:25-9:01 AC
 
 Editorials:
  - https://codeforces.com/blog/entry/61081
  - https://twitter.com/satanic0258/status/1027237112712593408
 
 Reference: https://en.wikipedia.org/wiki/Dilworth%27s_theorem
 
 */

// 8:25-9:01 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N;
LL A[MAX_N];
int f(int x, int N) {
  return (N+x-1)/x+x;
}
void solve() {
  int p=1;
  FORE(x,1,N) if(f(p,N)>f(x,N)) p=x;
  VI res;
  dump2(p,f(p,N));
  int G=N/p;
  REP(i,G) REP(j,p) res.push_back(N-(i+1)*p+j+1);
  FOR(n,1,N-G*p+1) res.push_back(n);
  assert(SZ(res)==N);
  REP(i,N) cout<<res[i]<<(i==N-1?'\n':' ');
}

int lislds(VI P) {
  int N=SZ(P);
  int lis=0,lds=0;
  int dp1[100]={0},dp2[100]={0};
   REP(i,N)dp1[i]=dp2[i]=1;
  REP(i,N) REP(j,i) {
    if(P[j]<P[i]) SMAX(dp1[i],dp1[j]+1),SMAX(lis,dp1[i]);
    if(P[j]>P[i]) SMAX(dp2[i],dp2[j]+1),SMAX(lds,dp2[i]);
  }
  return lis+lds;
}

void f(int N) {
  VI P(N);
  REP(i,N)P[i]=i+1;
  set<VI> res;
  int mins=N*N;
  do {
    int lis=0,lds=0;
    int dp1[100]={0},dp2[100]={0};
    REP(i,N)dp1[i]=dp2[i]=1;
    REP(i,N) REP(j,i) {
      if(P[j]<P[i]) SMAX(dp1[i],dp1[j]+1),SMAX(lis,dp1[i]);
      if(P[j]>P[i]) SMAX(dp2[i],dp2[j]+1),SMAX(lds,dp2[i]);
    }
    if(lis+lds==mins) res.emplace(P);
    else if(lis+lds<mins) res.clear(),mins=lis+lds,res.emplace(P);
  } while(next_permutation(P.begin(),P.end()));
  
  dump2(N,mins);
  if(N==9) FORR(a,res) dumpAR(a);
}

void test() {
//  dump(lislds({3,4,2,1}));
//  dump(lislds({4,5,1,2,3}));
  REP(i,10) f(i+1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
//  test();
  
  cin>>N;
  solve();
  return 0;
}
