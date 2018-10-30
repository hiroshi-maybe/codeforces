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
 
 10/24/2018 R518 div2
 
 11:00-11:35 time is up (1MLE, 1TLE)
 
 I figured out O(max{A}^2*N) time dp. However I couldn't optimize further.
 
 10/30/2018
 
 13:55-15:30 read editorials and got AC
 
 http://codeforces.com/blog/entry/62688
 
 In delivery dp, it's hard to find a property of cumulative sum.
 
 dp[i+1][a][a<=x]+=dp[i][x][done] if done||x<=a

 However if it's represented by dp in pull form, we can find structure of cumulative sum.
 
 Summary:
  - New technique that I've not known
   - If recurrence relation is sum of specific range, it's possible to apply cumulative sum
   - This is hard to figure out if formula is delivery form
   - I should look at both forms in recurrence relation for some discovery
 
 */

// 11:00-11:35
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
LL A[MAX_N];
int N;
LL dp[2][201][2];
const LL MOD=998244353;

LL cum[202][2];
LL solve() {
  ZERO(dp);
  if(A[0]==-1) {
    FORE(a,1,200) dp[0][a][0]=1;
  } else {
    dp[0][A[0]][0]=1;
  }
  auto docum=[&](int p) {
    REPE(a,200)REP(done,2) cum[a+1][done]=(cum[a][done]+dp[p][a][done])%MOD;
  };
  docum(0);
  FOR(i,1,N) {
    int p1=i&1,p2=p1^1;
    FORE(a,1,200) {
      if(A[i]!=-1&&a!=A[i]) {
        dp[p1][a][0]=dp[p1][a][1]=0;
        continue;
      }
      LL b=0; REP(done,2)b+=MOD+cum[a][done]-cum[1][done];
      dp[p1][a][0]=b;
      dp[p1][a][1]=MOD+cum[201][1]-cum[a][1]+dp[p2][a][0];
      REP(done,2) dp[p1][a][done]%=MOD;
//      dump4(i,a,dp[p1][a][0],dp[p1][a][1]);
    }
    docum(p1);
  }
  LL res=0;
  FORE(a,1,200) {
//    dump2(a,dp[(N-1)&1][a][1]);
    res=(res+dp[(N-1)&1][a][1])%MOD;
  }
  return res;
}

LL solve_tle() {
  ZERO(dp);
  if(A[0]==-1) {
    FORE(a,1,200) dp[0][a][0]=1;
  } else {
    dp[0][A[0]][0]=1;
  }
  FOR(i,1,N)FORE(x,1,200)REP(done,2) {
    int p1=(i+1)&1,p2=p1^1;
    if(A[i]!=-1) {
      LL a=A[i];
      if(done) {
        dp[p2][a][a<=x]+=dp[p1][x][done];
      } else if(x<=a) {
        dp[p2][a][a<=x]+=dp[p1][x][done];
      }
      dp[p2][a][a<=x]%=MOD;
    } else {
      FORE(a,1,200) {
        if(done) {
          dp[p2][a][a<=x]+=dp[p1][x][done];
        } else if(x<=a) {
          //          if(dp[i-1][x][done])dump4(a,x,done,dp[i-1][x][done]);
          dp[p2][a][a<=x]+=dp[p1][x][done];
        }
        dp[p2][a][a<=x]%=MOD;
      }
    }
  }
  LL res=0;
  FORE(a,1,200) res=(res+dp[(N-1)&1][a][1])%MOD;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
