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

// $ ../batch SumInTheTree | diff SumInTheTree.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SumInTheTree.cpp && ./a.out

/*
 
 1/5/2019
 
 9:42-10:06 WA
 10:49 AC
 
 */

const int MAX_N=1e6+1;
VI G[MAX_N];
LL S[MAX_N];
int N;

LL Inf=1e16;
LL res=0;

LL memo[MAX_N];
LL mindfs(int u) {
  LL &res=memo[u];
  if(res>=0) return res;
  res=S[u]!=-1?S[u]:Inf;
  FORR(v,G[u]) SMIN(res,mindfs(v));
  return res;
}

void dfs(int u, LL cur) {
  LL lb=Inf;
  FORR(v,G[u]) SMIN(lb,mindfs(v));
  LL s=S[u]!=-1?S[u]:Inf;
  assert(cur<=s);
  if(s!=Inf&&s>lb) {
    res=Inf;
    return;
  }
  s=min(s,lb);
  if(s>=Inf) s=cur;
  assert(cur<=s);
  LL a=s-cur;
  res+=a;
  FORR(v,G[u]) dfs(v,cur+a);
}

void solve() {
  MINUS(memo);
  dfs(0,0);
  if(res>=Inf) res=-1;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N-1) {
    int p; cin>>p;
    --p;
//    dump2(p,i+1);
    G[p].push_back(i+1);
  }
  REP(i,N) cin>>S[i];
  solve();
  
  return 0;
}
