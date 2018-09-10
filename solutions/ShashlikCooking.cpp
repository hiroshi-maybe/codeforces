#include <iostream>
#include <iomanip>
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
 
 9/5/2018
 
 9:45-10:17 RE
 10:23 passed
 
 http://codeforces.com/blog/entry/61668
 http://codeforces.com/contest/1040/submission/42503781
 http://codeforces.com/contest/1040/submission/42503118
 http://codeforces.com/contest/1040/submission/42502589 (brute-force)
 
 
 It's crucial to prove that first segment is either 2*K+1 (N is multiple of 2*K+1) or K+1 (otherwise).
 Adjusting in output would have been easier.
 
 I'm wondering how I can solve this kind of problem faster.
 1. There should be some simple and sufficient method
  - In this problem, there is solution with linear construction
 2. Find and show sufficiency fast
  - Length of segments of both ends could be <2*K+1
  - First segment K+1 covers most of cases
  - Once length of first segment is determined, succeeding can be determined too
 
 */

// 9:45-10:17 RE
// 10:23 passed
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int N,K;
//LL A[MAX_N];
void solve() {
  if(N<=K) {
    cout<<1<<endl;
    cout<<1<<endl;
    return;
  }
  int rem=N%(2*K+1);
  dump(rem);
  VI res;
  if(rem==0||rem>=K+1) {
    int l=1,r=2*K+1;
    while(r<=N) {
      res.push_back((l+r)/2);
      l+=2*K+1,r+=2*K+1;
    }
    if(l<=N) {
      assert(N-l+1>=K+1);
      res.push_back(l+K);
    }
  } else {
    int l=K+2,r=3*K+3;
    res.push_back(1);
    while(r<=N) {
//      dump2(l,r);
      res.push_back((l+r)/2);
      l+=2*K+1,r+=2*K+1;
    }
//    dump2(l,r);
    assert(K+1<=N+1-l&&N+1-l<=2*K);
    res.push_back(l+K);
  }
  cout<<SZ(res)<<endl;
  REP(i,SZ(res)) cout<<res[i]<<(i==SZ(res)-1?'\n':' ');
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  solve();
  return 0;
}
