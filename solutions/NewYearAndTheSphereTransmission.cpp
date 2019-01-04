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

// $ ../batch NewYearAndTheSphereTransmission | diff NewYearAndTheSphereTransmission.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NewYearAndTheSphereTransmission.cpp && ./a.out

/*
 
 12/30/2018
 
 07:07-7:55 AC
 
 https://codeforces.com/blog/entry/64196
 
 I didn't have clear proof during the contest 😞
 
 a*x (mod b) forms group g*Z/Z_{g/b} where g=gcd(a,b)
 
 Thus we can enumerate all `g` by trial division.
 
 */

int N;

set<LL> res;
void f_org(int x) {
  if(x!=N)x=min(x,N-x);
//  dump(x);
  assert(x!=0);
  LL y=N/x;
  LL a=y,b=x,c=y*(y-1)/2;
  res.emplace(a+b*c);
}

void f(LL g) {
  LL x=N/g;
  res.emplace(x+g*x*(x-1)/2);
}

void solve() {
  res.clear();
  for(LL p=1; p*p<=N; ++p) if(N%p==0) {
    f(p);
    if(p!=N/p) f(N/p);
  }
}

void test() {
  FOR(n,2,10000) {
    set<LL> S;
    FORE(k,1,n) {
      int x=0;
      LL sum=1;
      while((x+k)%n!=0) x=(x+k)%n,sum+=x+1;
      S.emplace(sum);
    }
    N=n;
    solve();
    if(res!=S) {
      dump(n);
      dumpAR(S);
      dumpAR(res);
    }
    assert(res==S);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>N;
  solve();
  FORR(x,res) printf("%lld ",x);
  println("");
  
  return 0;
}
