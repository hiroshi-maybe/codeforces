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
 
 19:40-21:11 I cannot understand why {delete no edges} and {delete (2,3)} are unique each other.
 21:15 I understand what unique means. Probably it's saying that resulting matching is "deterministic". Very poor problem statement.
 21:40 give up. I tried to solve a problem without deletion. However no luck.
 
 - drop condition of deletion
 - tree dp (edges enumeration)
 - parity of edges
 
 11/28/2018
 
 14:10-17:00 read editorials and got AC
 
 https://codeforces.com/blog/entry/63324
 
 Perfect matching <=> maximum matching is deteministic
 
 https://en.wikipedia.org/wiki/Matching_(graph_theory)
 
 Summary:
  - it's hard to solve without knowing perfect matching property
 
 */

// $ ../batch VasyaAndMaximumMatching | diff VasyaAndMaximumMatching.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address VasyaAndMaximumMatching.cpp && ./a.out
const int MAX_N=3e5+1;
VI G[MAX_N];
int N;
LL memo[MAX_N][3];
const LL MOD=998244353;

LL powmod(LL a, LL b) {
  assert(0<=a);
  assert(0<=b);
  a%=MOD;
  
  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}
LL modinv(LL a, LL p=MOD) {
  return powmod(a, p-2);
}

LL f(int u, int st, int pre) {
  LL &res=memo[u][st];
  if(res>=0) return res;
  int ccnt=0;
  FORR(v,G[u]) ccnt+=(v!=pre);
  if(ccnt==0) {
    return res=(st!=1);
  }
  res=1;
  if(st==2) {
    FORR(v,G[u])if(v!=pre) {
      res*=f(v,2,u),res%=MOD;
    }
    LL a=f(u,1,pre);
    res=(res+a)%MOD;
    return res;
  }
  LL P=1;
  FORR(v,G[u])if(v!=pre) {
    P*=(f(v,2,u)+f(v,1,u))%MOD,P%=MOD;
  }
  if(st==0) return res=P;
  
  res=0;
  FORR(v,G[u])if(v!=pre) {
    LL a=f(v,0,u);
    LL b=modinv((f(v,1,u)+f(v,2,u))%MOD);
    a*=P*b%MOD,a%=MOD;
    res=(res+a)%MOD;
  }
  return res;
}

void solve() {
  MINUS(memo);
  LL res=f(0,2,-1);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
  solve();
  
  return 0;
}
