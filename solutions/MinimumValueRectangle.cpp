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
 
 8/18/2018
 
 8:26-8:48 AC
 
 Editorials:
  - http://codeforces.com/blog/entry/61311
  - http://betrue12.hateblo.jp/entry/2018/08/19/182014
 
 */

// 8:48 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e6+1;
int N;
LL A[MAX_N];
void solve() {
  MAPII M;
  REP(i,N) M[A[i]]++;
  VI X;
  FORR(kvp,M) REP(i,kvp.second/2) X.push_back(kvp.first);
  sort(X.begin(),X.end());
  double minx=1e10;
  II res={-1,-1};
  int NN=SZ(X);
  REP(i,NN-1) {
    int a=X[i],b=X[i+1];
    double x=(1.0*a+b)*(1.0*a+b)/(1.0*a*b);
    if(x<minx) res={a,b},minx=x;
  }
  assert(res.first!=-1);
  cout<<res.first<<' '<<res.first<<' '<<res.second<<' '<<res.second<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int T; cin>>T;
  REP(i,T) {
    cin>>N;
    REP(i,N) cin>>A[i];
    solve();
  }
  return 0;
}
