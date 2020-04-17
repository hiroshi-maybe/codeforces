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
// $ cp-batch KaaviAndMagicSpell | diff KaaviAndMagicSpell.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address KaaviAndMagicSpell.cpp && ./a.out

/*
 
 4/15/2020
 
 8:46-10:05 give up
 
 4/16/2020
 
 9:10-10:04 read editorials
 21:17-22:20 AC
 
 https://twitter.com/hanseilimak/status/1251022146542858241
 https://codeforces.com/blog/entry/76099
 https://twitter.com/ngtkana/status/1250472114592743424
 https://twitter.com/risujiroh/status/1250477858637656064
 https://twitter.com/ajis_ka/status/1250472401617317888
 
 */

int N,M;
string S,T;

const int MAX_N=3001;
ModInt memo[MAX_N][MAX_N];
int viz[MAX_N][MAX_N];
ModInt f(int i, int j) {
  if(j<0) return 0;
  if(i==N) {
    return j==0?1:0;
  }
  ModInt &res=memo[i][j];
  if(viz[i][j]) return res;
  viz[i][j]=1;
  if(j==0) {
    if(i<M) res=S[i]==T[i]?f(i+1,j):0;
    else res=f(i+1,j)+1;
  }
  if(1<=j&&j<M) {
    if(i+j>=M) res=f(i+1,j)+(T[j-1]==S[i]?f(i+1,j-1):0);
    else res=(T[j-1]==S[i]?f(i+1,j-1):0)+(T[j+i]==S[i]?f(i+1,j):0);
  }
  if(j==M) res=(S[i]==T[M-1]?f(i+1,j-1):0)+f(i+1,j);
  if(j>M) res=f(i+1,j)+f(i+1,j-1);
//  dump(i,j,res);
  return res;
}
void solve() {
  N=SZ(S),M=SZ(T);
  ZERO(viz);
  ZERO(memo);
  ModInt res=0;
  REP(j,N) if((j<M&&S[0]==T[j])||j>=M) {
    res+=f(1,j)*2;
//    dump(j,f(1,j));
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>S>>T;
  solve();
  
  return 0;
}
