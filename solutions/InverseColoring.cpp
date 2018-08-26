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
 
 9:19-9:35 time is up
 
 8/26/2018
 
 13:36-15:20 read editorials and add solution
 
 Editorials:
  - http://codeforces.com/blog/entry/61311
  - http://betrue12.hateblo.jp/entry/2018/08/19/182014
 
 Under the constraint of rectangle, we want to know number of rectangle whose max area of same colors < K.
 That is equivalent to rectangle whose multiplication of max length of same color segment in both direction <K.

 11000011
 00111100
 00111100
 00111100
 11000011
 11000011
 00111100
 00111100
 
 - horizontal max = 4
 - vertical max = 3
 => max area = 12
 
 The constraint of "beautiful" rectangle is strong.
 Once pattern in first row is determined, row pattern is only at most two.
 
 Such patterns can be counted independently regardless of horizontal or vertical side by dp in O(N^3) time.
 
 Summary:
  - I couldn't even understand problem statement of "beautiful"
 - I needed to remove unnecessary modular arithmetic to avoid TLE :(
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out

const LL MOD=998244353;

void add(LL &a, LL b){
  a += b;
  if (a >= MOD)
    a -= MOD;
}

LL powmod(LL a, LL b) {
  assert(0<=a && a<MOD);
  assert(0<=b);
  
  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}
LL modinv(LL a, LL p=MOD) {
  return powmod(a, p-2);
}

const int MAX_N=500+5;
int N,K;
LL dp[MAX_N][MAX_N];
LL cnt[MAX_N];
LL cum[MAX_N];
void solve() {
  ZERO(dp); dp[0][0]=1;
  REP(i,N){
    LL dp2[MAX_N][MAX_N]; ZERO(dp2);
    REPE(j,N)REPE(k,N) {
      add(dp2[j+1][max(j+1,k)],dp[j][k]);
      add(dp2[1][max(1,k)],dp[j][k]);
      //(dp2[j+1][max(j+1,k)]+=dp[j][k])%=MOD;
      //(dp2[1][max(1,k)]+=dp[j][k])%=MOD;
    }
    swap(dp,dp2);
  }
  REPE(i,N) REPE(j,N) (cnt[i]+=dp[j][i])%=MOD;
  ZERO(cum);
  REPE(i,N) cum[i+1]=(cum[i]+cnt[i])%MOD;
  LL res=0;
  FORE(a,1,N) {
    int b=min(N,(K-1)/a);
    (res+=cnt[a]*cum[b+1]%MOD)%=MOD;
  }
//  dump(res);
  res=res*modinv(2)%MOD;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  solve();
  return 0;
}
