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
 
 9/6/2018
 
 8:41-9:03,10:08-10:25 AC
 
 http://codeforces.com/blog/entry/61692
 
 sum=N*(N+1)/2
 
 If x|sum, gcd(x,sum-x)=x
 
 Such `x` is always found because it's guaranteed that either N/2 or (N+1)/2 is integer.
 Note that result is NO only if `x`<2
 
 */

// 10:25 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int N;
//LL A[MAX_N];
const string yes="Yes",no="No";

void solve() {
  LL sum=1LL*N*(N+1)/2;
  FOR(n,2,N) if(sum%n==0) {
    cout<<yes<<endl;
    cout<<1<<" "<<n<<endl;
    cout<<N-1;
    FORE(m,1,N) if(m!=n) cout<<" "<<m;
    cout<<endl;
    return;
  }
  cout<<no<<endl;
}

void solve_org() {
  if(N<=2) {
    cout<<no<<endl;
    return;
  }
  VI A,B;
  FORE(n,1,N) (n%2==0?A:B).push_back(n);
  cout<<yes<<endl;
  cout<<SZ(A);
  REP(i,SZ(A)) cout<<' '<<A[i];
  cout<<endl;
  cout<<SZ(B);
  REP(i,SZ(B)) cout<<' '<<B[i];
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  solve();
  return 0;
}
