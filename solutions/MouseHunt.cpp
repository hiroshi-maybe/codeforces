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
 
 8/18/2018
 
 8:49-9:18 AC
 
 Editorials:
  - http://codeforces.com/blog/entry/61311
   - finding cycle by dfs is smart
  - http://betrue12.hateblo.jp/entry/2018/08/19/182014
   - SCC
 
 */

// 9:18 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
int N;
SETI E[MAX_N];
int IND[MAX_N];
LL C[MAX_N];

const LL Inf=1e11;
LL cost=Inf;
int viz[MAX_N];
void dfs(int u) {
  if(viz[u]!=-1) return;
  viz[u]=1;
  SMIN(cost,C[u]);
  FORR(v,E[u]) dfs(v);
}

void solve() {
  set<II> Q;
  REP(u,N) Q.emplace(IND[u],u);
  while(true) {
    assert(SZ(Q));
//    dump(SZ(Q));
    auto it=Q.begin();
    int d,u; tie(d,u)=*it; Q.erase(it);
    if(d!=0) break;
//    dump2(d,u);
    VI vs(E[u].begin(),E[u].end());
    FORR(v,vs) {
//      dump(v);
      auto it2=Q.find({IND[v],v});
      E[u].erase(v);
      if(it2!=Q.end()) {
        Q.erase(it2);
        IND[v]--;
        Q.emplace(IND[v],v);
//        dump2(v,IND[v]);
      }
    }
  }
  
  LL res=0;
  MINUS(viz);
  REP(u,N) if(SZ(E[u])&&viz[u]==-1) {
    cost=Inf;
    dfs(u);
    res+=cost;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>C[i];
  REP(u,N) {
    int v; cin>>v;
    --v;
    E[u].emplace(v);
    IND[v]++;
  }
  solve();
  return 0;
}
