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
 
 21:06-21:43 give up (2WA)
 
 10/26/2018
 
 15:40-15:45 figured out overflow bug...
 
 http://codeforces.com/blog/entry/61876
 http://betrue12.hateblo.jp/entry/2018/09/17/015954
 https://twitter.com/satanic0258/status/1041305564997804034
 
 If w/h = X/Y, there exists `k` s.t. w=k*X, h=k*Y
 
 I couldn't figure out it. Thus I did complex binary search and failed due to overflow...
 
 Key:
  - pairs which satisfies some ratio <=> make ratio relatively prime and represent by some constant `k`
  - try to represent pairs with one parameter so that we can count easily to satisfy specific condition. Search is easy too
  - transform formula to a convenient form

 Summary:
  - How to solve it?
   - Could you restate it still differently?
   - Could you change the data?
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
LL A,B,X,Y;

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
LL solve_org() {
  LL g=gcd(X,Y);
  X=X/g,Y=Y/g;
  LL H=B/Y;
  LL good=0,bad=H+1;
  while(abs(good-bad)>1) {
    LL k=(good+bad)/2LL;
    double xk=1.0*X*k;
    if(xk>(double)A) {
      bad=k;
      continue;
    }
    LL xk2=X*k;
    (xk2<=A?good:bad)=k;
  }
  return good;
}

LL solve() {
  LL g=gcd(X,Y);
  X=X/g,Y=Y/g;
  return min(A/X,B/Y);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin>>A>>B>>X>>Y;
  cout<<solve()<<endl;
  
  return 0;
}
