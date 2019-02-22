#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
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
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch SashaAndInterestingFactFromGraphTheory | diff SashaAndInterestingFactFromGraphTheory.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SashaAndInterestingFactFromGraphTheory.cpp && ./a.out

/*
 
 2/22/2019
 
 13:41-14:20 give up
 
 Possible approaches:
  1. combinatorics
   - C(N-2,x) * C(M-1,x) * x! * {# of ways to form x+2 forest}
    => O(N^3) time?
  2. Cayle's formula
   - N^(N-2) wasy to make a tree
  3. Count complete set
   - N^(N-2)*M^(N-1) - ?
 
 14:20-15:40 read editorials and got AC
 
 https://codeforces.com/blog/entry/65295
 
 Approach #1 and #2 are actually correct.
 Missing part:
  - Weight of other edges doesn't matter. Just multiply by M^(N-2-x)
   - We can fucus on how to choose forrest regardless of edge weight
  - How to count # of `x` forest from `n` vertices
   => there is generalized Cayley's formula... 😔
    T(n,k) = k*n^(n-k-1)
    https://en.wikipedia.org/wiki/Cayley's_formula#Generalizations
 
   f(x)
 = C(N-2,x) * C(M-1,x) * x! * M^(N-2-x) * T(N,x+2) where T(n,k) = T(N,x+2) in this problem
 = C(N-2,x) * C(M-1,x) * x! * M^(N-2-x) * (x+2)*N^(N-x-3)
 
 res = ∑ { f(x) : x=0..min(N-2,M-1) }
 
 */

const int MOD=1000000007;
//const int MOD=998244353;
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

const int MAX_N=1e6+1;
int N,M,A,B;

ModInt powM[MAX_N],powN[MAX_N],fact[MAX_N];
// C(N-2,x) * C(M-1,x) * M^(N-2-x) * (x+2)*N^(N-x-3)
ModInt f(LL x) {
  ModInt res=fact[x];
  res*=choose(N-2,x);
  res*=choose(M-1,x);
  res*=powM[N-2-x];
  assert(N-x-3>=-1);
  if(N-x-3>=0) res*=powN[N-x-3]*(x+2);
  return res;
}
void solve() {
  powM[0]=powN[0]=fact[0]=1;
  REP(i,MAX_N-1) {
    powM[i+1]=powM[i]*M;
    powN[i+1]=powN[i]*N;
    fact[i+1]=fact[i]*(i+1);
  }
  ModInt res;
  REPE(x,min(M-1,N-2)) res+=f(x);
  
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>A>>B;
  solve();
  
  return 0;
}
