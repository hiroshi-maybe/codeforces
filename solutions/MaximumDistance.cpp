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

// $ ../batch MaximumDistance | diff MaximumDistance.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MaximumDistance.cpp && ./a.out

/*
 
 1/7/2019
 
 10:47-11:20, 12:20-13:03 AC
 
 https://codeforces.com/blog/entry/63888
 https://betrue12.hateblo.jp/entry/2018/12/17/213944
 
 The challenge was noticing result for all the x[i] vertices is same.
 Once this is proved, coming up with binary search which is typical to find max-min value is straightforward.
 
 Maximum edges between u and v = D <=> Connected when edges whose weight <D are removed
 
 */

const int MAX_N=1e5+1;
vector<II> G[MAX_N];
int N,M,K;
int X[MAX_N];

int cnt=0,W;
int viz[MAX_N];
void dfs(int u) {
  if(viz[u]) return;
  viz[u]=1;
  if(X[u]) {
    ++cnt;
//    dump2(u,cnt);
  }
  FORR(p,G[u]) {
    int v,w; tie(v,w)=p;
//    dump4(u,v,w,w<=W);
    if(w<=W) dfs(v);
  }
}
bool f(int A, int u0) {
  ZERO(viz),cnt=0,W=A;
//  dump4(u0,A,cnt,K);
  dfs(u0);
//  dump4(u0,A,cnt,K);
  return cnt==K;
}
void solve_org(int u0) {
  int good=1e9,bad=0;
  while(abs(good-bad)>1) {
    int mid=(good+bad)/2;
    (f(mid,u0)?good:bad)=mid;
  }
  REP(i,K) printf("%d ",good);
  println("");
}

priority_queue<III> Q;
int uf[MAX_N],S[MAX_N];
int find(int u) { return u==uf[u]?u:uf[u]=find(uf[u]); }
int unite(int a, int b) {
  int pa=find(a),pb=find(b);
  if(pa==pb) return S[pa];
  uf[pb]=pa;
  S[pa]+=S[pb];
  return S[pa];
}

void solve(int u0) {
  REP(i,N) {
    uf[i]=i;
    if(X[i]) S[i]=1;
  }
  int res=-1;
  while(SZ(Q)) {
    int u,v,w; tie(w,u,v)=Q.top(); Q.pop();
    w=-w;
    int x=unite(u,v);
    if(x==K) {
      res=w;
      break;
    }
  }
  assert(res!=-1);
  REP(i,K) printf("%d ",res);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>K;
  int u0=-1;
  REP(i,K) {
    int x; cin>>x;
    --x;
    X[x]=1;
    u0=x;
  }
  assert(u0>=0);
  REP(i,M) {
    int u,v,w; cin>>u>>v>>w;
    --u,--v;
    Q.emplace(-w,u,v);
//    dump3(u,v,w);
    G[u].emplace_back(v,w);
    G[v].emplace_back(u,w);
  }
  solve(u0);
  
  return 0;
}
