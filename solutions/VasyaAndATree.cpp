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
 
 11/13/2018
 
 21:43-22:15 AC
 
 https://codeforces.com/blog/entry/63151  
 
 */

// 21:43-22:15 AC
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3e5+1;
VI G[MAX_N];
vector<pair<LL,LL>> Q[MAX_N];
int N,M;
LL res[MAX_N];

map<LL,LL> imos;
void dfs(int u, int pre, int d, LL cur) {
  auto qs=Q[u];
  FORR(q,qs) {
    LL k,x; tie(k,x)=q;
    imos[d]+=x;
    imos[d+k+1]-=x;
  }
  if(imos.count(d)) cur+=imos[d];
  res[u]=cur;
  FORR(v,G[u]) if(v!=pre) {
    dfs(v,u,d+1,cur);
  }
  
  // rollback
  FORR(q,qs) {
    LL k,x; tie(k,x)=q;
    imos[d]-=x;
    imos[d+k+1]+=x;
  }
}

void solve() {
  dfs(0,-1,0,0);
  REP(i,N) cout<<res[i]<<" ";
  cout<<endl;
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
  cin>>M;
  REP(i,M) {
    int u; LL d,x; cin>>u>>d>>x;
    --u;
    Q[u].emplace_back(d,x);
  }
  solve();
  
  return 0;
}
