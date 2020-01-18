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
// $ cp-batch TwoArrays | diff TwoArrays.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TwoArrays.cpp && ./a.out

/*
 
 1/14/2020
 
 7:10-8:22 AC
 
 https://codeforces.com/blog/entry/73105
 https://twitter.com/hanseilimak/status/1218455688038375424
 
 */

const int MAX_N=1000+10,MAX_M=11;
int N,M;

ModInt dp[MAX_M][MAX_N];
ModInt cnta[MAX_N],cntb[MAX_N],cum[MAX_N];
void solve() {
  FORE(x,1,N) {
    ZERO(dp);
    dp[0][x]=1;
    FORE(i,1,N) cum[i]=cum[i-1]+dp[0][i];
    REP(i,M-1){
      FORE(a,1,N) dp[i+1][a]=cum[a];
      ZERO(cum);
      FORE(j,1,N) cum[j]=cum[j-1]+dp[i+1][j];
    }
    cnta[x]=cum[N];
//    FORE(i,1,N) cnta[x]+=dp[M-1][i];
    ZERO(dp); ZERO(cum);
    dp[0][x]=1;
    for(int i=N; i>=1; --i) cum[i]=cum[i+1]+dp[0][i];
//    REPE(i,N) cum[i+1]=cum[i]+dp[0][i];
    REP(i,M-1){
      FORE(b,1,N) {
        dp[i+1][b]=cum[b];
//        dump(x,i,b,cum[b]);
      }
      ZERO(cum);
      for(int j=N; j>=1; --j) cum[j]=cum[j+1]+dp[i+1][j];
    }
//    FORE(i,1,N) cntb[x]+=dp[M-1][i];
    cntb[x]=cum[1];
//     dump(x,cnta[x],cntb[x]);
  }
  
  vector<ModInt> cum(N+2);
  REPE(i,N) cum[i+1]=cum[i]+cnta[i];
  ModInt res=0;
//  FORE(x,1,N) res+=cntb[x]*cum[x+1];
  FORE(a,1,N)FORE(b,1,a) {
//    dump(a,b,cnta[a],cntb[b]);
    res+=cnta[a]*cntb[b];
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  solve();
  
  return 0;
}
