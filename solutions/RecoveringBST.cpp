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
 
 8/19/2018
 
 7:47-8:54 time is up
 20:15-21:15 read editorials and add solution
 
 Editorials:
  - http://codeforces.com/blog/entry/61323
  - http://kmjp.hatenablog.jp/entry/2018/08/20/0930
 
 Tweets:
  - https://togetter.com/li/1258285
  - https://twitter.com/chokudai/status/1031219549142577154
  - https://twitter.com/n_vip/status/1031207497107947520
  - https://twitter.com/beet_aizu/status/1031206813071339521
  - https://twitter.com/satanic0258/status/1031208997158772737
 
 Key:
  - typical interval dp
  - if interval and Left or Right is determined, no need to remember root in dp state
 
 Summary:
  - No idea of interval dp during the contest
  - brute-force search first. dp is just an optimization of it
  - smart greedy optimization is next step of search
  - constant optimization of early exit is needed to avoid TLE 😡
 
 */
// 8:54 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=700+1;
int N;
LL A[MAX_N];

vector<LL> distinctPrimeFactors(LL n) {
  /*
   vector<LL> res=primeFactors(n);
   res.erase(unique(res.begin(),res.end()),res.end());
   return res;
   */
  assert(n>=1);
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) if(n%p==0) {
    res.push_back(p);
    while(n%p==0) n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}

SETI P[MAX_N];
SETI G[MAX_N];

bool interx(SETI a, SETI b) {
  FORR(x,a) if(b.count(x)) return true;
  return false;
}

int viz[MAX_N];
VI E[MAX_N];

void dfs(int u) {
  if(viz[u]) return;
  viz[u]=1;
  FORR(v,E[u]) dfs(v);
}

/*
 
 Below test case doesn't pass
 
 4
 2 3 5 30
 
 */
bool solve_wrong() {
  REP(i,N) {
    vector<LL> x=distinctPrimeFactors(A[i]);
    SETI S(x.begin(),x.end());
    P[i]=S;
  }
  
//  dump(interx(P[0],P[1]));
  
  int M=0;
  SETI S;
  G[0]=P[0];
  REP(i,N-1) {
    if(!interx(P[i],P[i+1])) ++M;
    FORR(p,P[i+1]) G[M].emplace(p);
  }
  ++M;
  
//  dump(M);
  REP(j,M)REP(i,j) {
    if(interx(G[i],G[j])) E[i].push_back(j),E[j].push_back(i);
  }
  
  ZERO(viz);
  dfs(0);
  REP(i,M) if(!viz[i]) return false;
  return true;
}

int memo[MAX_N][MAX_N][2];
int mx[MAX_N][MAX_N];

bool f(int l, int r, bool lr) {
  if(l==r) return true;
  int &res=memo[l][r][lr];
  if(res>=0) return res;
//  dump3(l,r,lr);
  int root=lr?l-1:r;
  res=false;
  FOR(i,l,r) if(mx[i][root]) {
    // early exit didn't cause TLE
    bool x=f(l,i,0)&&f(i+1,r,1);
    if(x) return res=true;
  }
  return res=false;
}

int gcd(int a, int b) {
  return b==0?a:gcd(b,a%b);
}
bool solve() {
  MINUS(memo);
  REP(i,N)REP(j,N) mx[i][j]=gcd(A[i],A[j])>1;
  
  bool res=false;
  REP(i,N) res|=f(0,i,0)&&f(i+1,N,1);
  return res;
}

const string yes="Yes",no="No";
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<(solve()?yes:no)<<endl;
  return 0;
}
