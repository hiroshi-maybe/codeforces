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
 
 5/1/2018 R478 div2 C
 
 23:23-24:35 ACC
 
 Solution by @kmjp:
  - http://codeforces.com/contest/975/submission/37804960
 
 If consumed strength is accumulated, we can use built-in binary search.
 
 My solution: searching K[i] in cum[r]-cum[p]
 @kmjp's solution: searching ∑ K[x] in cum[r]-cum[p]
 
 It's beautiful that we just keep accumulating queries.
 
 5/2/2018
 
 22:45-22:58 add simple solution with built-in binary search.
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 24:35 submit
const int MAX_N=200001;
LL A[MAX_N],K[MAX_N];
int N,Q;
LL cum[MAX_N+1];

void solve() {
  cum[0]=0;
  REP(i,N) cum[i+1]=cum[i]+A[i];
  
  LL cur=0;
  REP(i,Q) {
    cur+=K[i];
    if(cur>=cum[N]) {
      cur=0;
      cout<<N<<endl;
    } else {
      int p=lower_bound(cum,cum+N+1,cur)-cum;
      if(cum[p]>cur) --p;
      cout<<N-p<<endl;
    }
  }
}

void solve_org() {
  cum[0]=0;
  REP(i,N) cum[i+1]=cum[i]+A[i];
  
  int p=0; LL rem=A[0];
  REP(i,Q) {
    LL k=K[i]-rem;
    if(k<0) {
      rem-=K[i];
//      dump4(i,'a',p,rem);
      cout<<N-p<<endl;
    } else if(cum[N]-cum[p+1]<=k) {
      p=0; rem=A[0];
//      dump4(i,'b',p,rem);
      cout<<N<<endl;
    } else {
      int ng=p+1,ok=N;
//      dump(k);
      while(abs(ok-ng)>1) {
//        dump2(ng,ok);
        int mid=(ok+ng)/2;
        if(cum[mid]-cum[p+1]>k) ok=mid;
        else ng=mid;
      }
      LL x=(cum[ok]-cum[p+1])-k;
      p=ok-1;
      rem=x;
//      dump4(i,'c',p,rem);
      cout<<N-p<<endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>Q;
  REP(i,N) cin>>A[i];
  REP(i,Q) cin>>K[i];

  solve();
  
  return 0;
}
