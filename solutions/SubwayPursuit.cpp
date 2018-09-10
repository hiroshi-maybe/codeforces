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
#include <time.h>
#include <chrono>
#include <random>
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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*

 9/5/2018
 
 10:25-11:01 give up
 13:25-14:18 got AC by referring to below code
 http://codeforces.com/blog/entry/61668

 I figured out tons of implementation mistakes (15WA)
  - overflow
  - bug in binary search
  - random seed `mt19937` is better than `rand()`
 
 http://codeforces.com/contest/1040/submission/42525721
 https://codeforces.com/blog/entry/61587
 https://codeforces.com/blog/entry/61675
 
 */

// overflow, unexpectedly found result in binary search
// 10:25-11:01 give up
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const string bad="Bad",yes="Yes",no="No";
LL N;
int K;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
bool guess(LL l, LL r) {
  cout << l << " " << r << endl;
  string s; cin >> s;
  if (s == bad) assert(0);
  if (l == r && s == yes) exit(0);
  return s==yes;
}

void solve() {
  LL l=1,r=N;
  while(true) {
    if(r-l<=4*K) {
      LL delta = rnd()%(r-l+1);
      LL T=l+delta;
      guess(T,T);
      l=max(l-K,1LL);
      r=min(r+K,N);
    } else {
      LL mid=(l+r)/2;
      if(guess(l,mid)) {
        l=max(l-K,1LL);
        r=min(mid+K,N);
      } else {
        l=max(mid+1-K,1LL);
        r=min(r+K,N);
      }
    }
  }
}

void show(LL l, LL r) {
  dump3(l,r,r-l+1);
  cout<<l<<" "<<r<<endl; cout.flush();
}

void solve_org() {
//  srand(time(NULL));
  
  LL l=1,r=N;
  while(true) {
    LL mid=(l+r)/2;
    show(l,mid);
    string s; cin>>s;
    if(s==bad) exit(0);
    if(s==yes) {
      
      if(l==mid) exit(0);
      
      l=max(l-K,1LL);
      r=min(mid+K,N);
    } else {
//      l=max(mid-K,1LL);
      l=max(mid+1-K,1LL);
      r=min(r+K,N);
    }
//    dump3(r-l+1,4*K+1,r-l+1<=4*K+1);
    if(r-l+1<=4*K+1) {
//      srand (time(NULL));
      LL delta = rnd()%(r-l+1);
//      LL delta = rand()%(r-l+1);
//      dump3(l,r,delta);
      LL T=l+delta;
      show(T,T);
      string s; cin>>s;
      if(s==yes||s==bad) exit(0);
      l=max(l-K,1LL);
      r=min(r+K,N);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  solve();
  return 0;
}
