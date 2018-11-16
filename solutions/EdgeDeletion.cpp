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
 
 20:45-21:42 AC
 
 https://codeforces.com/blog/entry/63151
 
 First K vertices found by Dijkstra's algorithm is the solution
 
 Proof:
  By keeping K-edges, we can have at most min(N,K) good vertices.
  It's possible to show that this is always feasible (sufficient).
  In the process of Dijkstra's algorithm, whenever we find a new shortest path, one new edge is appended as part of the shoftest path. Thus Dijkstra's algorithm can find min(N,K) good vertices.
 
 */

// 21:42 AC
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3e5+1;
int N,M,K;
map<II,int> eid;
bool X[MAX_N];
int from[MAX_N];

const long long Inf=1e17;
const int MAX_V=MAX_N;
long long D[MAX_V];
vector<pair<int,long long>> G[MAX_N];
void dijkstra(int V, int st) {
  for(int i=0; i<V; ++i) D[i]=Inf;
  set<tuple<long long,int>> Q; Q.emplace(0,st); D[st]=0;
  
  int cnt=0;
  while(Q.size()>0) {
    auto it=Q.begin(); Q.erase(it);
    int u; long long d;
    tie(d,u)=*it;
    
    if(from[u]!=-1) {
      int x=from[u],y=u;
      if(x>y) swap(x,y);
      int id=eid[{x,y}];
      if(cnt<K) X[id]=1;
      ++cnt;
    }
    
    for(auto p : G[u]) {
      int v; long long w; tie(v,w)=p;
      if(d+w<D[v]) {
        auto it2=Q.find({D[v],v});
        if(it2!=Q.end()) Q.erase(it2);
        D[v]=d+w; Q.emplace(d+w,v);
        from[v]=u;
      }
    }
  }
}

void solve() {
  MINUS(from);
  ZERO(X);
  dijkstra(N,0);
  VI res;
  REP(i,M) if(X[i]) res.push_back(i);
  cout<<SZ(res)<<endl;
  REP(i,SZ(res)) cout<<res[i]+1<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>K;
  REP(i,M) {
    int u,v; LL w; cin>>u>>v>>w;
    --u,--v;
    if(u>v) swap(u,v);
    eid[{u,v}]=i;
    G[u].emplace_back(v,w),G[v].emplace_back(u,w);
  }
  
  solve();
  
  return 0;
}
