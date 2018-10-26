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
 
 10/24/2018
 
 18:20-18:40 give up
 
 10/25/2018
 
 17:00-18:36 understand what editorial is describing
 18:37-19:10 got AC
 
 - separate to two dimensions independently?
  => correct as a result of formula expansion
 - sum of multiplication <=> multiplication of sum?
  => kind of correct as a expansion of the formula
 
 http://codeforces.com/blog/entry/61891
 http://kmjp.hatenablog.jp/entry/2018/09/19/0900
 
 Key:
  - sum of squares can be expanded to square of sums and sum
  - expand multiplication in formula to leverage cumulative sum
  - dp with cumulative sum
 
 Summary:
  - My formula was wrong. congratulations about pooooooor math 👏. Unknown is expected value of "Addition" of scores"
  - Linear dp with cumulative sum is the first pattern for me. Nice to learn.
 
 */

// 18:40 time is up
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
LL A[MAX_N][MAX_N];
int N,M,TR,TC;
const LL MOD=998244353;

LL powmod(LL a, LL b) {
  assert(0<=a);
  assert(0<=b);
  a%=MOD;
  
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

LL dp[MAX_N][MAX_N];
LL solve() {
  vector<III> X;
  REP(i,N)REP(j,M) X.emplace_back(A[i][j],i,j);
  sort(X.begin(),X.end());
  
  ZERO(dp);
  LL dpsum=0,rrsum=0,rsum=0,ccsum=0,csum=0;
  int L=SZ(X);
  int l=0;
  while(l<L) {
    int r=l;
    while(r<L&&get<0>(X[r])==get<0>(X[l])) ++r;
    LL K=l;
    LL KINV=modinv(K);
    FOR(k,l,r) {
      int _,i,j; tie(_,i,j)=X[k];
      if(K==0) {
        dp[i][j]=0;
        continue;
      }
      
      dp[i][j]=(rrsum+ccsum+MOD-2LL*i%MOD*rsum%MOD+MOD-2LL*j%MOD*csum%MOD+dpsum)%MOD;
      (dp[i][j]*=KINV)%=MOD;
      (dp[i][j]+=i*i+j*j)%=MOD;
      
//      if(i==TR&&j==TC) {
//        dump4(k,rrsum,ccsum,dp[i][j]);
//        dump4(k,rsum,csum,dpsum);
//      }
    }
    FOR(k,l,r) {
      int _,i,j; tie(_,i,j)=X[k];
      (dpsum+=dp[i][j])%=MOD;
      (rrsum+=i*i)%=MOD;
      (ccsum+=j*j)%=MOD;
      (rsum+=i)%=MOD;
      (csum+=j)%=MOD;
    }
    l=r;
  }
  return dp[TR][TC];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,N)REP(j,M) cin>>A[i][j];
  cin>>TR>>TC;
  --TR,--TC;
  
  cout<<solve()<<endl;
  
  return 0;
}
