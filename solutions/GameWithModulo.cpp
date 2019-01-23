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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

// $ cp-batch GameWithModulo | diff GameWithModulo.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GameWithModulo.cpp && ./a.out

/*
 
 1/22/2019
 
 7:23-8:44 give up
 
 1/23/2019
 
 14:00-15:36 read editorial and got AC

 x (mod A) forms cycle.
 
  / / / /
 / / / / ....
 -----------------> x
  ^A
 
 We are interested in `A`. Thus let's try to find end of first cycle.
 Max # of query is 2*log max A. Thus exploring a method to binary searching `A` by the given query is the choice.
 
 We are exploring `A` by range of (2^k,2^(k+1)].
 
 1) x<y (mod A)
 
    /
   /
  /
 /
 ^x ^y
 
 We've not still caught up the end of cycle.
 
 2) x>=y (mod A)
 
   /  /
  /  /
 /  /
  ^x ^y
 
 Suppose x=2^k, y=2^(k+1).
 At this moment, we know that 2^k < A. At the same time, y-x=2^k.
 Thus if we found end of the cycle, x>=y (mod A) holds (equality holds only when A=1).
 
 Once we found the range, we can do binary search again to find min `y` which holds x>=y (mod A)
 
 Summary:
  - We need to specify two values. I had no idea to start from what... 😞
   - What to search is important. Finding first end of cycle is critical first step.
  - I didn't have an idea to binary search "range" of unknown
   - Searching by range (2^k,2^(k+1)) should be useful if binary search is preferred in terms of constraint
 
 */

void start() {
  string s; cin>>s;
  if(s!="start") {
    assert(s=="end");
    exit(0);
  }
}

LL AA=101;
bool ask(LL x, LL y) {
//  if(TRACE) {
//    return (x%AA)>=(y%AA);
//  }
  cout<<"? "<<x<<" "<<y<<endl;
  string s; cin>>s;
  if(s=="e") {
    assert(false);
    exit(0);
  }
  return s=="x";
}
void answer(LL A) {
  cout<<"! "<<A<<endl;
  start();
}
void solve() {
  start();
  while(true) {
    LL x=0,y=1;
    while(!ask(x,y)) {
      x=y,y*=2;
    }
    int l=x,r=y;
    while(abs(r-l)>1) {
      LL m=(l+r)/2;
      bool a=ask(x,m);
//      dump3(l,r,a);
      (a?r:l)=m;
    }
    //    LL a1=r+1;
    answer(r);
  }
}

LL go(LL len) {
  LL l=0,r=len;
  while(abs(r-l)>1) {
    dump4(l,r,l%AA,r%AA);
    if(ask(l,r)) return r-l; else {
      l=(l+r)/2LL;
    }
  }
  return -1;
}

void solve_wrong() {
  while(true) {
    start();
//    int cnt=0;
    LL l=0,r=1e9+1;
    while(abs(r-l)>1) {
      int mid=(l+r)/2;
      int len2=go(mid);
      if(len2<0) l=mid;
      else r=mid;
    }
//    LL a1=r+1;
    answer(l);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  solve();
  
  return 0;
}
