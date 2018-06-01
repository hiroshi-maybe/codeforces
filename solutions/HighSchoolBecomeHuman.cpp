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
 
 5/29/2018
 
 24:40-25:00, 26:00-26:14 ACC
 
 Editorials:
  - https://codeforces.com/blog/entry/59758
 
 Tweets:
  - https://togetter.com/li/1232170
  - https://twitter.com/_TTJR_/status/1001520890360676352
  - https://twitter.com/tempura_pp/status/1001527223382233088
 
 Summary:
  - I didn't want to depend on double
  - I did experiment and figured out that some special cases show up around x=2. Otherwise x>y => y^x > x^y
 
 */

//
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
int x,y;
char solve() {
  if(x==y) return '=';
  if(x==1) return '<';
  if(y==1) return '>';
  if(x==2&&y==4) return '=';
  if(x==4&&y==2) return '=';
  if(x==2&&y==3) return '<';
  if(x==3&&y==2) return '>';
  return x>y?'<':'>';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>x>>y;
  
  cout<<solve()<<endl;
  
  return 0;
}
