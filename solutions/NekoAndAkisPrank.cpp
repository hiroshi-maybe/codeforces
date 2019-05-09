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

// $ cp-batch NekoAndAkisPrank | diff NekoAndAkisPrank.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NekoAndAkisPrank.cpp && ./a.out
/*
 
 4/24/2019
 
 8:43-8:59 give up
 
 Maximum matching in a tree seems to be tree dp problem.
 However Trie tree is too large. I'm in stuck.
 
 5/8/2019
 
 13:56-14:30, 16:25-17:45 read editorials and got AC
 
 https://codeforces.com/blog/entry/66696
 http://drken1215.hatenablog.com/entry/2019/04/25/180000
 https://cinnamo-coder.hatenablog.com/entry/2019/04/25/031403
 
 It's hard to even start analysis without knowing that maximum matching in a tree can be solved by greedy from leaves.
 Result is sum of vertices in odd depth so that the edge of leaves are counted.
 Firstly we can make make a tree with prefix balance>=0 condition.
 That is necessary condition. The balance at depth 2*N may not be 0.
 We can count # of vertices by which balance 0 sequence can be created.
 The condition is balance <= 2*N - prefix length
 
 1. Based on greedy property, we want to count # of vertices of odd depth in the trie tree
 2. It's possible to make a trie with unwanted vertices by dp
  Some of trie nodes cannot achieve balance==0 at length 2*N.
  We want to filter them. How can we achieve that?
 3. It's possible to validate dp states by condition balance at depth `i` <= 2*N - i
 
 Summary:
  - missing knowledge
   - greedy from leaves solves maximum matching of a rooted tree
  - technique
   - filter states which satisfy sufficiency after dp
 
 */

const int MAX_N=1e3+1;
int N;

ModInt dp[2*MAX_N][MAX_N];
void solve() {
  ZERO(dp);
  dp[0][0]=1;
  REP(i,2*N) REPE(j,N) {
    if(j+1<=N)dp[i+1][j+1]+=dp[i][j];
    if(j>0)dp[i+1][j-1]+=dp[i][j];
  }
  ModInt res;
  for(int i=1; i<2*N; i+=2) REPE(j,N) {
    int rem=2*N-i;
    if(j<=rem) res+=dp[i][j];
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  solve();
  
  return 0;
}
