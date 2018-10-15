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
 
 10/14/2018
 
 21:05-22:15 give up
 
 Possible aproaches:
 - Convolution of formula ❌
 - dp ❌
 - decompose and combine (2^M => polynomial) ❌
 - count only smallest one to avoid duplication ✅
 - constructive property ❌
 
 22:16-23:15 read editorial and got AC
 
 http://codeforces.com/blog/entry/62411
 
 Ok. Actually no need to distinguish equality of segments.
 It's hard as analyzed that 2^M cases is not easy to transform.
 
 If we count only smallest string, we don't need to take care of it.
 Pros of this approach is just manipulating number of all the segments give unknown that we want to know.
 
 res = ∏ { cnt[i] : i=0..M-1 segments } * A^(N-2*B[M-1])
 
 cnt[i] (segment length `l`) is also interesting problem to solve.
 
 Firstly we can list all the possible strings with length 2*l.
 
 aaa..aaa
 .
 abc..cba
 .
 abc..def
 .
 .
 .
 fed..cba
 
 1) string is NOT symmetry like "abc..def"
 
 There should exist a counterpart in which swap resulted.
 
 "abc..def" <=> "fed..cba"
 
 In this case, we always select either one which is smaller
 
 ✅ "abc..def" <=> ❌ "fed..cba"

 2) string is symmetry like "abc..cba"
 
 There is no counterpart. "abc..cba" should always be picked.
 
 Suppose number of strings of case #1 = S, number of strings of case #2 = T.
 
 S + T = A^2*L
 T = A^L
 cnt[i] = S/2 + T
 
 S = A^2*L - T = A^2*L - A^L
 cnt[i] = S/2 + T = (A^2*L - A^L)/2 + A^L = (A^2*L + A^L)/2
 
 Actually there is dp solution
 https://twitter.com/satanic0258/status/1050429884709752832
 http://codeforces.com/contest/1065/submission/44151017 by @satanic0
 
 Key:
  - If you want to count unique pattern, count only smallest one to avoid duplication
 
 Summary:
  - "count unique string" did you a problem having a similar unknown? Yes. However I failed to come up with it 😞
   - Need more training to associate problems with similar unknown
  - I tried to leverage knowledge that I got in analysis of small problem. However it lead to wrong direction. I should have sought for different approach
  - Anyway we need to decompose to each segment. I should have digged into easier approach to combine them. That is simply counting avoiding duplication
  - Very impressive puzzle! 😊
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_M=2e5+1;
LL B[MAX_M];
int M;
LL N,A;
LL X[MAX_M];

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

LL solve() {
  A=A%MOD;
  X[0]=B[0];
  REP(i,M-1) X[i+1]=B[i+1]-B[i];
  LL res=1;
  LL div2=modinv(2LL);
  REP(i,M) {
    LL l=X[i];
    LL x=powmod(A,2LL*l),y=powmod(A,l);
    LL z=(x+y)%MOD*div2%MOD;
    res=res*z%MOD;
  }
  LL l=N-2LL*B[M-1];
  assert(l>=0);
  res=res*powmod(A,l)%MOD;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>A;
  REP(i,M) cin>>B[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
