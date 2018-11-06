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
 
 11/4/2018
 
 16:30-17:50 analysis
 19:30-20:20 got WA on test case #3 and give up
 
 f(N) is just computation. I tried to compute min delta s.t. f(k-1) = f(k) - delta.
 I classified to three cases how perimeter decreases.
 However it did not have optimality...
 
 my note:
  - greedy or dp?
  - formula transformation?
 
 11/5/2018
 
 21:50-22:50 read editorial and got AC
 
 http://codeforces.com/blog/entry/62985
 
 Perimeter of manhattan distance of a convex polygon <=> Perimeter of the bounding rectangle
 
 Hmmm considering bounding rectangle for manhattan distance is typical? Anyway I'll remember it.
 Or pay attention to x-axis and y-axis for manhattan distance because it's projection to those axis.
 
 Summary:
  - Manhattan distance <=> Projection to x-axis and y-axis
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3e5+1;
LL xs[MAX_N],ys[MAX_N];
int N;

void solve() {
  const LL Inf=1e9;
  LL x1=Inf,x2=-Inf,y1=Inf,y2=-Inf;
  REP(i,N) {
    LL x=xs[i],y=ys[i];
    SMIN(x1,x),SMIN(y1,y),SMAX(x2,x),SMAX(y2,y);
  }
  LL res2=2LL*((x2-x1)+(y2-y1));
  
  LL res=0;
  int i1=-1,i2=-1,j1=-1,j2=-1;
  REP(i,N) {
    LL x=xs[i],y=ys[i];
    if(x==x1) i1=i;
    if(y==y1) j1=i;
    if(x==x2) i2=i;
    if(y==y2) j2=i;
  }
  int A[4]={i1,i2,j1,j2};
  REP(j,4)REP(i,j) REP(k,N) {
    LL x1=Inf,x2=-Inf,y1=Inf,y2=-Inf;
    for(int l : {A[i],A[j],k}) {
      LL x=xs[l],y=ys[l];
      SMIN(x1,x),SMIN(y1,y),SMAX(x2,x),SMAX(y2,y);
    }
    SMAX(res,2LL*((x2-x1)+(y2-y1)));
  }
  printf("%lld ",res);
  REP(_,N-3) printf("%lld ",res2);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  scanf("%d",&N);
  REP(i,N) scanf("%lld %lld",&xs[i],&ys[i]);
  
  solve();
  
  return 0;
}

LL X[MAX_N][2],D[MAX_N];
int L[MAX_N],R[MAX_N];

void solve_wrong() {
  LL cur=0;
  set<pair<LL,int>> Q;
  
  auto link=[&](int l, int i, int r) {
    L[i]=l,R[i]=r;
    
    LL dd=0;
    REP(j,2) {
      LL d;
      if(X[l][j]<=X[i][j]&&X[i][j]<=X[r][j]) d=0;
      else if(X[r][j]<=X[i][j]&&X[i][j]<=X[l][j]) d=0;
      else d=min(abs(X[r][j]-X[i][j]),abs(X[l][j]-X[i][j]));
      dd+=d;
    }
    dump4(l,i,r,dd);
    auto it=Q.find({D[i],i});
    if(it!=Q.end()) Q.erase(it);
    Q.emplace(dd,i),D[i]=dd;
  };
  REP(i,N) {
    int l=(N+i-1)%N;
    int r=(i+1)%N;
    L[i]=l,R[i]=r;
    link(l,i,r);
    REP(j,2) cur+=abs(X[i][j]-X[l][j]);
//    if(i==N-1)REP(j,2) cur+=abs(X[i][j]-X[r][j]);
  }
  vector<LL> res;
  REP(_,N-2) {
    res.push_back(cur);
    auto it=Q.begin();
    LL d; int remi;
    tie(d,remi)=*it;
    Q.erase(it);
    
    dump4(remi,d,d*2,cur);
    
    cur-=2LL*d;
    int l=L[remi],r=R[remi];
    link(L[l],l,r);
    link(l,r,R[r]);
    Q.erase({d,remi});
  }
  reverse(ALL(res));
  REP(i,SZ(res)) printf("%lld ",res[i]);
  println("");
}

int main_wrong() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  scanf("%d",&N);
  REP(i,N) scanf("%lld %lld",&X[i][0],&X[i][1]);
  
  solve();
  
  return 0;
}
