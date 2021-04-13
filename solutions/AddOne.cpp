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
template <typename T> struct MX {
  int N,M;
  MX(int N, int M) : N(N), M(M) {
    assert(N>0&&M>0);
    dat=vector<vector<T>>(N, vector<T>(M, 0));
  }
  MX(vector<vector<T>> &d) : dat(d) {
    assert(dat.size()>0&&dat[0].size()>0);
    N=dat.size(),M=dat[0].size();
  }
  inline vector<T>& operator [] (int i) {return dat[i]; }
  MX<T> &operator+=(MX<T> that) { dat=add(dat,that.dat); return *this; }
  MX<T> &operator-=(MX<T> that) { that*=-1,dat=add(dat,that.dat); return *this; }
  MX<T> &operator*=(MX<T> that) { dat=mult(dat,that.dat); return *this; }
  MX<T> &operator*=(T k) { dat=mult(dat,k); return *this; }
  MX<T> operator + (const MX<T> &that) const { return MX<T>(*this)+=that; }
  MX<T> operator - (const MX<T> &that) const { return MX<T>(*this)-=that; }
  MX<T> operator * (const MX<T> &that) const { return MX<T>(*this)*=that; }
  MX<T> operator * (const T &k) const { return MX<T>(*this)*=k; }
  bool operator==(MX<T> that) const { return dat==that.dat; }
  bool operator!=(MX<T> that) const { return dat!=that.dat; }
  // res = A^n, O(N^3*lg n) time
  MX<T> pow (long long n) const {
    assert(N==M);
    MX<T> res(N,N); for(int i=0; i<N; ++i) res.dat[i][i]=1;
    MX<T> a=MX<T>(*this);
    while(n>0) {
      if(n%2) res*=a;
      a*=a,n>>=1;
    }
    return res;
  }
  T det() {
    assert(N==M);
    T res=1;
    MX B(N,N);
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) B[i][j] = (*this)[i][j];
    for(int i=0; i<N; ++i) for(int j=i+1; j<N; ++j) {
      for (; B[j][i]!=0; res=-res) {
        T tm=B[i][i]/B[j][i];
        for(int k=i; k<N; ++k) {
          T t = B[i][k]-tm*B[j][k];
          B[i][k]=B[j][k];
          B[j][k]=t;
        }
      }
      res*=B[i][i];
    }
    return res;
  }
  MX inverse() {
    assert(N==N);
    MX B(N,2*N);
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) B[i][j] = (*this)[i][j];
    for(int i=0; i<N; ++i) B[i][N+i]=1;
    for(int i=0; i<N; ++i) {
      int pivot = i;
      for(int j=i; j<N; ++j) if(B[j][i]!=B[pivot][i]) pivot=j;
      assert(B[pivot][i]!=0); // regular?
      swap(B[i],B[pivot]);
      for(int j=i+1; j<=2*N; ++j) B[i][j]/=B[i][i];
      for(int j=0; j<N; ++j) if(i!=j) for(int k=i+1; k<=2*N; ++k) {
        B[j][k] -= B[j][i] * B[i][k];
      }
    }
    MX res(N,N);
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) res[i][j]=B[i][N+j];
    return res;
  }
  friend ostream& operator<<(ostream& os, const MX<T>& that) {
    for(int i=0; i<that.N; ++i) for(int j=0; j<that.M; ++j) os<<that.dat[i][j]<<",\n"[j==that.M-1];
    return os;
  }
private:
  vector<vector<T>> dat;
  // O(N^2) time
  vector<vector<T>> add(vector<vector<T>> &A, vector<vector<T>> &B) {
    assert(A.size()==B.size()&&A[0].size()==B[0].size());
    int N=A.size(),M=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(N,vector<T>(M));
    for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) res[i][j]=A[i][j]+B[i][j];
    return res;
  }
  // O(N^3) time
  vector<vector<T>> mult(vector<vector<T>> &A, vector<vector<T>> &B) {
    assert(A[0].size()==B.size());
    int NN=A.size(),MM=B[0].size(),L=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(NN,vector<T>(MM));
    for(int i=0; i<NN; ++i) for(int j=0; j<MM; ++j) for(int k=0; k<L; ++k) res[i][j]+=A[i][k]*B[k][j];
    return res;
  }
  vector<vector<T>> mult(vector<vector<T>> &A, T k) {
    int N=A.size(),M=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(N,vector<T>(M));
    for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) res[i][j]=k*A[i][j];
    return res;
  }
};
const int MOD=1000000007;
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

// $ cp-batch AddOne | diff AddOne.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AddOne.cpp && ./a.out

/*

 4/11/2021

 8:21-9:13 TLE
 9:32 TLE. give up, read solutions and got AC

 https://codeforces.com/blog/entry/89550
 https://twitter.com/kzyKT_M/status/1381284807724867588

 */

const int MAX_N=2e5+10;
int N,M;
vector<MX<ModInt>> pows;

ModInt dp[10][MAX_N][10];
ModInt A[10][MAX_N];
void solve() {
  VI cnt(10);
  while(N>0) cnt[N%10]++,N/=10;
  //REP(i,SZ(s)) cnt[s[i]-'0']++;

  ModInt res;
  //REP(i,10)REP(j,10) res+=dp[i][M][j]*cnt[i];
  REP(i,10) res+=A[i][M]*cnt[i];
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  /*
  MX<ModInt> mx(10,10);
  FOR(i,1,10) mx[i][i-1]=1;
  mx[0][9]=mx[1][9]=1;
  //pows.reserve(MAX_N);
  //pows.push_back(mx);
  //FOR(i,1,MAX_N) pows.push_back(pows.back()*mx);
  dump(mx);
  auto p2=mx.pow(2);
  dump(p2);
  auto p10=mx.pow(10);
  dump(p10);
  auto p100=mx.pow(100);
  dump(p100);*/

  REP(st,10) {
    dp[st][0][st]=1;
    REP(i,MAX_N-1) {
      REP(j,10) dp[st][i+1][j]=0;
      REP(j,9) dp[st][i+1][j+1]+=dp[st][i][j];
      dp[st][i+1][0]+=dp[st][i][9];
      dp[st][i+1][1]+=dp[st][i][9];
    }
    REP(i,MAX_N)REP(j,10) A[st][i]+=dp[st][i][j];
  }

  int t; cin>>t;
  while(t--) {
    cin>>N>>M;
    solve();
  }

  return 0;
}
