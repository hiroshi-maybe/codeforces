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
template <class T> struct RMQ {
public:
  T Inf;
  vector<T> A;
  int SIZE; // normalized size of original array
  T merge(T a, T b) { return min(a,b); }
  RMQ(int N, T Inf) : Inf(Inf) {
    this->SIZE=calcsize(N);
    this->A=vector<T>(2*SIZE,Inf);
  }
  // O(N) initialization
  RMQ(vector<T> &X, T Inf) : Inf(Inf) {
    this->SIZE=calcsize(X.size());
    this->A=vector<T>(2*SIZE,Inf);
    for(int i=0; i<X.size(); ++i) A[i+SIZE-1]=X[i];
    for(int i=SIZE-2; i>=0; --i) {
      A[i]=merge(A[2*i+1],A[2*i+2]);
    }
  }
  void update(int i, T v) {
    i+=SIZE-1;
    A[i]=v;
    while(i>0) {
      i=(i-1)/2;
      A[i]=merge(A[2*i+1],A[2*i+2]);
    }
  }
  // half-open range [ql,qr)
  T query(int ql, int qr) {
    return qu(ql,qr,0,0,SIZE);
  }
private:
  // i: node index (<SIZE if not leaf)
  T qu(int ql, int qr, int i, int l, int r) {
    if(qr<=l||r<=ql) return Inf;
    if(ql<=l&&r<=qr) return A[i];
    int m=(l+r)/2;
    
    return merge(qu(ql,qr,2*i+1,l,m),qu(ql,qr,2*i+2,m,r));
  }
  int calcsize(int N) {
    int n=1; while(n<N) n<<=1;
    return n;
  }
};
// $ cp-batch YetAnotherMonsterKillingProblem | diff YetAnotherMonsterKillingProblem.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address YetAnotherMonsterKillingProblem.cpp && ./a.out

/*
 
 11/13/2019
 
 7:38-8:26 AC
 
 https://codeforces.com/blog/entry/71434
 https://twitter.com/hanseilimak/status/1195852931519504384
 
 */

const int MAX_N=1e6+1;
int A[MAX_N],P[MAX_N],S[MAX_N];
int N,M;

const int Inf=1e7;
void solve() {
  VI XX(A,A+N),YY(N+1);
  REP(i,N)XX[i]=-XX[i];
  REP(i,M) SMIN(YY[S[i]],-P[i]);
//  dumpc(YY);
  RMQ<int> X(XX,0),Y(YY,0);
  int res=0,l=0;
  while(l<N) {
    int good=l,bad=N+1;
    while(abs(good-bad)>1) {
      int mid=(good+bad)/2;
      int maxa=-X.query(l,mid);
      int num=mid-l;
      int maxp=-Y.query(num,N+1);
      bool res=maxp>=maxa;
//      dump(res,mid,maxa,maxp);
      (res?good:bad)=mid;
    }
//    dump(l,good);
    if(good==l) {
      cout<<-1<<endl;
      return;
    }
    ++res,l=good;
  }
  cout<<res<<endl;
  /*
  VI dp(N+1,Inf);
  dp[0]=0;
  REP(i,N) {
    int good=N,bad=i;
    while(abs(good-bad)>1) {
      
    }
  }*/
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(_,T) {
    cin>>N;
    REP(i,N)cin>>A[i];
    cin>>M;
    REP(i,M)cin>>P[i]>>S[i];
    solve();
  }
  
  return 0;
}
