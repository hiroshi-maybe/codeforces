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
 
 11/28/2018
 
 20:00-20:20 pause
 
 11/29/2018
 
 15:10-16:13 WA on test case #4
 17:13 give up and read editorials
 
 17:40 pause
 
 19:45-20:45 analyze editorial
 21:00 implement and got AC
 
 https://codeforces.com/blog/entry/63384
 http://kmjp.hatenablog.jp/entry/2018/11/24/0900
 
 We are interested in min gap between intervals.
 Thus there are two approaches to query
  - query start time for each descendent end time (solution by @kmjp)
  - query end time for each ascendent start time (I took this in my solution)
 
 My mistake was querying start time for each "ascendent" end time, which is NOT optimal.

 *--1--*    *--3--*
   *--2--*
 
 In above case, 3 should be merged with 2 instead of 1.

 Keys:
  - merge if r_i-l_j <= X/Y
  - greedily merge with closest right boundary for each left boundary of intervals
 
 */

// $ ../batch TVShows | diff TVShows.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TVShows.cpp && ./a.out
const int MAX_N=1e5+1;
LL L[MAX_N],R[MAX_N];
int N;
LL X,Y;

const LL MOD=1e9+7;

void solve() {
  int D=X/Y;
//  dump(D);
  vector<III> xs;
  set<III> ys;
  REP(i,N) xs.emplace_back(L[i],R[i],i);
  sort(ALL(xs));
  LL res=0;
  REP(i,N) {
    int l,r,j; tie(l,r,j)=xs[i];
    auto it=ys.upper_bound({-l,2e9,2e9});
    //    dump3(j,l,r);
    if(it!=ys.end()) {
      int rr,ll,jj; tie(rr,ll,jj)=*it;
      //      dump4(ll,rr,jj,ll<=r+D);
      if(l-D<=-rr) {
//        dump2(j,jj);
        //        dump4(l,r,ll,rr);
        ys.erase(it);
        ys.emplace(-r,ll,jj);
        continue;
      }
    }
    ys.emplace(-r,l,j);
  }
  
  FORR(t,ys) {
    int r,l,i; tie(r,l,i)=t;
//    dump3(i,l,-r);
    res=(res+X+(-r-l)*Y%MOD)%MOD;
  }
  cout<<res<<endl;
}

void solve_wrong2() {
  int D=X/Y;
  dump(D);
  vector<III> xs;
  set<III> ys;
  REP(i,N) xs.emplace_back(R[i],L[i],i);
  REP(i,N) ys.emplace(L[i],R[i],i);
  sort(ALL(xs));
  LL res=0;
  REP(i,N) {
    int l,r,j; tie(r,l,j)=xs[i];
    auto it=ys.upper_bound({r,2e9,2e9});
//    dump3(j,l,r);
    if(it!=ys.end()) {
      int ll,rr,jj; tie(ll,rr,jj)=*it;
//      dump4(ll,rr,jj,ll<=r+D);
      if(ll<=r+D) {
        if(i<N-1) {
          int l2,r2,j2; tie(r2,l2,j2)=xs[i+1];
          if(r2<rr) continue;
        }
        dump2(j,jj);
//        dump4(l,r,ll,rr);
        L[jj]=L[j],L[j]=-1; // merge
        ys.erase(it);
        ys.emplace(l,rr,jj);
      }
    }
  }
  
  REP(i,N) if(L[i]!=-1) {
    dump4(i,L[i],R[i],X+(R[i]-L[i])*Y);
    res=(res+X+(R[i]-L[i])*Y%MOD)%MOD;
  }
  cout<<res<<endl;
}

void solve_wrong() {
  map<LL,int> imos;
  LL res=0;
  REP(i,N) {
    LL a=(R[i]-L[i]-1)*Y%MOD;
    (res+=a)%=MOD;
    imos[L[i]]++,imos[R[i]]--;
  }
  int x=0;
  int cur=0;
  FORR(kvp,imos) {
    cur+=kvp.second;
    dump2(kvp.first,cur);
    SMAX(x,cur);
  }
  dump(x);
  res=res+x*X%MOD;
  res%=MOD;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>X>>Y;
  REP(i,N) cin>>L[i]>>R[i];
  solve();
  
  return 0;
}
