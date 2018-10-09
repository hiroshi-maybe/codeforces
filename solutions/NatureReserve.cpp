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
 
 10/5/2018
 
 22:16-22:35 analysis
 23:20 bugfix of maximal radius
 23:21 precision error
 23:35 TLE. give up.
 
 O(lg A*lg A*N) does not beat TL. I should have switched my approach right away 😡
 
 10/8/2018
 
 22:00-23:05 AC (wasted time because I was not calling revised function g())
 
 http://codeforces.com/blog/entry/62238
 http://codeforces.com/contest/1059/standings by @kmjp
  - binary search

 If `r` is determined, range of possible center of circle is determined.

     (x-a)^2+(y-r)^2<=r^2 (`a` is the center of x)
 <=> x-sqrt(2yr-y^2) <= a <= x+sqrt(2yr-y^2)
 
 If this interval is not empty, `r` is valid.
 
 http://codeforces.com/contest/1059/submission/43855968
  - ternary search by @nuip
 
 Summary:
  - I was aware of convergence property which is necessary for ternary search. However I made a mistake in runtime analysis 😡
  - Also wasted time to revise my function 😡😡
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
double X[MAX_N],Y[MAX_N];
int N;
const long double EPS=1e-7;

bool chk(long double x, long double r) {
  bool ok=true;
  REP(i,N) {
    long double xx=(long double)X[i]-x,yy=(long double)Y[i]-r;
    long double a=xx*xx+yy*yy,b=r*r;
//    dump3(i,X[i],Y[i]);
//    dump4(x,r,a,b);
    ok&=(b-(a-EPS)>=0);
  }
  return ok;
}
long double f_tle(long double x) {
  long double good=1e20,bad=0;
  REP(_,100) {
    long double r=(good+bad)/2.0;
//    dump2(r,chk(x,r));
    (chk(x,r)?good:bad)=r;
  }
  return good;
}
long double solve_tle() {
  bool p=false,n=false;
  REP(i,N) p|=Y[i]>0,n|=Y[i]<0;
  if(p&&n) return -1;
  REP(i,N) Y[i]=abs(Y[i]);
  
  long double l=-1e7,r=1e7;
  REP(_,50) {
    long double ll=l+(r-l)/3.0,rr=r-(r-l)/3.0;
    long double a=f_tle(ll),b=f_tle(rr);
//    dump4(ll,rr,a,b);
    if(a>b) l=ll;
    else r=rr;
  }
//  dump2(l,r);
  long double a=f_tle(l),b=f_tle(r);
  return (a+b)*0.5;
}

double T1[MAX_N],T2[MAX_N],T3[MAX_N];
double g(double x) {
  double res=0;
  REP(i,N) {
    double xx=(double)X[i]-x;
    double r=(xx*xx+Y[i]*Y[i])/(2*Y[i]);
    //double r=T1[i]+x*(x*T2[i]+T3[i]);
    SMAX(res,r);
  }
  return res;
}

double solve() {
  bool p=false,n=false;
  REP(i,N) p|=Y[i]>0,n|=Y[i]<0;
  if(p&&n) return -1;
  REP(i,N) Y[i]=abs(Y[i]);
  
  /*
  vector<pair<LL,LL>> ps(N);
  REP(i,N) ps[i].first=X[i],ps[i].second=Y[i];
  srand(ps[12345%N].first);
  random_shuffle(ps.begin(),ps.end());
  
  REP(i,N) {
    T1[i]=(X[i]*X[i]+Y[i]*Y[i])/(2*Y[i]);
    T2[i]=1/(2*Y[i]);
    T3[i]=-X[i]/Y[i];
  }*/
  
  double l=-1e7,r=1e7;
  REP(_,100) {
    double ll=(l+l+r)/3.0,rr=(l+r+r)/3.0;
    double a=g(ll),b=g(rr);
    if(a>b) l=ll;
    else r=rr;
  }
  //  dump2(l,r);
  double a=g(l),b=g(r);
  return (a+b)*0.5;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>X[i]>>Y[i];
  cout<<setprecision(20)<<fixed<<solve()<<endl;
  
  return 0;
}
