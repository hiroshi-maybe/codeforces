
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
 
 6/18/2018
 
 26:15-26:39 1WA
 26:55 ACC (X=0 corner case)
 
 Tweets:
  - https://togetter.com/li/1238701
  - https://twitter.com/satanic0258/status/1008781430355185664
 
 res = 2^K*(2*X-1)+1
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 26:39 1WA
// 26:55 OK (X=0 corner case)
LL X,K;
const LL MOD=1e9+7;
LL powmod(LL a, LL b) {
  assert(0<=a && a<MOD);
  assert(0<=b);
  
  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}

LL solve() {
  if(X==0) return 0;
  LL res=1;
  LL a=powmod(2LL,K);
  LL b=2LL*X%MOD+MOD-1LL;
  b%=MOD;
  res=a*b%MOD;
  res=(res+1LL)%MOD;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>X>>K;
  
  cout<<solve()<<endl;
  
  return 0;
}
