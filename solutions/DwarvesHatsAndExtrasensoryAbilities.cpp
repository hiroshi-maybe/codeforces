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
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline bool SMIN(T &l,const T &r){return l<r?l=r,1:0;}
template<class T> inline bool SMAX(T &l,const T &r){return l>r?l=r,1:0;}
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
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 10/15/2018
 
 16:50-17:30 I'm totally confused about the problem statement..
 19:55-21:05 read togetter comments and understand problem concept. Got AC (1WA)
 
 https://codeforces.com/blog/entry/62455
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
int N;

int ask(int x, int y) {
  cout<<x<<" "<<y<<endl;
  string s; cin>>s;
  return s[0]=='b';
}

void solve() {
  int n=0;
  LL l=0,r=1e9+1;
  LL mid=(l+r)/2;
  int c0=ask(mid,0); ++n;
  l=mid;
  while(abs(r-l)>5&&n<N) {
    LL mid=(l+r)/2;
    int c=ask(mid,0);
    (c==c0?l:r)=mid;
    ++n;
  }
  
  int x0=l+1,y0=0,x1=l;
  l=0,r=1e9+1;
  while(n<N) {
    LL mid=(l+r)/2;
    int c=ask(x1,mid);
    (c==c0?l:r)=mid;
    ++n;
  }
  assert(abs(r-l)>2);
  int y1=l+1;
  cout<<x0<<" "<<y0<<" "<<x1<<" "<<y1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  solve();
  
  return 0;
}
