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
 
 9/23/2018 R512 div2
 
 7:10-8:05 time is up
 
 10/2/2018
 
 19:40-20:58 got AC after reading editorials
 
 Q1. When triangle cannot be constructed?
 
 => when K/gcd(NM,K)>2 holds
 
 Another proof:
 
 S=1/2(a*d-b*c) for triangle (0,0),(a,b),(c,d)
 a*d-b*c = 2*N*M/K
 
 Thus 2*N*M should be divisible by K
 
 Q2. a*b/2 is sufficient to build?
 Don't we need to consider more general 1/2*(ad-bc)?
 
 => https://twitter.com/osrehun/status/1043907884688371712
 
 1/2(ad-bc)=NM/K <=> ad-bc=2NM/K
 
 The most important condition is that K>=2.
 Thus ad-bc=2NM/K<=NM
 
 From this condition, we are guessing that it's always possible to build 2NM/K<=NM with only (0,0), (a,0) and (0,d).
 If we can find such construction, problem is solved.
 
 a) K is even
 
 Define K'=K/2
 
 K|2NM => K'|N*M. K' may include divisors of both N and M.
 We can figure out how to split K by looking at gcd(N,K).
 
 Suppose g1=gcd(N,K), g2=K/g1. Then
 N*M = g1*N' * g2*M' where g1*g2=K, N=g1*N', M=g2*M'
 
 Clearly N'<=N and M'<=M. Thus a=N', b=M'
 
 Ex. N=3*7, M=5*11, K=2*3*5 (S=7*11/2)
 => g1=3,N'=7, g2=5,M'=11
 (0,0),(7,0) and (0,11) satisfies it.
 
 b) K is odd
 
 K(>=2) divides N*M. It should have divisor (>1) of either N or M (possibly both).
 Suppose K has divisor of N. Then there exists g1=gcd(N,K)>2 where N=g1*N'
 
 Then 2*N*M/K <= 2*N'*M. Since g1>2, we can build a=2*N'<N, b=M'=M/(K/g1)
 
 http://codeforces.com/blog/entry/62013
 https://twitter.com/osrehun/status/1043907884688371712
 https://www.hamayanhamayan.com/entry/2018/09/24/084425
 http://betrue12.hateblo.jp/entry/2018/09/24/123255
 http://codeforces.com/blog/entry/62013?#comment-460617
 
 Pick's theorem:
 https://ja.wikipedia.org/wiki/%E3%83%94%E3%83%83%E3%82%AF%E3%81%AE%E5%AE%9A%E7%90%86
 
 Summary:
  - Look at condition carefully. It may encourage that we can guess simple solution
   - 2*N*M/K <= N*M implies that (0,0), (a,0) and (0,d) are sufficient
  - We just want to show sufficiency. Try simpler strategy before trying more complex and general one.
  - Constructive problem just needs sufficiency. Thus simple strategy is more likely to work.
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
LL N,M,K;

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
void end() {
  cout<<"NO"<<endl;
  exit(0);
}
void ok(LL a, LL b) {
  assert(a*b==2LL*N*M/K);
  cout<<"YES"<<endl;
  cout<<0<<" "<<0<<endl;
  cout<<a<<" "<<0<<endl;
  cout<<0<<" "<<b<<endl;
  exit(0);
}
vector<LL> divs(LL N) {
  vector<LL> res;
  for(LL p=1; p*p<=N; ++p) if(N%p==0) {
    res.push_back(p);
    if(p*p!=N) res.push_back(N/p);
  }
  return res;
}
void solve_org() {
  LL g=gcd(N*M,K);
  LL k=K/g;
  if(k>2) end();
  LL T=N*M/g*2/k;
  vector<LL> S=divs(N);
  int MM=SZ(S);
  REP(i,MM) S.push_back(S[i]*2);
  FORR(a,S) if(T%a==0) {
    LL b=T/a;
    if(a<=N&&b<=M) ok(a,b);
    if(a<=M&&b<=N) ok(b,a);
  }
  end();
}

void solve() {
  if(2LL*N*M%K!=0) end();
  if(K%2==0) {
    LL K2=K/2;
    LL g1=gcd(N,K2),g2=K2/g1;
//    dump4(g1,g2,N/g1,M/g2);
    ok(N/g1,M/g2);
  } else {
    LL g1=gcd(N,K),g2=K/g1;
    LL N2=N/g1,M2=M/g2;
//    dump4(g1,g2,N2,M2);
    if(g1!=1) N2*=2;
    else M2*=2;
    ok(N2,M2);
  }
}

void test_gridarea() {
  int N=4,M=6,K=3;
  int S=N*M/K;
  REPE(a,N)REPE(b,M)REPE(c,N)REPE(d,M) {
    double s=(a*d-b*c)/2.0;
    if(S==s) dump4(a,b,c,d);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
//  test_gridarea();
  
  cin>>N>>M>>K;
  solve();
  
  return 0;
}
