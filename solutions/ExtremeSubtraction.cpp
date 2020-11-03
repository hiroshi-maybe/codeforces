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

// $ cp-batch ExtremeSubtraction | diff ExtremeSubtraction.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ExtremeSubtraction.cpp && ./a.out

/*

 11/2/2020

 6:35-7:29 give up
 20:30-22:30 read tweets and got AC

 https://twitter.com/hanseilimak/status/1323512866016694272
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.b0paukjtieqx

 https://codeforces.com/blog/entry/84298

 https://twitter.com/drken1215/status/1323304125564551168
 https://twitter.com/Rubikun_pro/status/1323306439658463232
 https://twitter.com/kzyKT_M/status/1323303535191060480
 https://twitter.com/Cinnamon_VR/status/1323303362561892352
 https://twitter.com/n_vip/status/1323303364722003968
 https://twitter.com/ngtkana/status/1323303927920537600
 https://twitter.com/laycrs/status/1323304091108343813
 https://twitter.com/drken1215/status/1323304125564551168

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

bool solve() {
  VI B(N);
  FOR(i,1,N) B[i]=A[i]-A[i-1];
  VI imos(N,0);
  REP(i,N) {
    if(B[i]>0) imos[i]-=B[i];
    else if(B[i]<0) imos[0]+=B[i],imos[i]-=B[i];
  }
  //dumpc(B);
  //dumpc(imos);
  int cur=0;
  REP(i,N) cur+=imos[i],A[i]+=cur;
  //dumpC(A,A+N);
  return A[0]>=0;
}

bool solve_editorial() {
  VI xs(N),ys(N);
  xs[0]=A[0],ys[0]=0;
  FOR(i,1,N) {
    xs[i]=min(xs[i-1],A[i]-ys[i-1]);
    ys[i]=A[i]-xs[i];
    if(xs[i]<0||ys[i]<ys[i-1]) return false;
  }
  /*
  dumpC(A,A+N);
  dumpc(xs);
  dumpc(ys);*/
  return true;
}

bool solve_wrong() {
  VI as={A[0]};
  FOR(i,1,N) if(A[i]!=A[i-1]) as.push_back(A[i]);

  int N=SZ(as);
  if(N<=2) return true;

  int l=1,r=N-2;
  while(l<N&&as[l-1]>as[l]) ++l;
  while(r>=0&&as[r+1]>as[r]) --r;
  //dump(l,r);
  if(r<l) return true;
  if(l==r&&(as[l-1]+as[r+1]>=as[l])) return true;
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N) cin>>A[i];
    cout<<(solve()?"YES":"NO")<<endl;
  }

  return 0;
}
