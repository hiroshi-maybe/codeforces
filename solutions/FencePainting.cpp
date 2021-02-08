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

// $ cp-batch FencePainting | diff FencePainting.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address FencePainting.cpp && ./a.out

/*

 2/5/2021

 7:12-7:40 AC

 https://codeforces.com/blog/entry/87523

 */

const int MAX_N=1e6+1;
int A[MAX_N],B[MAX_N],C[MAX_N];
int N,M;

void solve() {
  VV<int> xs(N+2);
  int lastp=-1;
  REP(i,N) {
    if(A[i]!=B[i]) {
      if(B[i]==C[M-1]) lastp=i;
      xs[B[i]].emplace_back(i);
    }
  }

  if(lastp==-1) {
    REP(i,N) if(B[i]==C[M-1]) lastp=i;
  } else xs[C[M-1]].pop_back();

  if(lastp==-1) {
    cout<<"NO"<<endl;
    return;
  }

  VI res(M);
  res[M-1]=lastp;
  for(int i=M-2; i>=0; --i) {
    int c=C[i];
    if(xs[c].empty()) res[i]=lastp;
    else res[i]=xs[c].back(),xs[c].pop_back();
  }
  FORE(i,1,N) if(SZ(xs[i])) {
    cout<<"NO"<<endl;
    return;
  }

  VI as(A,A+N),bs(B,B+N);
  REP(i,M) as[res[i]]=C[i];
  //dumpc(res);
  //dumpc(as);
  //dumpc(bs);
  assert(as==bs);

  cout<<"YES"<<endl;
  REP(i,M) cout<<res[i]+1<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>M;
    REP(i,N) cin>>A[i];
    REP(i,N) cin>>B[i];
    REP(i,M) cin>>C[i];
    solve();
  }

  return 0;
}
