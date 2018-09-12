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
 
 9/7/2018
 
 7:53-9:11 AC
 
 http://codeforces.com/blog/entry/61727
 http://betrue12.hateblo.jp/entry/2018/09/08/101540
 https://www.hamayanhamayan.com/entry/2018/09/08/184008
 
 It took tons of time to notice that straight can be replaced with some of diagonal moves.
 -- can be replaced with /\
 
 Look at parity of K and (X,Y).
 
 Every time diagonal move happens, parity of (x,y) matches parity of K.
 
 K      0  ->    1  ->    2
 Pos (0,0) -> (1,1) -> (2,0)
 
 Thus if Parity of (X,Y) is equal to K respectively, K jump can reach (X,Y).
 Otherwise, we need to consume horizontal or vertical move to adjust parities.
 
 Key:
  - prove that (X,Y) is reachable if X<=K and Y<=K
  - prove that Parity of X(Y) is equal to K <=> K diagonal move is possible
 
 Summary:
  - Try to find invariant for operation if math or greedy property is needed
   - Parity or modular group is typical one
 
 */

// 9:11 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
int N;

LL solve(LL X, LL Y, LL K) {
  if(X>Y) swap(X,Y);
  // X<=Y
  if(K<Y) return -1;
  LL res=K;
  if(K%2!=X%2) --res;
  if(K%2!=Y%2) --res;
  return res;
}

LL solve_org(LL X, LL Y, LL K) {
  if((K+X)%2!=0) K-=1,Y-=1;
  if((K+Y)%2!=0) K-=1,X-=1;
  assert((K+X)%2==0&&(K+Y)%2==0);
  LL a=(K+X)/2,b=(K+Y)/2;
  if(a>K||b>K) return -1;
  return K;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) {
    LL X,Y,K; cin>>X>>Y>>K;
    cout<<solve(X,Y,K)<<endl;
  }
  return 0;
}
