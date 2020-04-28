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
LL choose(LL n, LL k) {
  if(n<k) return 0;
  
  const int MAX_N = 1e6+1;
  assert(0<=k&&k<=MAX_N);
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
LL factmod(LL n) {
  static vector<LL> memo(1,1);
  if(memo.size()<=n) {
    LL l=memo.size();
    memo.resize(n+1);
    for(LL i=l; i<=n; ++i) memo[i]=memo[i-1]*i, memo[i]%=MOD;
  }
  return memo[n];
}
// $ cp-batch PlacingRooks | diff PlacingRooks.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PlacingRooks.cpp && ./a.out

/*
 
 4/26/2020
 
 9:16-9:35 give up
 
 4/28/2020
 
 9:50-12:00 read editorials and got AC
 
 https://twitter.com/hanseilimak/status/1255207585566736384
 https://codeforces.com/blog/entry/76633
 https://twitter.com/ngtkana/status/1254453537032962048
 https://twitter.com/satanic0258/status/1254451872468922368
 https://twitter.com/camypaper/status/1254450837172060160
 https://twitter.com/kzyKT_M/status/1254448990629670918
 
 code by @kzyKT
 https://codeforces.com/contest/1342/submission/78194816
 
 https://mathtrain.jp/zensya
 https://drken1215.hatenablog.com/entry/2018/02/01/200628
 
 */

int N,K;

long long stirling(int N, int K, bool d10ableBox = false) {
  if(N<K) return 0;
  if(N==0) return 1;
  LL res=0,rev=1;
  
  auto pow=[&](long long x, long long n) -> long long {
    long long res=1;
    while(n>0) {
      if(n&1) res=res*x%MOD;
      x=x*x%MOD,n>>=1;
    }
    return res;
  };
  auto inv=[&](long long x) -> long long { return pow(x,MOD-2); };
  
  for(int i=1; i<=K; ++i) {
    rev=(rev*i)%MOD;
    int sign=(K-i)%2?-1:1;
    res+=(sign+MOD)%MOD*choose(K,i)%MOD*pow(i,N)%MOD;
  }
  return d10ableBox?res:res*inv(rev)%MOD;
}

ModInt solve() {
  if(K>=N) return 0;
  if(K==0) return factmod(N);
  
  int M=N-K;
  ModInt res=stirling(N,M,true);
  res*=choose(N,M);
  
//  ModInt res=stirling(N,M,false);
//  res*=choose(N,M);
//  res*=factmod(M);
  return res*2;
}

ModInt solve_wrong() {
  if(K>=N) return 0;
  if(K==0) return factmod(N);
  int M=N-K;
  dump(N,K,M,K+M-1,K);
  ModInt res=ModInt(choose(K+M-1,K))*factmod(N)/factmod(N-M)*2;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K;
  cout<<solve()<<endl;
  
  return 0;
}
