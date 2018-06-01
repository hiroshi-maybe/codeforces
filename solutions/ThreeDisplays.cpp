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
 
 5/29/2018 R485 div2 C
 
 25:00-25:12 submit
 
 Editorials:
  - https://codeforces.com/blog/entry/59758
   - O(1) space solution
   - http://codeforces.com/contest/987/submission/38826188
 
 Tweets:
  - https://togetter.com/li/1232170
  - https://twitter.com/_TTJR_/status/1001520890360676352
  - https://twitter.com/tempura_pp/status/1001527223382233088

 Solution of official editorial is impressive.
 If `i` is pinned, we still need to search `j` on which `k` is independent.
 However if `j` is pinned, `i` and `k` are mutually independent.
 
 */

// 25:00-25:12 submit
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3005;
int S[MAX_N],C[MAX_N];
int N;

const int Inf=1e9;
int solve() {
  VI X(N,-1);
  REP(i,N)FOR(j,i+1,N) if(S[j]>S[i]&&(X[i]==-1||C[X[i]]>C[j])) X[i]=j;
  int res=Inf;
  REP(i,N)FOR(j,i+1,N) if(S[i]<S[j]&&X[j]!=-1) SMIN(res,C[i]+C[j]+C[X[j]]);
  return res==Inf?-1:res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>S[i];
  REP(i,N) cin>>C[i];

  cout<<solve()<<endl;
  
  return 0;
}
