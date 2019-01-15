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

// $ ../batch GCDCounting | diff GCDCounting.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GCDCounting.cpp && ./a.out

/*
 
 1/12/2019
 
 15:18-15:54 AC
 
 https://codeforces.com/blog/entry/64483
 
 */

const int MAX_N=2e5+10;
int A[MAX_N];
VI G[MAX_N];
int N;

map<int,int> memo[MAX_N];
int res=0;
void dfs(int u, int pre) {
  VI P;
  int a=A[u];
  for(int p=2; p*p<=a; ++p) if(a%p==0) {
    P.push_back(p);
    while(a%p==0) a/=p;
  }
  if(a!=1) P.push_back(a);
  FORR(v,G[u]) if(v!=pre) dfs(v,u);
  FORR(p,P) {
    int m1=0,m2=0;
    FORR(v,G[u]) if(v!=pre) {
      int cnt=memo[v][p];
//      dump4(u,p,v,cnt);
      if(cnt>m2) m2=cnt;
      if(m2>m1) swap(m1,m2);
    }
//    dump4(u,p,m1,m2);
    SMAX(res,m1+m2+1);
    memo[u][p]=m1+1;
  }
}
void solve() {
  dfs(0,-1);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  solve();
  
  return 0;
}
