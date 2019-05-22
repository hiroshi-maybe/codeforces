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

// $ cp-batch CuteSequences | diff CuteSequences.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CuteSequences.cpp && ./a.out

/*
 
 5/17/2019
 
 9:07-9:53 AC
 
 https://codeforces.com/blog/entry/67081
 
 */

//const int MAX_N=1e6+1;
//LL A[MAX_N];
LL A,B,M;

void solve() {
  vector<LL> X;
  X.push_back(A);
  LL cur=A;
  while(cur+1<=B) {
    X.push_back(cur+1);
    cur=2LL*cur+1;
  }
  dumpc(X);
  int N=SZ(X);
  vector<LL> Y(N,1);
  LL D=B-X.back();
  assert(D>=0);
  LL d=min(D,M-1);
  Y[N-1]+=d,D-=d;
  FOR(i,1,N-1) {
    LL a=1LL<<(N-2-i);
    dump(i,a);
    LL y=min(M-1,D/a);
    Y[i]=1+y,D-=a*y;
  }
  dumpc(Y);
  if(D>0) {
    println("-1");
  } else {
    LL cur=X.front();
    FOR(i,1,N) {
      X[i]=cur+Y[i];
      cur=2LL*cur+Y[i];
    }
    dumpc(X);
    assert(X[N-1]==B);
    printf("%d ",N);
    FORR(x,X)    printf("%lld ",x);
    println("");
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int Q;
  cin>>Q;
  REP(i,Q) {
    cin>>A>>B>>M;
    solve();
  }
  
  return 0;
}
