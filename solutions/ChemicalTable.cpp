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
 
 7/30/2018 R500 div2
 
 26:25-27:13 1WA on test case #6
 27:45 time is up
 
 7/31/2018
 
 22:00-23:10 read editorials and add solution
 
 Editorials:
  - http://codeforces.com/blog/entry/60920
  - http://ferin-tech.hatenablog.com/entry/2018/07/31/003324
 
 Tweets:
  - https://togetter.com/li/1251978
  - https://twitter.com/satanic0258/status/1023883406822653952
  - https://twitter.com/noimi__/status/1023882923479457792
  - https://twitter.com/noimi__/status/1023883972630073346
 
 From samples, I imagined
 
 ** **
 ** **
 
 ** **
 ** **
 
 => res = R+C-SZ(RS)-SZ(CS)
 
 However empty table does not follow it. res = R+C-1
 I tried to find some property which satisfies both. However no luck 😞
 
 I have no idea how I can come up with bipartite graph from this problem.
 Set of row and set of column are mutually independent set. That's the only key? 🤔
 
 Key:
  - row <=> column bipartite graph
  - Minimal edge to make isolated components into one connected component is |C|-1
 
 Summary:
  - How can we reach an idea to make bipartite graph? 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡
  - If pair of rows and columns matters, bipartite graph is typical? 😞
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 26:25-27:13 1WA on #6
const int MAX_N=2e5+1;
int R[MAX_N],C[MAX_N];
int N,M,Q;

LL solve_wrong() {
  SETI RS,CS;
  REP(i,Q) RS.emplace(R[i]),CS.emplace(C[i]);
  if(RS.empty()&&CS.empty()) return N+M-1;
  return N-SZ(RS)+M-SZ(CS);
}

int uf[2*MAX_N];
int find(int x) { return x==uf[x]?x:uf[x]=find(uf[x]); }
void unite(int x1, int x2) {
  int p1=find(x1),p2=find(x2);
  uf[p1]=p2;
}

LL solve() {
  REP(i,N+M) uf[i]=i;
  REP(i,Q) unite(R[i]-1,N+C[i]-1);
  SETI S;
  REP(i,N+M) S.emplace(find(i));
  return SZ(S)-1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>Q;
  REP(i,Q) cin>>R[i]>>C[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
