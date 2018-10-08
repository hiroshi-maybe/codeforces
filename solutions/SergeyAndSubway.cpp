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
 
 10/5/2018
 
 17:27-17:50 give up
 
 Need to compute all-pairs-shortest-distance? Feasible without lg N LCA?
 how to use additional edges? hypothesis: if d>1, --d happens
 
 10/7/2018
 
 21:00-21:20
 
 All pairs shortest distance on tree:
  - d(u,v) = d(root,u) + d(root,v) - 2*d(root,LCA(u,v))
  - https://mathoverflow.net/questions/59680/all-pairs-shortest-paths-in-trees
 
 Find LCA with union-find tree:
  - https://en.wikipedia.org/wiki/Tarjan%27s_off-line_lowest_common_ancestors_algorithm
  - https://www.geeksforgeeks.org/tarjans-off-line-lowest-common-ancestors-algorithm/

 10/8/2018
 
 12:00-13:15 read submit solutions and tweets and got AC
 
 It's possible to show that for d'(u,v) = ceil(d(u,v)/2)
 I confirmed correctness for two cases:
  - d(ancestor(u),u)
  - d(u,v) (v is not ancestor of u)
 
 Thus..
 
 res = ∑ { ceil(d(u,v)/2) : u,v∈V }
 
 Math solution by @nuip
 https://twitter.com/n_vip/status/1047784314933407745
 https://codeforces.com/contest/1060/submission/43768538
 
 ceil(d(u,v)/2) = d(u,v)/2   if d(u,v) is even
                  d(u,v)/2+1 if d(u,v) is odd
 
 From this formula...
 
   ∑ { ceil(d(u,v)/2) : u,v∈V }
 = ∑ { d(u,v)/2 + parity(d(u,v)) : u,v∈V } /2
 = ∑ { d(u,v)/2 + p : u,v∈V, p = 1 only if color of u,v is different } /2
 = (∑ { d(u,v)/2 } + ∑ { 1 : color(u)!=color(v) })/2
 = (∑ { d(u,v)/2 } + |Black Node|*|White Node|)/2
 
 Key:
  - d'(u,v) = ceil(d(u,v)/2
  - Annoying ceil can be decomposed by parity. Parity can be determined by coloring in tree
  - Sum of parity `1` is number of pairs of nodes with different colors
  - Node color can be determined by depth in tree
  - Sum of all pairs distance in tree can be computed by counting how many time each edge is passed
 
 Summary:
  - How to solve this problem?
   - Look at principal part (additional edges)
   - Problem to prove (show d'(u,v)=ceil(d(u,v)/2)
   - Decompose to two parts (sum of all pairs distance and sum of odd distances)
   - Solve related problem
    - parity => graph coloring
    - sum of number of odd distance pairs => counting problem (form of sum to form of one multiplication)
    - sum of all pairs distances in tree => number of edges to be passed (decomposition)
  - Formula transformation to make it easy
   - ∑ { ceil(d(u,v)/2) : u,v∈V } =>
  - 2-coloring works for parity
   - (w,w) => even, (b,b) => even, (b,w) => odd
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
int V;
vector<int> G[MAX_N];

LL S[MAX_N],D[2];
void dfs(int u, int pre, int d) {
  D[d%2]++;
  LL cnt=1;
  FORR(v,G[u]) if(v!=pre) {
    dfs(v,u,d+1);
    cnt+=S[v];
  }
  S[u]=cnt;
}
LL solve() {
  dfs(0,-1,0);
  LL res=0;
  REP(u,V) res+=S[u]*((LL)V-S[u]);
  res+=D[0]*D[1];
  assert(res%2==0);
  return res/2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>V;
  REP(_,V-1) {
    int u,v;
    cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
  cout<<solve()<<endl;
  
  return 0;
}
