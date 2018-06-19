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
 
 25:40-25:59 1WA
 26:06 3WA
 26:15 AC
 
 Tweets:
  - https://togetter.com/li/1238701
  - https://twitter.com/satanic0258/status/1008781430355185664
 
 a=p*X, b=q*X where gcd(p,q)=1
 
     a*b/X = Y
 <=> p*q*X = Y
 <=> p*q = Y/X
 
 Summary:
  - gcd, lcm check was necessary..
  - It turns out that Y%X != 0 in some inputs 😡
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
//int A[MAX_N];
//int N;
int L,R,X,Y;

// 25:59 1WA
// 26:06 3WA
// 26:15 OK
LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
LL lcm(LL a, LL b) { return a*b/gcd(a,b); }
bool ok(LL a) { return L<=a&&a<=R; }
LL solve() {
  LL res=0;
  if(Y%X!=0) return 0;
  LL A=Y/X;
  for(LL p=1; p*p<=A; ++p) if(A%p==0) {
    LL q=A/p;
    LL a=p*X,b=q*X;
    if(!ok(a)) continue;
    if(!ok(b)) continue;
    if(gcd(p,q)!=1) continue;
//    if(gcd(a,b)!=X) continue;
//    if(lcm(a,b)!=Y) continue;
  
//    dump4(a,b,gcd(a,b),lcm(a,b));
    
    if(a==b) res+=1;
    else res+=2;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>L>>R>>X>>Y;
  cout<<solve()<<endl;
  
  return 0;
}
