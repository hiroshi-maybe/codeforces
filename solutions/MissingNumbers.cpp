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

// $ ../batch MissingNumbers | diff MissingNumbers.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MissingNumbers.cpp && ./a.out

/*
 
 1/7/2019
 
 11:20-12:04 WA on test #4
 12:20 give up. I guess implementation mistake?
 13:11 TLE. fuck.
 
 16:00-17:45, 19:00-20:00, 22:00-22:30 read editorials. It took tons of time to understand optimality of smaller A[i]..
 22:30-23:00 I proved greedy optimality and got AC
 
 https://codeforces.com/blog/entry/63888
 https://betrue12.hateblo.jp/entry/2018/12/17/213944
 http://kmjp.hatenablog.jp/entry/2018/12/21/0930
 
 Some observations are needed
  - A[i]^2 is upper-bounded by 1e5
  - smaller `A[i]` is better

 Hmmm I cannot understand why smaller A[i] is optimal...
 22:30 Now I got it.
 
 Proof of greedy choice:
 
 a^2 +X[2k] => b^2 +X[2k+1] => c^2 +X[2k+2] => d^2 (a < b < c < d)

 Now we have b^2. We want to find X[2k+1] s.t. b^2+X[2k+1]=c^2 AND c^x+X[2k+2]=d^2
 We must search two perfect squares `c^2` and `d^2` s.t. c<d.
 Those are some points in sequence of perfect squares {1^2, 2^2, 3^2, .., c^2, .., d^2, .. }
 
 Suppose we have a1,a2,b1,b2 (a1<a2,b1<b2) where a1^2+X[2k]=b1^2 and a2^2+X[2k]=b2^2.
 We want to find (c,d) s.t. b^2+X[2k+1]=c^2 AND c^x+X[2k+2]=d^2
 We are searching c and d in perfect square sequences.
 
 If b1<c<b2, b2 cannot be optimal.
 {1^2, 2^2, ... b1^2, ..., c^2, ..., b2^2, ... }
                ^          ^         ^
 
 If b1<b2<c, b1 and b2 can be chosen.
 {1^2, 2^2, ... b1^2, ..., b2^2, ..., c^2, ... }
                ^          ^          ^

 Thus choosing b1 (smaller index) is always optimal.
 If we choose smaller `b`^2, we have more choices of `c`^2 and `d`^2.
 
 I didn't have clear view to go through linear sequence of perfect square.
 Thus I doubted that smaller one may not catch up c^2 and d^2.
 However that's wrong. condition that we should satisfy is b<c<d.
 If larger `b` finds (c,d), smaller `b` should find it too.
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

LL isqrt(LL x) {
  assert(x>0);
  LL y=(LL)(sqrtl((long double) x)+0.5);
  while(y*y<x) ++y;
  while(y*y>x) --y;
  if(y*y==x) return y;
  return -1;
}

void nope() {
  println("No");
  exit(0);
}
void solve_tle() {
  vector<LL> res;
  LL sq=0,sum=0;
  REP(i,N/2) {
    LL xe=A[i];
    LL a=-1,b=-1;
    for(LL p=1; p*p<=xe; ++p) if(xe%p==0) {
      if((xe/p+p)%2!=0) continue;
      LL bb=(xe/p+p)/2,aa=bb-p;
      if(aa<=0) continue;
      if(aa*aa-sq<=0) continue;
      a=aa,b=bb;
      dump2(p,xe/p);
      break;
    }
    if(a==-1||b==-1) nope();
    LL xo=a*a-sq;
    dump4(i,a,b,xo);
    assert(xo>=1);
    sum+=xo;
    assert(sum==a*a);
    res.push_back(xo);
    sq=b*b;
    sum+=xe;
    assert(sum==b*b);
  }
  println("Yes");
  REP(i,N/2) {
    printf("%lld %lld ",res[i],A[i]);
  }
  println("");
}

void solve() {
  vector<LL> ps;
  REP(n,MAX_N) ps.push_back(1LL*n*n);

  vector<LL> res(N/2);
  int b=0;
  REP(i,N/2) {
    LL xe=A[i];
    int c=b+1,d=c+1;
    while(c<MAX_N) {
      while(d<MAX_N&&ps[d]-ps[c]<xe) ++d;
      if(d>=MAX_N) nope();
      if(ps[d]-ps[c]==xe) break;
      ++c;
    }
    LL xo=ps[c]-ps[b];
    res[i]=xo;
    b=d;
  }
  println("Yes");
  REP(i,N/2) {
    printf("%lld %lld ",res[i],A[i]);
  }
  println("");
}

void exp() {
  map<int,vector<II>> dif;
  FORE(n,1,1000)FORE(m,n+1,1000) {
    int d=m*m-n*n;
    dif[d].emplace_back(n,m);
  }
  FORR(kvp,dif) if(kvp.first<100) {
    dump(kvp.first);
    FORR(p,kvp.second) printf("(%d,%d)",p.first,p.second);
    println("");
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  exp();
  
  cin>>N;
  REP(i,N/2) cin>>A[i];
  solve();
  
  return 0;
}
