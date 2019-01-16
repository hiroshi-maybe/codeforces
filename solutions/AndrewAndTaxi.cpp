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

// $ ../batch AndrewAndTaxi | diff AndrewAndTaxi.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AndrewAndTaxi.cpp && ./a.out

/*
 
 1/13/2019
 
 7:24-9:02 No idea how to restore without making cycle by reverse
 9:08 waiting for system test to submit my solution... WA again :(
 
 1/15/2019
 
 14:30-16:40 read editorials and got AC
 
 https://codeforces.com/blog/entry/64545
 https://codeforces.com/blog/entry/64543
 https://codeforces.com/blog/entry/64532
 
 I didn't have clear proof that we can build DAG whenever remaining edges have no cycle after removing edges that we can choose direction.
 
 Key:
  - No cycle in a directed graph <=> DAG
  - Cycle detection <=> topological sort or dfs by 3-coloring
  - Monone property in terms of edge weight <=> binary search by removing edges
  - DAG construction <=> Topological sort and add edges following topological order
 
 */

const int MAX_N=1e5+1;
vector<tuple<int,int,LL>> G[MAX_N];
int N,M;

vector<tuple<int,int,LL>> GG[MAX_N];

vector<int> tsort(vector<vector<tuple<int,int,LL>>> &G) {
  int N=SZ(G);
  vector<int> D(N,0);
  REP(u,N) {
    FORR(t,G[u]) {
      int v,i; LL c; tie(v,i,c)=t;
      D[v]++;
    }
  }
  vector<int> res;
  queue<int> Q;
  REP(u,N) if(D[u]==0) Q.emplace(u);
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
    res.push_back(u);
    FORR(t,G[u]) {
      int v,i; LL c; tie(v,i,c)=t;
      D[v]--;
      if(D[v]==0) Q.emplace(v);
    }
  }
//  dumpAR(res);
  return res;
}

vector<vector<tuple<int,int,LL>>> filtere(LL T) {
  vector<vector<tuple<int,int,LL>>> res(N);
  REP(u,N) FORR(t,G[u]) {
    int v,i; LL c; tie(v,i,c)=t;
    if(c>T) res[u].emplace_back(v,i,c);
  }
  return res;
}

void solve() {
  LL good=1e9,bad=-1;
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2LL;
    
    vector<vector<tuple<int,int,LL>>> GG=filtere(m);
    VI o=tsort(GG);
    bool x=SZ(o)==N;
    (x?good:bad)=m;
  }
  
  vector<vector<tuple<int,int,LL>>> GG=filtere(good);
  auto us=tsort(GG);
  VI ord(N); REP(i,N) ord[us[i]]=i;
  
  assert(SZ(ord)==N);
  VI res;
  REP(u,N) FORR(t,G[u]) {
    int v,i; LL c; tie(v,i,c)=t;
    if(ord[v]<ord[u]) res.push_back(i);
  }
  
  println("%lld %d", good,SZ(res));
  FORR(i,res) printf("%d ",i+1);
  println("");
}

int viz[MAX_N]; // -1: w, 0: g, 1: b
int done[MAX_N]; // 1: cycle, 0: no-cycle, -1: unknown

bool dfs(int u, LL T) {
  if(viz[u]!=-1) {
    if(viz[u]==0) dump(u);
    return done[u]=(viz[u]==0);
  }
  viz[u]=0;
  
  int res=false;
  for(auto p: G[u]) {
    int v,_; LL c; tie(v,_,c)=p;
    if(c>T) {
      if(viz[v]==-1) dfs(v,T);
      res|=done[v];
    }
  }
  viz[u]=1;
//  if(done[u]) dump(u);
  return done[u]=res;
}
bool f(LL T) {
  MINUS(viz),MINUS(done);
  REP(u,N) {
    if(viz[u]==-1) dfs(u,T);
//    assert(done[u]==0);
    if(done[u]) return false;
  }
  return true;
}

int D[MAX_N];
void solve_org() {
  LL good=1e9,bad=-1;
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2LL;
    bool x=f(m);
//    dump2(m,x);
    (x?good:bad)=m;
  }
  
  VI res;
  REP(u,N) FORR(t,G[u]) {
    int v,i; LL c; tie(v,i,c)=t;
    if(c<=good) {
      GG[v].emplace_back(u,i+M,-c);
      GG[u].emplace_back(v,i,-c);
    } else {
      GG[u].emplace_back(v,i,c);
      D[v]++;
    }
  }
  dumpc(D,D+N);
  queue<int> Q;
  SETI ans,vize;
  REP(i,N) if(D[i]==0) Q.emplace(i);
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
    dump(u);
    FORR(t,GG[u]) {
      int v,i; LL c; tie(v,i,c)=t;
      dump4(u,v,i,c);
      if(c<0) {
        int ii=i%M;
        if(i>=M&&!vize.count(ii)) {
          dump4(u,v,ii,c);
          ans.emplace(ii);
        }
        vize.emplace(ii);
      } else {
        D[v]--;
        if(D[v]==0) Q.emplace(v);
        dump3(u,D[v],v);
      }
    }
  }
  
  println("%lld %d", good,SZ(ans));
  FORR(i,ans) printf("%d ",i+1);
  println("");
}

void solve_wrong() {
  LL good=1e9,bad=-1;
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2LL;
    bool x=f(m);
    dump2(m,x);
    (x?good:bad)=m;
  }
  
  VI res;
  REP(u,N) FORR(t,G[u]) {
    int v,i; LL c; tie(v,i,c)=t;
    if(c<=good) {
      GG[v].emplace_back(u,i,c);
      res.push_back(i+1);
    }
  }
  
  SETI S;
  MINUS(viz),MINUS(done);
  REP(u,N) {
    if(viz[u]==-1) dfs(u,0);
    //    assert(done[u]==0);
    if(done[u]) {
      FORR(t,GG[u]) {
        int v,i; LL c; tie(v,i,c)=t;
        if(done[v]==1) S.emplace(i+1);
      }
    }
  }
  VI ans;
  REP(i,SZ(res))if(!S.count(res[i])) ans.push_back(res[i]);
  
  println("%lld %d", good,SZ(ans));
  REP(i,SZ(ans)) printf("%d ",ans[i]);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,M) {
    int u,v; LL c; cin>>u>>v>>c;
    --u,--v;
    G[u].emplace_back(v,i,c);
  }
  solve();
  
  return 0;
}
