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

// $ cp-batch GuessTheRoot | diff GuessTheRoot.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GuessTheRoot.cpp && ./a.out

/*
 
 4/22/2019
 
 9:44-10:00 give up
 
 5/6/2019
 
 22:55-23:20 give up
 
 5/7/2019
 
 17:40-18:30 read editorials and got AC
 19:36 add solution by Gaussian Elimination
 
 https://codeforces.com/blog/entry/66687
 https://cinnamo-coder.hatenablog.com/entry/2019/04/23/165615
 https://twitter.com/tempura_cpp/status/1120365894507450369
 https://twitter.com/satanic0258/status/1120368263710380035
 https://en.wikipedia.org/wiki/Lagrange_polynomial
 https://mathtrain.jp/hokan

 Gauss Jordan elimination
  - https://twitter.com/xuzijian629/status/1120365688344862720
  - https://codeforces.com/contest/1155/submission/53153675
 
 */
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

const int MOD=1000003;
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
template <typename T> struct GaussJordanElimination2 {
  vector<T> solve(MX<T> A, vector<T> b) {
    const int N=A.N;
    MX<T> X(N,N+1); // Augmented matrix which merges A with b
    for(int i=0; i<N; ++i) {
      for(int j=0; j<N; ++j) X[i][j]=A[i][j];
      X[i][N]=b[i];
    }
    
    for(int i=0; i<N; ++i) {
      // invariant: X[p][p]=1 for p=0..i-1
      int pivot=i;
      for(int j=i; j<N; ++j) {
        // find maximum coefficient to minimize precision error
        if (X[j][i]!=X[pivot][i]) pivot=j;
      }
      // solution is undeterministic, or no solution exists
      if(X[pivot][i]==0) return vector<T>();
      swap(X[i],X[pivot]);
      // X[i][i]=1
      for(int j=i+1; j<=N; ++j) X[i][j]/=X[i][i];
      for(int j=0; j<N; ++j) if(i!=j) {
        // row reduction
        for(int k=i+1; k<=N; ++k) X[j][k]-=X[j][i]*X[i][k];
      }
    }
    vector<T> xs(N);
    for(int i=0; i<N; ++i) xs[i]=X[i][N];
    return xs;
  }
};

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

int ask(int x) {
  cout<<"? "<<x<<endl;
  int res; cin>>res;
  return res;
}

void answer(int x) {
  cout<<"! "<<x<<endl;
  exit(0);
}

void solve() {
  MX<ModInt> A(11,11);
  vector<ModInt> B(11);
  REP(i,11) {
    int y=ask(i+1);
    REP(j,11) A[i][j]=ModInt(i+1).pow(j);
    B[i]=y;
  }
  if(A.det()==0) answer(-1);
  GaussJordanElimination2<ModInt> GE;
  vector<ModInt> as=GE.solve(A,B);
//  dumpc(as);
  REP(x,MOD) {
    ModInt y;
    REP(i,11) y+=as[i]*ModInt(x).pow(i);
    if(y==0) answer(x);
  }
  answer(-1);
}

void solve_lagrange() {
  vector<II> X;
  REP(i,11) {
    int y=ask(i+1);
    X.emplace_back(i+1,y);
  }
  vector<ModInt> B(11);
  REP(i,11) {
    ModInt rev(1);
    REP(j,11) if(i!=j) rev*=ModInt(X[i].first-X[j].first);
    B[i]=ModInt(X[i].second)/rev;
  }
  REP(x,MOD) {
    ModInt y;
    REP(i,11) {
      ModInt xx(1);
      REP(j,11) if(i!=j) xx*=x-X[j].first;
      y+=xx*B[i];
    }
    if(y==0) answer(x);
  }
  answer(-1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  solve();
  
  return 0;
}
