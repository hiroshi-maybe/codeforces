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
// minmax
template<class T> inline bool SMIN(T &l,const T &r){return l<r?l=r,1:0;}
template<class T> inline bool SMAX(T &l,const T &r){return l>r?l=r,1:0;}
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
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 10/25/2018
 
 24:11-24:41 give up
 
 10/26/2018
 
 My analysis:
  - I put A and B lines with D=Y2-Y1 gap vertically to simplify reflection condition
   => D does not matter ❌
  - 2<=res<=N+M
   => ✅
  - incline 𝛂 = d/(x1-x2) of the razor, x1∈A,x2∈B
   => d does not matter ❌
  - Is it possible to find optimal 𝛂?
   => d does not matter ❌
  - If 𝛂 is known, can we figure out how many sensors are hit?
   => d does not matter ❌
  - Can we use cycle of D?
   => D does not matter ❌
  - do I know a problem with similar unknown (maximization)?
   - search and solve decision problem
   - search, compare and get maximal
   - dp
   => Search and compare is the method. Finding necessary search scope is the main key ✅
  - do I know similar problem?
   - geometry problem by brute-forcing incline of two points. However I cannot enumerate pairs for N=1e5
   => Cycle and modular airthmetic is the key due to integer coordinate ❌
 
 I figured out that I was actually missing a condition that one point should be chosen from A and the other from B. Lol.
 
 17:30-17:55 pause
 
 10/27/2018
 
 13:00-14:45 read editorials and got AC
 
 http://kmjp.hatenablog.jp/entry/2018/09/17/0930
 http://betrue12.hateblo.jp/entry/2018/09/17/015954
 
 It's obvious that modular arithmetic is necessary.
 The key is finding necessary scope of cycle `M`.
 Observation by experiment is needed. If `d` is the delta, {odd}*d cycle is always subset of {d} cycle.
 
 x = x0 + 2*d*k
 
 There are two independent factors: `d` and `x0`.
 If `x0` is different for same `d`, razor points are different. We need to search it.
 If `d` is different, set of points for `d` is subset of `dd`.
 Finding the condition between `d` and `dd` is the key.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
LL A[MAX_N],B[MAX_N];
int N,M;

LL solve() {
  LL res=2;
  REP(l,32) {
    LL d=1LL<<l;
    unordered_map<LL,LL> S;
    REP(i,N) S[A[i]%(2LL*d)]++;
    REP(j,M) S[(B[j]+d)%(2LL*d)]++;
    FORR(kvp,S) res=max(res,kvp.second);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int _;
  cin>>N>>_;
  REP(i,N) cin>>A[i];
  cin>>M>>_;
  REP(i,M) cin>>B[i];
  cout<<solve()<<endl;
  
  return 0;
}
