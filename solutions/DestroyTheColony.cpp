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

const int MOD=1e9+7;
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

// $ cp-batch DestroyTheColony | diff DestroyTheColony.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DestroyTheColony.cpp && ./a.out

/*
 
 2/3/2019
 
 8:28-10:00 give up
 
 2/6/2019
 
 14:00-16:00, 16:40-18:44 read editorials and got AC
 
 https://codeforces.com/blog/entry/64989
 http://kmjp.hatenablog.jp/entry/2019/02/07/0900
 
 Revert works because counting in subset sum is `commutative` and `associative` (Abelian group).
 Suppose we have `a`x2 and `b`x1.
 
 "aab" = "aa" + "b" = "b" + "aa"
 
 In dp, we are processing characters in alphabet order.
 
      0  1   2   3
 `a` ""     aa
 `b` ""  b  aa aab
 
 "aab" is created by "aa"+"b" in dp (dp[3]=dp[2]+cnt(b))
 However "aab" = "aa"+"b" = "b"+"aa"
 Thus we can revert dp[3] by subtracting dp[1] even though dp[3] was populated from dp[2] (dp[3]=dp[3]-cnt(a))
 
 How can we figure out this works? Suppose we are processing characters in random order like `b`, `a`, `z`, ..
 Even if order of character is ramdomized, dp[n] should be always same because order doesn't matter.
 In other word, counting operation is commutative and associative.
 
 */

const int MAX_N=1e5+10;

int cnt[52];
int Q,N;
string S;

ModInt CC,res[52][52];
ModInt dp[MAX_N+1],dp2[MAX_N+1],dp3[MAX_N+1];
ModInt fact[MAX_N+1];
ModInt ifact[MAX_N+1];

int id(char c) {
  if(islower(c)) {
    return c-'a';
  } else {
    return 26+c-'A';
  }
}
void solve() {
  REP(i,SZ(S)) cnt[id(S[i])]++;
  fact[0]=ModInt(1);
  REP(i,MAX_N) fact[i+1]=ModInt(i+1)*fact[i];
  ifact[1]=ModInt(1);
  FOR(i,1,MAX_N) ifact[i+1]=ModInt(1)/ModInt(i+1)*ifact[i];
  CC=fact[N/2]*fact[N/2]*ModInt(2);
  REP(c,52) if(cnt[c]) CC*=ifact[cnt[c]];

  REPE(i,MAX_N) dp[i]=ModInt(0);
  dp[0]=ModInt(1);
  REP(c,52) if(cnt[c]) for(int n=N; n>=0; --n) if(dp[n]) dp[n+cnt[c]]+=dp[n];
  
  REP(c,52) if(cnt[c]) {
    REPE(i,N)dp2[i]=dp[i];
    // revert contribution of char `c`
    REPE(i,N)if(i+cnt[c]<=N) dp2[i+cnt[c]]-=dp2[i];
    res[c][c]=dp2[N/2];

    FOR(c2,c+1,52) {
      REPE(i,N)dp3[i]=dp2[i];
      // revert contribution of char `c2`
      REPE(i,N)if(i+cnt[c2]<=N) dp3[i+cnt[c2]]-=dp3[i];
      res[c][c2]=dp3[N/2];
    }
  }
}

VI pre[55][MAX_N];
set<LL> subset;

void dfs(LL mask, int i, int sum) {
  if(pre[i][sum].empty()) {
    dump(mask,i,sum);
    assert(sum==0);
    subset.emplace(mask);
    return;
  }
  FORR(j,pre[i][sum]) {
    dfs(mask|(1LL<j),j,sum-cnt[i]);
  }
}

void solve_wrong() {
  N=SZ(S);
  REP(i,SZ(S)) {
    if(islower(S[i])) {
      cnt[S[i]-'a']++;
    } else {
      cnt[26+S[i]-'A']++;
    }
  }
//  dfs(0,0,0,0),dfs(0,0,0,1);
//  REP(i,52)REP(j,MAX_N) dp[i][j]=-Inf;
  int dp[55][MAX_N]={};
  ZERO(dp);
  dp[0][0]=1;
  REP(i,52)REP(j,MAX_N) if(dp[i][j]) {
    if(cnt[i]>0) {
      dp[i+1][j+cnt[i]]|=1;
      pre[i+1][j+cnt[i]].push_back(i);
    }
    dp[i+1][j]=1;
  }
  REPE(i,52) if(dp[i][N/2]&&SZ(pre[i][N/2])) {
    dump(i);
    dfs(1LL<<i,i,N/2);
  }
  dumpc(subset);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  cin>>S;
  N=SZ(S);
  solve();
  cin>>Q;
  REP(i,Q) {
    int x,y; cin>>x>>y;
    --x,--y;
    int c1=id(S[x]),c2=id(S[y]);
    if(c1>c2) swap(c1,c2);
    cout<<(CC*res[c1][c2]).val<<endl;
  }
  
  return 0;
}
