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
 
 11/4/2018 Lyft 5 Final
 
 11:40-12:40 time is up
 
 I tried to figure out worst case and how to narrow down nodes to be queried.
 However I had no idea.
 
 11/5/2018
 
 19:55-21:43 read editorial and got AC
 
 http://codeforces.com/blog/entry/62985
 
 ```
 Here is why it works. Let's use the fact that if the two subtrees don't intersect, there is an edge in the tree such that if we cut the tree on this edge, it will split it into two components, each containing one of the subtrees.
```
 
 I tried to do induction from some special tree structure.
 However it didn't work.
 Actually key of observation is classification of general case
 
 If this problem is solved, how does it settle down?
 `A x` in Y or `B y` in X should give conclusion. However it's not still clear which is better.
 
 Let's think about which `A` query or `B` query is benefitial for the first query.
 If luckily `A` query with node in X hits Y, problem is solved.
 Otherwise, we don't have further information. Thus this query is not useful to obtain something at first.
 However `B` gives rough position of opponent's subtree. This seems to be better first step.
 
 I haven't evaluated how `B` query should be used.
 It's actually benefitial because I can roughly estimate where `Y` subtree is located.
 
 How to solve it?
  - Did you use all the data? Did you use the whose condition?
   - Analysis of `B` query was not enough
  - You may be obliged to consider auxiliary problems if an immediate connection cannot be found
   - two exclusive auxiliary problems can be reduced in terms of tree intersection
  - Could you derive something userful from the data?
   - two cases { trees intersect, trees do not intersect }
  - Have you taken int account all essential notions involved in the problem?
   - some useful property should be used of tree (not graph)

 Summary:
  - Analysis of usefulness of `B` query was missing.
  - Induction from special case is often very useful. However don't forget to evaluate the condition in general form. Condition can be decomposed to a few cases.
  - Decomposition is kind of auxiliary problem"s"! Don't be afraid of splitting problems!
  - Exclusive and exhausitive decomposition is easy because we often don't need proof. Try it out too
  - I paid too much attention to maximum number of queries.
  - Writing two separated trees in the note was also a failure. I missed a chance to understand exhausitive cases.
  - In interaction problem, many things are unknown. However there should be some general cases. Use it to prove sufficiency.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
VI G[MAX_N];
int N,K1,K2;
SETI X,Y;

int cnt=0;
int ask(int q, int u) {
  assert(cnt<5);
  cout<<(char)('A'+q)<<" "<<u+1<<endl;
  cout.flush();
  int res; cin>>res;
  if(res==-1) {
    exit(0);
  }
  assert(res!=-1);
  return res-1;
}
void ans(int u) {
  if(u!=-1) ++u;
  cout<<"C "<<u<<endl;
  cout.flush();
}

int dfs(int u, int pre) {
  if(X.count(u)) return u;
  FORR(v,G[u])if(v!=pre) {
    int w=dfs(v,u);
    if(w!=-1) return w;
  }
  return -1;
}

void solve() {
  int y1=*(Y.begin());
  int x=ask(1,y1);
  int x1=dfs(x,-1);
  int y=ask(0,x1);
  if(Y.count(y)) ans(x1);
  else ans(-1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int T;
  cin>>T;
  REP(i,T) {
    cnt=0;
    REP(i,MAX_N)G[i].clear();
    X.clear(),Y.clear();
    
    cin>>N;
    REP(i,N-1) {
      int u,v; cin>>u>>v;
      --u,--v;
      G[u].push_back(v),G[v].push_back(u);
    }
    cin>>K1;
    REP(i,K1) {
      int u; cin>>u;
      X.emplace(--u);
    }
    cin>>K2;
    REP(i,K2) {
      int u; cin>>u;
      Y.emplace(--u);
    }
    solve();
  }
  
  return 0;
}
