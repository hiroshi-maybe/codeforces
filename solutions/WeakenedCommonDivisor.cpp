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
 
 8/19/2018
 
 6:49-7:17 give up
 
 My solution was returning `1` for below test casa
 
 ```
 1
 10 9
 ```
 
 1 should not be expected result
 
 8/26/2018
 
 16:10-16:40 read editorials
 
 Editorials:
  - http://codeforces.com/blog/entry/61323
  - http://betrue12.hateblo.jp/entry/2018/08/20/212528

 Tweets:
  - https://togetter.com/li/1258285
  - https://twitter.com/satanic0258/status/1031208997158772737
  - https://twitter.com/ei1333/status/1031208880380862464
  - https://twitter.com/Yazaten/status/1031208986035384320
 
 There are tons of divisors. Enumeration of it TLEs.
 Primes are always better than divisors. Testing by unique primes of A[0] and B[0] works.
 
 Key:
  - there exists an answer, it should be prime factor of either A[i] or B[i]
 
 */

// 6:56 1WA
// 7:03 2WA
// 7:17 3WA
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
int N;
LL A[MAX_N],B[MAX_N],L[MAX_N];

LL gcd(LL a, LL b) {
  return b == 0 ? a : gcd(b, a % b);
}
LL lcm(LL a, LL b) {
  return (a*b) / gcd(a,b);
}

int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rand() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

vector<LL> distinctPrimeFactors(LL n) {
  /*
   vector<LL> res=primeFactors(n);
   res.erase(unique(res.begin(),res.end()),res.end());
   return res;
   */
  assert(n>=1);
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) if(n%p==0) {
    res.push_back(p);
    while(n%p==0) n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}

LL solve() {
  vector<LL> X[2];
  X[0]=distinctPrimeFactors(A[0]);
  X[1]=distinctPrimeFactors(B[0]);
  REP(i,2) FORR(x,X[i]) {
    bool ok=true;
    REP(j,N) ok&=(A[j]%x==0)||(B[j]%x==0);
    if(ok) return x;
  }
  return -1;
}

/*
 
 TLE for test case
 
 2
 1999999973 1999999943
 1999999973 1999999943
 
 sqrt(3999999832000001539) ≈ 2*10^9
 
 */
LL solve_tle() {
  if(N==1) {
    //LL res=gcd(A[0],B[0]);
    //if(res==1) res=-1;
    //return res;
    return A[0];
  }
  
  REP(i,N) L[i]=lcm(A[i],B[i]);
  LL res=L[0];
  REP(i,N) res=gcd(res,L[i]);
  if(res==1) return -1;
  
  dump(res);
  vector<LL> P=distinctPrimeFactors(res);
  dump(SZ(P));
  FORR(p,P) {
    bool ok=true;
    REP(i,N) if(A[i]%p!=0&&B[i]%p!=0) ok=false;
    if(ok) return p;
  }
  return -1;
}

bool ok(LL res) {
  bool ok=true;
  REP(i,N) ok&=((A[i]%res)==0)||((B[i]%res)==0);
  return ok;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  /*
  while(true) {
    int sz=genRandNum(1,100);
//    dump(sz);
    VI a=genRandSeq(sz,2,1000),b=genRandSeq(sz,2,1000);
    N=sz;
    REP(i,N)A[i]=a[i],B[i]=b[i];
    LL res=solve();
    if(!ok(res)) {
      dump(res);
      dumpAR(a);
      dumpAR(b);
      REP(i,N) dump(L[i]);
    }
    assert(ok(res));
  }*/
  
  cin>>N;
  REP(i,N) cin>>A[i]>>B[i];
  cout<<solve()<<endl;
  return 0;
}
