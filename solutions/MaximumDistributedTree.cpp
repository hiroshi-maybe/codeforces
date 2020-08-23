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
//#define __KUMATRACE__ true
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
  bool operator<(const ModInt &that) const { return val < that.val; }  // To use std::map<ModInt, T>
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
// $ cp-batch MaximumDistributedTree | diff MaximumDistributedTree.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MaximumDistributedTree.cpp && ./a.out

/*

 8/21/2020

 9:10-9:42 WA

 8/22/2020

 11:10-12:38 AC after looking at https://codeforces.com/contest/1401/submission/90644514

 https://twitter.com/hanseilimak/status/1297410655914307585
 https://codeforces.com/blog/entry/81700

 https://twitter.com/ei1333/status/1296848580024532992
 https://twitter.com/kzyKT_M/status/1296848413615513602
 https://twitter.com/laycrs/status/1296850450688270336
 https://twitter.com/satanic0258/status/1296851869327753216

 */

const int MAX_N=1e5+1;
LL P[MAX_N];
int N,M;

VI G[MAX_N];
LL A[MAX_N];
int dfs(int u, int pre=-1) {
  int res=1;
  FORR(v,G[u])if(v!=pre) {
    res+=dfs(v,u);
  }
  LL b=res,a=N-res;

  A[u]=a*b;
  dump(u,A[u]);

  return res;
}
void solve() {
  dfs(0,-1);

  sort(A,A+N),reverse(A,A+N);
  assert(A[N-1]==0);
  dumpC(A,A+N)
  vector<LL> ps(P,P+M);
  sort(ALL(ps)),reverse(ALL(ps));
  while(SZ(ps)<N-1) ps.push_back(1);
  dumpc(ps);

  ModInt res(0);
  for(int i=N-2; i>=1; --i) {
    dump(ps.back(),A[i],A[i]*ps.back());
    res+=ModInt(A[i])*ps.back(),ps.pop_back();
  }

  ModInt x(1);
  while(SZ(ps)) x*=ps.back(),ps.pop_back();
  res+=x*A[0];
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N) G[i].clear(),A[i]=0,P[i]=0;
    REP(i,N-1) {
      int u,v; cin>>u>>v;
      --u,--v;
      G[u].push_back(v),G[v].push_back(u);
    }
    cin>>M;
    REP(i,M) cin>>P[i];
    solve();
  }

  return 0;
}
