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
      A[i]=max(A[2*i+1],A[2*i+2]);
    }
  }
  void update(int i, T v) {
    i+=SIZE-1;
    A[i]=v;
    while(i>0) {
      i=(i-1)/2;
      A[i]=max(A[2*i+1],A[2*i+2]);
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
    
    return max(qu(ql,qr,2*i+1,l,m),qu(ql,qr,2*i+2,m,r));
  }
  int calcsize(int N) {
    int n=1; while(n<N) n<<=1;
    return n;
  }
};
// $ cp-batch SubarraySorting | diff SubarraySorting.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SubarraySorting.cpp && ./a.out

/*
 
 6/30/2019
 
 9:20-9:55 MLE
 10:00 WA on #31
 10:08 AC
 
 https://codeforces.com/blog/entry/68111
 
 smaller value never goes beyond larger value. This is necessary condition.
 If above proposition is true, we can restore A from B by sort of two consecutive elements.
 
 */

const int MAX_N=3e5+1;
int A[MAX_N], B[MAX_N];
int N;

queue<int> pos[MAX_N];
int X[MAX_N];
set<int> S;
bool solve() {
  S.clear();
  REP(i,N) {
    int a=A[i];
    pos[a].push(i);
    S.emplace(a);
  }
  REP(i,N) {
    int b=B[i];
    if(pos[b].empty()) return false;
    int j=pos[b].front(); pos[b].pop();
    X[j]=i;
  }
  RMQ<int> rmq(N,-1);
  REP(i,N) {
    int a=A[i];
    int maxp=rmq.query(1,a);
    int myp=X[i];
    if(maxp>myp) return false;
    rmq.update(a,myp);
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  while(T--) {
    cin>>N;
    REP(i,N) cin>>A[i];
    REP(i,N) cin>>B[i];
    cout<<(solve()?"YES":"NO")<<endl;
    FORR(a,S) pos[a]=queue<int>();
  }
  
  return 0;
}
