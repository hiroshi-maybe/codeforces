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
 
 10/25/2018
 
 22:17-23:07 AC (RE due to array boundary bug)
 
 http://codeforces.com/blog/entry/61876
 http://betrue12.hateblo.jp/entry/2018/09/17/015954
 https://twitter.com/satanic0258/status/1041305564997804034
 
 */

// 23:07 AC (1WA)
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
LL X1[MAX_N],X2[MAX_N];
int N;
LL H;

LL D[MAX_N];
vector<LL> cum;

int f(int i) {
  int good=i,bad=N;
  while(abs(good-bad)>1) {
    int mid=(good+bad)/2;
    LL d=cum[mid]-cum[i];
    (H-d>0?good:bad)=mid;
  }
  return good;
}

//const LL Inf=1e18;
LL solve() {
  cum=vector<LL>(N,0);
  REP(i,N-1) cum[i+1]=cum[i]+X1[i+1]-X2[i];
  
  LL res=0;
  REP(i,N) {
    int j=f(i);
    LL d=H-(cum[j]-cum[i]);
    assert(d>=0);
    LL x=X2[j]+d;
//    dump4(i,j,d,x);
    res=max(res,x-X1[i]);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>H;
  REP(i,N) cin>>X1[i]>>X2[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
