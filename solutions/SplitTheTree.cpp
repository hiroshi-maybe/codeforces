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
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
template<class T> using VV=vector<vector<T>>;
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
 
 10/9/2018
 
 19:50-20:40 give up
 
 Q. Is it possible to keep suboptimality in tree dp for two constraints (L and S)?
 
 http://codeforces.com/blog/entry/62238
  - greedy and segment tree
 https://togetter.com/li/1273669
 https://twitter.com/n_vip/status/1048250457129345024
 https://twitter.com/satanic0258/status/1048251496771416065
 https://twitter.com/btk15049/status/1048251765907283968
 
 References of doubling on a tree:
  - https://www.slideshare.net/satanic2/ss-72500089
   - how to build jump table
  - https://yukicoder.me/wiki/lowest_common_ancestor
  - https://www.npca.jp/works/magazine/2015_5/
 
 Maximum length for each vertex -> feasible by doubling (length increases monotonically)
 Maximum sum for each vertex -> feasible by doubling (cost increases monotonically)
 
 A. Yes it's possible by pre-computing furthest node for each vertices.
 
 Suppose we want to know longest path from vertex `u` to some ancestor.
 Then we can go up with...
 
   max(
    min{ depth: depth[p]-depth[u]=L },
    min{ depth: cum[p]-cum[u]<=S }
  )
 
 http://codeforces.com/contest/1059/submission/43850215 by @kmjp
 http://codeforces.com/contest/1059/submission/43844562 by @nuip
 http://codeforces.com/contest/1059/submission/43859650 by @satanic0
 http://codeforces.com/contest/1059/submission/43842509 by @Benq
 
 22:50 pause
 
 10/10/2018
 
 14:30-17:41 AC (7WA)
 
 Key:
  - path in tree <=> Euler tour in tree or doubling (popular technique in LCA)
  - greedy analysis: merging with subtree is always optimal if possible rather than merging with ancestor
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+10;
int N,L;
LL S;
LL W[MAX_N];
VI G[MAX_N];
int D[MAX_N];
LL cum[MAX_N];
//vector<vector<int>> P;
int P[20][MAX_N];
int X[MAX_N];

struct BinaryLifting {
public:
  int V,root;
  int H;
  BinaryLifting(int root, int V) : V(V), root(root) {
  }
  void buildLiftingTable() {
    H=1;
    while((1<<H)<=V) ++H;
    MINUS(P);
//    P=vector<vector<int>>(H,vector<int>(V,-1));
    
    dfs(root,-1,0,0);
    for(int i=0; i<H; ++i) {
      for(int j=0; j<V; ++j) {
        if(P[i][j]!=-1) P[i+1][j]=P[i][P[i][j]];
      }
    }
  }
private:
  void dfs(int u, int par, int d, int sum) {
    D[u]=d;
    cum[u]=sum+W[u];
    P[0][u]=par;
    for(int v : G[u]) if(v!=par) {
      dfs(v,u,d+1,cum[u]);
    }
  }
};

LL solve() {
  BinaryLifting bf(0,N);
  bf.buildLiftingTable();
//  REP(j,bf.H)REP(i,N) dump3(i,j,P[j][i]);
  
  REP(i,N) {
    int x=i;
    for(int j=bf.H-1; j>=0; --j) {
//      assert(x<N);
      if(x>=0&&P[j][x]!=-1&&D[i]-D[P[j][x]]<=L-1) { x=P[j][x]; }
    }
    int y=i;
    for(int j=bf.H-1; j>=0; --j) {
//      dump4(i,j,y,P[j][y]);
//      dump3(cum[i],cum[P[j][y]],W[P[j][y]]);
      if(y>=0&&P[j][y]>=0&&cum[i]-(cum[P[j][y]]-W[P[j][y]])<=S) y=P[j][y];
    }
//    dump3(i,x,y);
    X[i]=max(x,y);
//    dump2(i,X[i]);
  }
  int res=0;
  const int Inf=1e6;
  for(int u=N-1; u>=0; --u) {
    int x=Inf;
    FORR(v,G[u]) if(X[v]>=0) {
      if(x!=Inf) ++res;
      SMIN(x,X[v]);
    }
//    dump4(u,x,X[u],res);
    if(x!=Inf) SMAX(X[u],x);
    if(X[u]==u) {
      ++res;
      X[u]=-1;
    }
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>L>>S;
  REP(i,N) {
    cin>>W[i];
    if(W[i]>S) {
      cout<<-1<<endl;
      exit(0);
    }
  }
  REP(i,N-1) {
    int p; cin>>p;
    --p;
    G[p].push_back(i+1);
  }
  cout<<solve()<<endl;
  
  return 0;
}
