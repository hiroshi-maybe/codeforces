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

// $ ../batch NewYearAndThePermutationConcatenation | diff NewYearAndThePermutationConcatenation.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NewYearAndThePermutationConcatenation.cpp && ./a.out

/*
 
 12/30/2018
 
 07:57-8:52 AC by experiment
 
 https://codeforces.com/blog/entry/64196
 http://kmjp.hatenablog.jp/entry/2018/12/31/0930
 
 https://www.nayuki.io/page/next-lexicographical-permutation-algorithm
 
 Understanding how next permutation works is mandatory to solve this problem.
 Permutation with suffix/prefix with length `k` holds when A[N-k..N-1] is NOT decreasing.
 
 Thus for `k` suffix, res[k]=C(N,N-k)*(N-k)!*(k!-1), k=2..N-1
 
 Note that we may count multiple times for same consecutive permutations.
 
 5,3,2,1,4, 5,3,2,4,1
   ^          $
     ^          $
       ^          $
         ^          $
 
 Thus we don't need to worry about duplicated count for `k!-1` part in the formula.
 I spent a lot of time to correct my understanding... 😞
 
 */

const int MOD=998244353;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};
int N;

void solve_org() {
  ModInt np(1);
  FORE(n,1,N) np*=n;
  ModInt res=np,cur(N);
  REP(i,N-2) {
    res+=np-cur;
    cur*=N-i-1;
  }
  cout<<res<<endl;
}

LL choose(LL n, LL k) {
  if(n<k) return 0;
  
  const int MAX_N = 1e6+1;
  assert(k<=MAX_N);
  static LL fact[MAX_N+1],revfact[MAX_N+1],rev[MAX_N+1];
  
  if(rev[1]==0) {
    rev[1]=1;
    for(int i=2;i<=MAX_N;i++) rev[i]=rev[MOD%i]*(MOD-MOD/i)%MOD;
    fact[0]=1,revfact[0]=1;
    for(int i=1;i<=MAX_N;i++) {
      fact[i]=fact[i-1]*i%MOD;
      revfact[i]=revfact[i-1]*rev[i]%MOD;
    }
  }
  return fact[n]*revfact[n-k]%MOD*revfact[k]%MOD;
}

void solve() {
  vector<ModInt> fact(N+1,ModInt(1));
  FORE(k,1,N) fact[k]=fact[k-1]*ModInt(k);
//  dumpAR(fact);
  ModInt res(fact[N]);
  FOR(k,2,N) res+=ModInt(choose(N,k))*fact[N-k]*(fact[k]-ModInt(1));
  cout<<res<<endl;
}

void test() {
  VI A;
  int n=5;
  VI P(n); REP(i,n)P[i]=i+1;
  do {
    FORR(p,P) A.push_back(p);
  } while (next_permutation(ALL(P)));
//  dumpAR(A);
  
  int cnt=0;
  MAPII M;
  REPE(i,SZ(A)-n) {
    VI xs; int sum=0;
    REP(j,n) sum+=A[i+j],xs.push_back(A[i+j]);
    if(sum==n*(n+1)/2) {
      M[i%n]++;
//      dumpAR(xs);
//      sort(ALL(xs));
//      if(xs!=P)dumpAR(xs);
      ++cnt;
    }
  }
  dump(cnt);
  FORR(kvp,M) dump2(kvp.first,kvp.second);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>N;
  solve();
  
  return 0;
}
