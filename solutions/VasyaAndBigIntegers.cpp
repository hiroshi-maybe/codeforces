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
 
 9/20/2018
 
 9:34-9:45 time is up
 
 9/26/2018
 
 14:50-19:00, 19:30-19:50 AC after reading reditorials
 
 http://kmjp.hatenablog.jp/entry/2018/09/21/0900
 http://codeforces.com/blog/entry/61969
 
 We are solving dp[i] which corresponds counting for A[i..]
 From L and R, we should be able to find valid range [l,r] s.t. L<=A[i..<l]<=R and L<=A[i..<r]<=R.
 
 Then dp[i] = dp[l]+dp[l+1]+..+dp[r]
 
 There are two problems that we should solve:
 1. How to find (l,r) in O(1) for `i`
 2. How to compute dp[i] = ∑ { dp[j] : j=l..r }
 
 1. How to find (l,r) for A[i..]
 
 If we could find the first digit that differs between A[i..] and L, we can determine `l`.
 "the first digit that differs" is exactly common prefix between A[i..] and L, which can be precomputed by Z-algorithm in linear time.
 Same method is applicable to `r` as well.
 
 2. How to compute dp in [l,r]
 
 We can keep cumulative sum to compute dp value in specific range.
 - dp[i] : counting of A[i...]
 - cum[i] : ∑ { dp[j] : j=i..N-1 }
 
 => dp[i] = cum[r+1]-cum[l]
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e6+10;
string A,L,R;
const LL MOD=998244353;

vector<int> zalgo(string S) {
  int N=S.size();
  vector<int> Z(N,0);
  int l=0;
  for(int i=1; i<N; ++i) {
    // S[l..r] is current right most prefix-substring
    int r=l+Z[l],pre=Z[i-l];
    if (i+pre<r) {
      Z[i]=pre;
    } else {
      int j=max(0, r-i);
      while(i+j<N&&S[j]==S[i+j]) ++j;
      Z[i]=j;
      l=i;
    }
  }
  Z[0]=N;
  return Z;
}

int comp(VI &Z, string &S, int i) {
  if(i+SZ(S)>SZ(A)) return -1;
  int di=Z[i+SZ(S)+1];
  if(di==SZ(S)) return 0;
  assert(i+di<SZ(A));
  return A[i+di]<S[di]?-1:1;
}

LL dp[MAX_N],cum[MAX_N];
LL solve() {
  ZERO(dp),ZERO(cum);
  int N=SZ(A);
  VI ZL=zalgo(L+"$"+A),ZR=zalgo(R+"$"+A);
  
  dp[N]=cum[N]=1;
  for(int i=N-1; i>=0; --i) {
    if(A[i]=='0') {
      if(L=="0") (dp[i]=dp[i+1])%=MOD;
      else dp[i]=0;
    } else {
      int l=i+SZ(L);
      if(comp(ZL,L,i)==-1) ++l;
      int r=i+SZ(R);
      if(comp(ZR,R,i)==1) --r;
      
      if(l<=r&&l<=N) {
        r=min(r,N);
        if(r!=N)dp[i]=(cum[l]+MOD-cum[r+1])%MOD;
        else dp[i]=cum[l];
      }
    }
    cum[i]=(cum[i+1]+dp[i])%MOD;
  }
  return dp[0];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>A>>L>>R;
  cout<<solve()<<endl;
  return 0;
}
