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

// $ cp-batch LunarNewYearAndARecursiveSequence | diff LunarNewYearAndARecursiveSequence.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LunarNewYearAndARecursiveSequence.cpp && ./a.out

/*
 
 2/15/2019
 
 17:44-18:25 give up

 This problem seemed to be matrix power problem (from recurrence relation of k-neighbored values).
 However I couldn't design powered matrix.
 
 2/17/2019
 
 10:00-11:45, 12:45-13:00 learn about baby-step giant step (discrete logarithm, discrete root)
 
 2/18/2019
 
 17:00-20:30, 21:00-24:00 learn about baby-step giant step (discrete logarithm, discrete root)
 
 2/19/2019
 
 10:00-12:30, 15:00-15:45 learn about Euler's theorem and multiplicative group
 15:45-17:00 enhance matrix library
 17:00-17:44 Finally I got AC!!! Libraries (ModInt, modroot, MX) worked like a charm.
 
 https://codeforces.com/blog/entry/64928
 http://kmjp.hatenablog.jp/entry/2019/02/01/0930
 https://naoyat.hatenablog.jp/entry/CodeforcesRound536Div2
 
 https://twitter.com/pazzle1230/status/1090995447638806528
 https://twitter.com/n_vip/status/1090998428622962689
 https://twitter.com/satanic0258/status/1090995066712219648
 https://twitter.com/satanic0258/status/1091003998604128256
 https://twitter.com/satanic0258/status/1091013452938698753
 
 https://cp-algorithms.com/algebra/discrete-root.html
 https://cp-algorithms.com/algebra/primitive-root.html
 https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a#7-%E5%B9%B3%E6%96%B9%E5%89%B0%E4%BD%99-a
 
 */

int MOD=998244353;
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

template <typename T> struct MX {
  int N,M;
  vector<vector<T>> dat;
  MX(int N, int M) : N(N), M(M) {
    assert(N>0&&M>0);
    dat=vector<vector<T>>(N, vector<T>(M, 0));
  }
  MX(vector<vector<T>> &d) : dat(d) {
    assert(dat.size()>0&&dat[0].size()>0);
    N=dat.size(),M=dat[0].size();
  }
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
  void debug() {
    cerr<<N<<"x"<<M<<endl;
    for(int i=0; i<N; ++i) {
      for(int j=0; j<M; ++j) {
        cerr<<dat[i][j]<<",";
      }
      cerr<<endl;
    }
  }
private:
  // O(N^2) time
  vector<vector<T>> add(vector<vector<T>> &A, vector<vector<T>> &B) {
    assert(A.size()==B.size()&&A[0].size()==B[0].size());
    int N=A.size(),M=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(N,vector<T>(M));
    for(int i=0; i<N; ++i) {
      for(int j=0; j<M; ++j) {
        res[i][j]=A[i][j]+B[i][j];
      }
    }
    return res;
  }
  // O(N^3) time
  vector<vector<T>> mult(vector<vector<T>> &A, vector<vector<T>> &B) {
    assert(A[0].size()==B.size());
    int NN=A.size(),MM=B[0].size(),L=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(NN,vector<T>(MM));
    for(int i=0; i<NN; ++i) {
      for(int j=0; j<MM; ++j) {
        for(int k=0; k<L; ++k) {
          res[i][j]+=A[i][k]*B[k][j];
        }
      }
    }
    return res;
  }
  vector<vector<T>> mult(vector<vector<T>> &A, T k) {
    int N=A.size(),M=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(N,vector<T>(M));
    for(int i=0; i<N; ++i) {
      for(int j=0; j<M; ++j) {
        res[i][j]=k*A[i][j];
      }
    }
    return res;
  }
};

int powmod(int _a, int b, int MOD) {
  long long a=_a;
  long long res=1;
  for(int mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a,res%=MOD;
    a*=a,a%=MOD;
  }
  return (int)res;
}
int modlog(int a, int b, int MOD) {
  int sqrtM=(int)sqrt(MOD+.0)+1;
  long long ga=powmod(a,sqrtM,MOD);
  unordered_map<int, int> G;
  long long cur=ga;
  for(int p=1; p<=sqrtM; ++p) {
    if(!G.count(cur)) G[cur]=p;
    cur=cur*ga%MOD;
  }
  int res=MOD+10;
  cur=b;
  for(int q=0; q<=sqrtM; ++q) {
    if(G.count(cur)) {
      res=min(res,G[cur]*sqrtM-q);
    }
    cur=cur*a%MOD;
  }
  if(res>MOD) res=-1;
  if(res>=0) assert(powmod(a,res,MOD)==b);
  return res;
}

int primitiveroot(int M) {
  auto totient=[&](int n)->int {
    int res=n;
    for(int p=2; p*p<=n; ++p) if(n%p==0) {
      res=res/p*(p-1);
      while(n%p==0) n/=p;
    }
    if(n!=1) res=res/n*(n-1);
    return res;
  };
  
  vector<int> P;
  int phi=totient(M),n=phi;
  for(int i=2; i*i<=n; ++i) if(n%i==0) {
    P.push_back(i);
    while (n%i==0) n/=i;
  }
  if(n>1) P.push_back(n);
  for(int res=2; res<=M; ++res) {
    bool ok = true;
    for (int i=0; i<P.size()&&ok; ++i) ok&=powmod(res,phi/P[i],M)!=1;
    if(ok) return res;
  }
  return -1;
}
int modroot(int k, int a, int MOD) {
  if(a==0) return 0;
  function<int(int,int)> gcd=[&](int a, int b)->int { return b==0?a:gcd(b,a%b); };
  int g=primitiveroot(MOD);
  int y=modlog(powmod(g,k,MOD),a,MOD);
  if(y==-1) return -1;
  
  assert(powmod(powmod(g,y,MOD),k,MOD)==a);
  int x=powmod(g,y,MOD);
  assert(powmod(x,k,MOD)==a);
  
  return x;
  /*
   cout<<x<<endl;
   int delta=(MOD-1)/gcd(k,MOD-1);
   vector<int> res;
   for(int cur=x%delta; cur<MOD-1; cur+=delta) res.push_back(powmod(g,cur,MOD));
   sort(res.begin(),res.end());
   return res;*/
}

const int MAX_K=1e2+1;
int B[MAX_K];
int K,N,M;

void solve() {
  MOD--;
  
  MX<ModInt> X0(K,1); X0.dat[0][0]=ModInt(1);
  MX<ModInt> A(K,K);
  REP(i,K) A.dat[0][i]=B[i];
  REP(i,K-1) A.dat[i+1][i]=1;
  MX<ModInt> X=A.pow(N-K)*X0;
  int hn=X.dat[0][0].val;
  
  MOD++;
  
  int res=modroot(hn,M,MOD);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>K;
  REP(i,K) cin>>B[i];
  cin>>N>>M;
  solve();
  
  return 0;
}
