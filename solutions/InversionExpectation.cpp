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

// $ ../batch InversionExpectation | diff InversionExpectation.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address InversionExpectation.cpp && ./a.out

/*
 
 1/3/2019
 
 16:40-17:35 give up
 
 This is counting problem.
 
 res=sum of # of inversions / |unused|!
 
 Ideas:
  - inversion => BIT?
  - permutation => insertion dp => too many states
  - dp with cumulative sum => hard to manage unused elements
  - move backward => too many states
  - drop condition. how to solve if A={-1,-1,..,}?
 
 17:35-18:15, 20:00-21:32 read editorials and got AC by counting
 
 https://codeforces.com/blog/entry/64156
 https://betrue12.hateblo.jp/entry/2018/12/29/144314
 http://kmjp.hatenablog.jp/entry/2018/12/30/0930
 
 Key:
  - compute total number without breaking into partial sequences by math
  - decompose to independent four problems
   - {known,unknown} x {known,unknown}
 
 I was completely blind about decomposition of summation.
 We can dedompose to stateless independent problems based on four cases
 Try to find decomposition approach especially if linear time solution is required.
 
 I computed counting for each cases while editorials are directly computing expected value.
 I got 2WAs because I missed to multiply by permutation of elements which are not in pairs... 😞
 
 Editorial solution is decomposing to four "expected value" problem by linearity of expectation.
 There exists different independent sample spaces and random variables for {known,unknown}x{known,unknown} cases.
 
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

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

struct BIT {
public:
  int N;
  vector<int> T;
  BIT(int N): N(N) {
    T=vector<int>(N+1,0);
  }
  
  // query in [0,r] : ∑ { sum[i] : i=0..r }
  int query(int r) {
    ++r; // 0-based index to 1-based index
    int res=0;
    while(r>0) {
      res+=T[r];
      r-=lsone(r);
    }
    return res;
  }
  
  // query ∑ { sum[i] : i=l..r }
  int query(int l, int r) {
    assert(l<=r&&0<=l&&r<N);
    return query(r)-query(l-1);
  }
  
  // sum[i]+=x
  void add(int i, int x) {
    assert(0<=i&&i<N);
    ++i; // 0-based index to 1-based index
    while(i<=N) {
      T[i]+=x;
      i+=lsone(i);
    }
  }
  
  // sum[i]=x
  void update(int i, int x) {
    int v1=query(i)-query(i-1);
    add(i,x-v1);
  }
  
  // compute total inversions
  int inversions(vector<int> ns) {
    int N=ns.size(),res=0;
    for(int i=N-1; i>=0; --i) {
      // Count elements which stays in right side and smaller
      res+=query(ns[i]-1);
      add(ns[i],1);
    }
    return res;
  }
private:
  int lsone(int i) { return i&-i; }
};

void solve() {
  SETI S; REP(i,N)if(A[i]!=-1) S.emplace(A[i]);
  int M=N-SZ(S);
  ModInt factM(1),factM_1(1),factM_2(1);
  FORE(n,1,M) factM*=ModInt(n);
  FORE(n,1,M-1) factM_1*=ModInt(n);
  FORE(n,1,M-2) factM_2*=ModInt(n);

  ModInt res;
  
  // known x known
  BIT B(N+10);
  for(int i=N-1; i>=0; --i)if(A[i]!=-1) {
    res+=ModInt(B.query(A[i]))*factM;
    B.add(A[i],1);
  }
  
  // unknown x unknown
  ModInt cum[MAX_N];
  REP(i,N) cum[i+1]=cum[i]+ModInt(A[i]==-1);
  res+=(cum[N]*(cum[N]-ModInt(1))/ModInt(2)).pow(2)*factM_2;
  
  // known x unknown
  BIT cnt(N+10);
  FORE(n,1,N) if(!S.count(n)) cnt.add(n,1);
  REP(i,N) if(A[i]!=-1) {
    ModInt r=cnt.query(1,A[i]),l=cnt.query(A[i],N);
    res+=r*(ModInt(cum[N]-cum[i]))*factM_1;
    res+=l*(ModInt(cum[i]))*factM_1;
  }
  
  ModInt fact(1);
  FORE(n,1,M) fact*=ModInt(n);
//  dump3(M,res.val,fact.val);
  res/=fact;
  cout<<res<<endl;
  
//  ModInt a(39),b(6);
//  cout<<(a/b)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
