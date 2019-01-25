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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');

// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

// $ cp-batch PowersOfTwo | diff PowersOfTwo.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PowersOfTwo.cpp && ./a.out

/*
 
 1/24/2019
 
 14:13-15:45 AC
 
 https://codeforces.com/blog/entry/64130
 https://betrue12.hateblo.jp/entry/2018/12/28/152148
 https://mumumucoder.hatenablog.com/entry/2018/12/28/015653
 
 My solution does not have clear proof of correctness.
 However solutions in editorials are clearly correct.
 
 Suppose N=9, K=4.
 
 We can represent N in binary representation and keep summation of them N as invariant.
 
        8 4 2 1
 cnt = {1,0,0,1}, ∑ cnt = 2 < K (=4)
 
 We can break 2^k into 2*2^(k-1).
 The most important point is that ∑cnt always incerases by "1" when this operation happens.
 Therefore if ∑cnt < K, we can eventually adjust ∑cnt to K as long as K<N. Alogrithm terminates.
 K<=2*10^5. This O(K) operation fits in TL.
 
 */

int N,K;

void nope() {
  println("NO");
  exit(0);
}
VI res;
void f(int i, int n, int k) {
  if(i==-1) {
    assert(n==0&&k==0);
    return;
  }
  int pow2=1<<i;
  while(n-pow2>=0&&k-1>=0&&n-pow2>=k-1) {
    res.push_back(pow2);
    n-=pow2,--k;
//    dump2(n,k);
  }
  f(i-1,n,k);
}
void solve_org() {
  VI X;
  if(K<__builtin_popcount(N)||K>N) nope();
  f(30,N,K);
  assert(SZ(res)==K);
  assert(accumulate(ALL(res),0)==N);
  println("YES");
  REP(i,K) printf("%d ",res[i]);
  println("");
}

void solve() {
  int cnt[31]={};
  REP(i,31) if((N>>i)&1) cnt[i]++;
  int sum=accumulate(cnt,cnt+31,0);
  int i=30;
  while(sum<K&&i>0) {
    if(cnt[i]>0) {
      cnt[i]--,cnt[i-1]+=2;
      sum+=1;
    } else {
      --i;
    }
  }
  
  if(sum!=K) {
    nope();
  } else {
    assert(accumulate(cnt,cnt+31,0)==K);
    int x=0;
    println("YES");
    REP(i,31) REP(j,cnt[i]) printf("%d ",1<<i),x+=(1<<i);
    assert(x==N);
    println("");
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K;
  solve();
  
  return 0;
}
