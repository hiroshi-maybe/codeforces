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

// $ ../batch MinimumDiameterTree | diff MinimumDiameterTree.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MinimumDiameterTree.cpp && ./a.out

/*
 
 12/23/2018
 
 06:31-7:20 give up
 
 12/30/2018
 
 15:05-17:05 read editorial and got AC
 
 https://codeforces.com/blog/entry/64078
 https://betrue12.hateblo.jp/entry/2018/12/26/002629
 
 It was pretty hard to understand below logic in editorials:
 
 ∑{dist(x,y)} >= (L-1)*∑{w[e]:e∈E}
 
 We need to show optimality to figure out that above inequality is "minimal".
 It's possible to put `0` weight to edges which is not adjacent to leaves WITHOUT changing total weight of edges.
 Then all the weights are distributed to edges with leaves which contributes to (L-1)*1 paths.
 
 I couldn't even "guess" that putting equal weights to all the edges adjacent to leaves.
 
 1. Understand that equal diameter for all the paths are optimal. This is property of summation of min max out of a set
 2. It's possible if `0` weights to edges which is not adjacent to edges to balance diameter
 3. We can show that by focusing on contribution of each edge (which is typical technique to compute sum of all pairs paths in a tree)
 4. Try to connect max diameter with summation of edges in inequality
 
 */

const int MAX_N=1e6;
int N;
LL S;
VI G[MAX_N];

void solve() {
  int L=0;
  REPE(i,N) if(SZ(G[i])==1) ++L;
//  dump2(S,L);
  double res=2.0*S/L;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(18)<<fixed;
  
  cin>>N>>S;
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  solve();
  
  return 0;
}
