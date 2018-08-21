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
 
 7:48-8:25 AC
 
 Editorial:
  - http://codeforces.com/blog/entry/61311
   - brilliant formula to compute the result
  - http://betrue12.hateblo.jp/entry/2018/08/19/182014
 
 1. adjust order of odd ones so that adjacent cells have the same value like 1,1,2,2,..
 2. value for (x,y) is a=ceil((x-1)*N+y)
 3. a+=ceil(N^2/2) if x+y is odd
 
 Summary:
  - math problem is tough
  - simplify by some adjustment (it's subtraction for odd group in this problem)
  - 1-index may sometimes work better
 
 */

// 8:25 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N,Q;
int X[MAX_N],Y[MAX_N];
void solve() {
  REP(i,Q) {
    int x=X[i],y=Y[i];
    --x,--y;
    swap(x,y);
    int p1=(x+y)%2;
    LL res=(p1==0?0:(1LL*N*N+1)/2);
    res+=(LL)y/2LL*N;
    int yy=y-(((LL)y/2)*2);
//    dump4(y,x,res,yy);
    assert(yy==0||yy==1);
    if(yy==0) {
      res+=(LL)x/2+1;
    } else {
      res+=p1==0?(N+1)/2:N/2;
      res+=x/2+1;
    }
//    dump3(y,x,res);
    cout<<res<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>Q;
  REP(i,Q) cin>>X[i]>>Y[i];
  solve();
  return 0;
}
