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

/*
 
 11/19/2018
 
 12:58-14:09 WA
 14:30 give up
 
 https://codeforces.com/blog/entry/63324
 
 11/27/2018
 
 13:10-15:30 read editorial and understand correctness of it.
 15:31-15:46 implement and got AC
 
 Detour cannot be optimal.
 
 1) short cut
     __B
 A__/
 
 2) detour
    __B
 A__\
 
 Due to triangle inequality, case #2 cannot be optimal. Manhattan distance always beat it.
 
   |\
 b | \
   |  \ c
   |___\
     a
 
 a+c>b shows it.
 
 It's possible to classify based on above observation.
 However, applying shortest path algorithm is simpler.
 If we go through the line, the access point always crosses bounding box of the start and end points. There exists at most 4 points. Thus Floyd-Warshall works.
 
 Summary:
  - if system test does not pass due to precision error, it's likely to be unexpected algorithm
  - I was looking at how to approach the diagonal line. However we can simplify solution by showing that manhattan distance is optimal in most of cases.
  - Before analyzing complex cases, try to figure out how we can skip them by simple case (Just Manhatan distance in this problem)
 
 */

// $ ../batch BarcelonianDistance | diff BarcelonianDistance.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BarcelonianDistance.cpp && ./a.out
LL X1,X2,Y1,Y2;
LL A,B,C;

double xtoy(double x) {
  return 1.0*(-A*x-C)/(double)B;
}
double ytox(double y) {
  return 1.0*(-B*y-C)/(double)A;
}

void solve() {
  VV<double> mx(6, vector<double>(6, 1e18));
  double xs[6]={(double)X1,(double)X2,      (double)X1,ytox((double)Y1),      (double)X2,ytox((double)Y2)};
  double ys[6]={(double)Y1,(double)Y2,xtoy((double)X1),      (double)Y1,xtoy((double)X2),      (double)Y2};
  REP(i,6)mx[i][i]=0;
  REP(i,6)REP(j,6) if(i<2||j<2) mx[i][j]=mx[j][i]=abs(xs[i]-xs[j])+abs(ys[i]-ys[j]);
  REP(i,6)REP(j,6) if(i>=2&&j>=2) mx[i][j]=mx[j][i]=hypot((xs[i]-xs[j]),abs(ys[i]-ys[j]));
  
  REP(k,6)REP(i,6)REP(j,6)SMIN(mx[i][j],mx[i][k]+mx[k][j]);
  cout<<mx[0][1]<<endl;
}

double calc2(double x, double y, double cx, double cy) {
  return abs(X2-x)+abs(y-Y2)+hypot(x-cx,y-cy);
}
double h(double cx, double cy, double x) {
  double y=xtoy(x);
  double a=calc2(x,y,cx,cy);
  double y1=floor(y),x1=ytox(y1);
  double b=calc2(x1,y1,cx,cy);
  double y2=floor(y)+1.0,x2=ytox(y2);
  double c=calc2(x2,y2,cx,cy);
  return min({a,b,c});
}

double g(double x, double y) {
  LL l=-1e9,r=1e9+1;
  while(abs(r-l)>2) {
    LL l2=l+(r-l)/3,r2=r-(r-l)/3;
    LL a=h(x,y,l2),b=h(x,y,r2);
    if(a<b) r=r2;
    else l=l2;
  }
  double res=1e18;
  SMIN(res,h(x,y,l));
  SMIN(res,h(x,y,l+1));
  return res;
}
double calc1(double x, double y) {
  return g(x,y)+abs(X1-x)+abs(y-Y1);
}
double f(LL x) {
  double y=xtoy(x);
  double a=calc1(x,y);
  double y1=floor(y),x1=ytox(y1);
  double b=calc1(x1,y1);
  double y2=floor(y)+1.0,x2=ytox(y2);
  double c=calc1(x2,y2);
  return min({a,b,c});
}

void solve_wrong() {
  double res=abs(X1-X2)+abs(Y1-Y2);
  LL l=-1e9,r=1e9+1;
  while(abs(r-l)>2) {
    LL l2=l+(r-l)/3,r2=r-(r-l)/3;
    LL a=f(l2),b=f(r2);
    if(a<b) r=r2;
    else l=l2;
  }
  SMIN(res,f(l));
  SMIN(res,f(l+1));
//  SMIN(res,f(l+2));
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cout<<setprecision(10)<<fixed;
  
  cin>>A>>B>>C>>X1>>Y1>>X2>>Y2;
  solve();
  
  return 0;
}
