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

// $ cp-batch PalindromelessArrays | diff PalindromelessArrays.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PalindromelessArrays.cpp && ./a.out

/*
 
 4/18/2019
 
 15:26-15:40, 19:25-20:23 WA on test case #5
 20:30 give up
 
 4/19/2019
 
 10:00-10:45, 14:00-16:00 read editorials and got AC
 
 https://codeforces.com/blog/entry/66147
 http://drken1215.hatenablog.com/entry/2019/03/23/081500
 http://kmjp.hatenablog.jp/entry/2019/03/27/0900
 https://cinnamo-coder.hatenablog.com/entry/2019/03/23/025507
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,K;

vector<LL> B[2];

ModInt g1(int L) {
  VV<ModInt> dp(L,vector<ModInt>(2));
  dp[0][0]=0,dp[0][1]=K-1;
  REP(i,L-1) {
    dp[i+1][0]=dp[i][1];
    dp[i+1][1]=dp[i][0]*(K-1)+dp[i][1]*(K-2);
  }
  return dp[L-1][1];
}
ModInt g2(int L) {
  VV<ModInt> dp(L,vector<ModInt>(3));
  dp[0][0]=0,dp[0][1]=1,dp[0][2]=K-2;
  REP(i,L-1) {
    dp[i+1][0]=dp[i][1]+dp[i][2];
    dp[i+1][1]=dp[i][0]+dp[i][2];
    dp[i+1][2]=(dp[i][0]+dp[i][1])*(K-2)+dp[i][2]*(K-3);
  }
//  dump(dp[L-1][0],dp[L-1][2]);
  return dp[L-1][0]+dp[L-1][2];
}

ModInt f(vector<LL> A) {
  dumpc(A);
  vector<pair<LL,int>> X;
  int N=SZ(A);
  REP(i,N) {
    if(X.empty()||X.back().first!=A[i]) X.emplace_back(A[i],0);
    X.back().second++;
  }
  ModInt res(1);
  int M=SZ(X);
  dumpc(X);
  if(SZ(X)==1) {
    return X.front().first==-1?ModInt(K)*(ModInt(K-1).pow(X[0].second-1)):1;
  }
  REP(i,M) {
    if(X[i].first==-1) {
      if(i==0||i==M-1) res*=ModInt(K-1).pow(X[i].second);
      else if(X[i-1].first==X[i+1].first) res*=g1(X[i].second);
      else res*=g2(X[i].second);
    } else {
      if(X[i].second>1) return 0;
    }
  }
  dump(res);
  return res;
}

void solve() {
  REP(i,N) B[i%2].push_back(A[i]);
  ModInt res=f(B[0])*f(B[1]);
  cout<<res<<endl;
}

ModInt dp[MAX_N];
void solve_wrong() {
  dp[0]=1;
  REP(i,N) {
    if(A[i]!=-1) {
      dp[i+1]=(i>=2&&A[i-2]==A[i])?0:dp[i];
    } else {
      int d=i<2?0:1;
      if(i<N-2) {
        if(A[i+2]!=-1) d+=1;
      }
//      dump(i,d);
      dp[i+1]=dp[i]*ModInt(max(0,K-d));
    }
  }
  cout<<dp[N]<<endl;
}

int calc2(int len, int k){
  VV<int> dp(len+1,VI(2,0));
  dp[0][0] = 1;
  REP(i,len){
    dp[i+1][0] = (LL)dp[i][1]*(k-1)%MOD; //挟まれた数
    dp[i+1][1] = (dp[i][0]+(LL)dp[i][1]*(k-2)%MOD)%MOD; //その他
  }
  return (LL)dp[len][1]*(k-1)%MOD;
}
int calc3(int len, int k){
  VV<int> dp(len+1,VI(3,0));
  dp[0][0] = 1;
  REP(i,len){
    dp[i+1][0] = (dp[i][1]+(LL)dp[i][2]*(k-2)%MOD)%MOD; //左端の数
    dp[i+1][1] = (dp[i][0]+(LL)dp[i][2]*(k-2)%MOD)%MOD; //右端の数
    dp[i+1][2] = (dp[i][0]+dp[i][1]+(LL)dp[i][2]*(k-3)%MOD)%MOD; //その他の数
  }
  return (dp[len][0]+(LL)dp[len][2]*(k-2)%MOD)%MOD;
}

void test() {
  K=4;
  for(int l=2; l<=1e3; ++l) {
    //int a=calc2(l,K),b=g1(l).val;
    int a=calc3(l,K),b=g2(l).val;
    if(a!=b)dump(l,a,b);
    assert(a==b);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
