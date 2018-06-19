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
 
 6/18/2018
 
 27:00-27:30 time up
 
 6/19/2018
 
 17:00-18:00 read editorials
 24:15-25:43 implement and got AC
 
 Editorial:
  - http://kmjp.hatenablog.jp/entry/2018/06/19/0900_1
 
 Tweets:
  - https://togetter.com/li/1238701
  - https://twitter.com/satanic0258/status/1008781430355185664
 
 Submit solutions:
  - http://codeforces.com/contest/992/submission/39372783 by @natsugiri
   - this is nested loop though, runtime is O(N*lg 2e18) by breaking inner loop for prod>2e18
   - very simple and beautiful code 👏
  - http://codeforces.com/contest/992/submission/39369516 by @uwi
  - http://codeforces.com/contest/992/submission/39365641 by @dotorya
   - binary search
 
 Impressive problem to train deep estimation of runtime complexity.
 Algorithm with nested loop works because number of execution of inner loop is upper-bounded by log 2e18
 x, 2, 1, 2, 1, 2, .. , 1, 2, y is worst case to compare summation with product.
 
 Note that 1, 1, 1, .. , 1 must be aggregated to guarantee above upper-bound.
 
 P * x <= S + x only if x=1 (P = ∏a )
 
 Thus consecutive 1s must be packed firstly.
 
 Key:
  - Simply try all possible intervals with nested loop
  - P is at most MAX_N*MAX_a*MAX_K (=2e18). Thus inner loop is executed at most log 2e18
  - P*x <= S+x only if x=1, thus consecutive 1s must be compressed (coordinate compression)
 
 Summary:
  - Impressive problem which tricks runtime complexity
  - I need more training to solve such a problem which needs deeper analysis of computation 😄
  - Multiplication of arbitrary natural numbers could be upper-bounded by logarithm
  - Interval starting with `1` needs multiple left-end start (2WA in implementation)
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
LL A[MAX_N];
int N,K;
const LL Inf=2e18+1;

LL solve_bruteforce() {
  LL res=0;
  
  REP(i,N) {
    LL prod=1,sum=0;
    FOR(j,i,N) {
      //      dump4(i,j,prod,sum);
      LL n=A[j];
      //      dump4(i,j,n,cnt);
      
      prod*=n;
      sum+=n;
      if(prod==sum*K) {
        ++res;
        dump4(i,j,prod,sum);
      }
    }
  }
  return res;
}

LL solve_x() {
  vector<pair<LL,int>> X;
  REP(i,N) {
    if(A[i]==1&&SZ(X)&&X.back().first==1) X.back().second++;
    else X.emplace_back(A[i],1);
  }
  LL res=0;
  int M=SZ(X);
  
  LL a=0;
  REP(i,M) {
//    dump3(i,X[i].first,X[i].second);
    a+=X[i].first*X[i].second;
  }
  assert(a==accumulate(A,A+N,0LL));
  
  REP(i,M) {
    LL prod=1,sum=0;
    FOR(j,i,M) {
//      dump4(i,j,prod,sum);
      LL n=X[j].first,cnt=X[j].second;
//      dump4(i,j,n,cnt);
      
      REP(k,cnt) {
        prod*=n;
        sum+=n;
        if(prod==sum*K) {
          ++res;
          dump4(prod,sum,K,k);
        }
      }
    }
  }
  return res;
}

LL solve() {
  vector<pair<LL,int>> X;
  REP(i,N) {
    if(A[i]==1&&SZ(X)&&X.back().first==1) X.back().second++;
    else X.emplace_back(A[i],1);
  }
  LL res=0;
  int M=SZ(X);
  REP(i,M) {

    int KK=X[i].second;
    REP(k,KK) {
      LL prod=1,sum=0;
      if(X[i].first==1) {
        sum=1;
        if(prod==sum*K) ++res;
        --X[i].second;
      }
      
      FOR(j,i,M) {
        //        dump4(i,j,prod,sum);
        LL n=X[j].first,cnt=X[j].second;
        //        dump4(i,j,n,cnt);
        if(n!=1) {
          if(prod>=Inf/n) break;
          prod*=n;
          sum+=n;
          if(prod==sum*K) {
            ++res;
//            dump3(prod,sum,K);
          }
        } else {
          if(prod%K==0) {
            LL x=prod/K-sum;
            if(1<=x&&x<=cnt) {
              ++res;
//              dump4(prod,sum,K,x);
            }
          }
          sum+=cnt;
        }
      }
    }
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
