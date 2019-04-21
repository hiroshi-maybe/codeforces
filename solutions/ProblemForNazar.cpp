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

// $ cp-batch ProblemForNazar | diff ProblemForNazar.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ProblemForNazar.cpp && ./a.out

/*
 
 4/18/2019
 
 8:51-9:30 compilation error
 9:33 AC
 
 https://codeforces.com/blog/entry/66602
 https://naoyat.hatenablog.jp/entry/CodeforcesRound553Div2
 https://cinnamo-coder.hatenablog.com/entry/2019/04/19/123713
 
 simple code by @nuip
 https://codeforces.com/contest/1151/submission/52961786
 
 Summary:
  - subtract `cnt` so that we can easily figure out the number of the last extra elements.
 
 */

LL L,R;

LL exact(LL s, int t) {
  LL res=0;
  REP(_,t) {
    res+=s;
    s*=4;
  }
  return (LL)res;
}

ModInt f_org(LL R) {
  if(R==0) return 0;
  int n=0;
  while(R>((1LL<<n)-1)) ++n;
  int odd=(n+1)/2,even=n-odd;
  dump(n,odd,even);
  LL x,y;
  if(n%2==0) {
    x=(LL)exact(1,odd);
    y=(LL)exact(2,even-1);
    y+=R-((1LL<<(n-1))-1);
  } else {
    x=(LL)exact(1,odd-1);
    x+=R-((1LL<<(n-1))-1);
    y=(LL)exact(2,even);
  }
  dump(x,y);
  ModInt o=ModInt(x)*(ModInt(x)*(ModInt(2)))/ModInt(2),e=ModInt(y)*(ModInt(y)*ModInt(2)+ModInt(2))/ModInt(2);
  dump(o,e);
  return o+e;
}

ModInt f(LL R) {
  int par=1,step=0;
  ModInt S[2]={2,1};
  ModInt res(0);
  while(R>0) {
    LL n=min(R,1LL<<step);
    R-=n;
    ModInt a=S[par],d=a+ModInt(2)*(n-1);
    ModInt x=(a+d)*n/2;
//    dump(step,a,d,n,x);
    res+=x;
    S[par]=d+2;
    par^=1,++step;
  }
  return res;
}

void solve() {
  ModInt r=f(R),l=f(L-1);
  cout<<r-l<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>L>>R;
  solve();
  
  return 0;
}
