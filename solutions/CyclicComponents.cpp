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
 
 5/7/2018 R479 div3
 
 24:21-24:51 AC
 
 Editorials:
  - http://codeforces.com/blog/entry/59281
  - http://tancahn2380.hatenablog.com/entry/2018/05/09/045642
 
 */

// 24:48 TLE
// 24:51 AC
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_V=2e5+1;
int DE[MAX_V];
int V,E;
/*
struct GraphCycle {
public:
  // input
  int V;
  vector<vector<int>> G;
  GraphCycle(int V): V(V), G(V), done(V, -1), viz(V, 0) {}
  void edge(int u, int v) {
    assert(u<V&&v<V);
    G[u].push_back(v);
  }
  
  vector<int> findCycles() {
    vector<int> res;
    for(int u=0; u<V; ++u) {
      if(!viz[u]) {
        dfs(u,-1);
        if(done[u]) res.push_back(u);
      }
    }
    dumpAR(res);
    return res;
  }
private:
  vector<int> done; // -1: not done, 0: descendent has NO cycle, 1: descendent has cycle
  vector<int> viz;
  
  int dfs(int u, int pre) {
    if(done[u]!=-1) return done[u];
    viz[u]=true;
    
    int res=false;
    for(int v : G[u]) if(v!=pre) {
      if(!viz[v]) dfs(v,u);
      res|=done[v]==-1?true:done[v];
    }
    return done[u]=res;
  }
};*/
struct UF {
public:
  int groupNum;
  UF(int N) {
    uf=vector<int>(N);
    rank=vector<int>(N);
    for(int i=0; i<N; ++i) uf[i]=i,rank[i]=0;
    groupNum=N;
  }
  
  int find(int i) {
    return uf[i]==i?i:uf[i]=find(uf[i]);
  }
  
  bool same(int x, int y) {
    return find(x)==find(y);
  }
  
  void unite(int x, int y) {
    x=find(x);
    y=find(y);
    if(x==y) return;
    groupNum--;
    
    if (rank[x]==rank[y]) {
      uf[x]=y;
      rank[y]++;
      return;
    }
    
    if (rank[x]<rank[y]) {
      uf[x]=y;
    } else {
      uf[y] =x;
      if(rank[x]==rank[y]) ++rank[x];
    }
  }
private:
  vector<int> rank;
  vector<int> uf;
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>V>>E;
  UF uf(V);
  REP(i,E) {
    int u,v;
    cin>>u>>v;
    --u,--v;
    uf.unite(u,v);
    DE[u]++,DE[v]++;
  }
  
  int res=0;
  unordered_map<int,vector<int>> S;
  REP(u,V) S[uf.find(u)].push_back(u);
  FORR(kvp,S) {
    bool ok=true;
    FORR(v,kvp.second) ok&=(DE[v]==2);
    res+=ok;
  }
  cout<<res<<endl;
  
  return 0;
}

// 1. more precision in double in iostream
// cout<<setprecision(12)<<fixed;
