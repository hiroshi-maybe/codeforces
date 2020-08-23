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

// $ cp-batch ColoredRectangles | diff ColoredRectangles.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ColoredRectangles.cpp && ./a.out

/*

 8/14/2020

 7:54-8:06 WA
 8:33 AC

 https://codeforces.com/blog/entry/81506

 */

const int MAX_N=200+1;
int r[MAX_N],g[MAX_N],b[MAX_N];
int R,G,B;

LL dp[MAX_N][MAX_N][MAX_N];
void solve() {
  sort(r,r+R),reverse(r,r+R);
  sort(g,g+G),reverse(g,g+G);
  sort(b,b+B),reverse(b,b+B);

  LL res=0;
  ZERO(dp);
  REPE(i,R)REPE(j,G)REPE(k,B) {
    SMAX(res,dp[i][j][k]);
    if(i<R&&j<G) SMAX(dp[i+1][j+1][k],dp[i][j][k]+r[i]*g[j]);
    if(j<G&&k<B) SMAX(dp[i][j+1][k+1],dp[i][j][k]+g[j]*b[k]);
    if(i<R&&k<B) SMAX(dp[i+1][j][k+1],dp[i][j][k]+r[i]*b[k]);
  }
  cout<<res<<endl;
}

void solve_wrong() {
  vector<priority_queue<int>> Q(3);
  REP(i,R) Q[0].emplace(r[i]);
  REP(i,G) Q[1].emplace(g[i]);
  REP(i,B) Q[2].emplace(b[i]);

  LL res=0;
  const int Inf=1e8;
  while(true) {
    vector<II> xs(3);
    REP(i,3) {
      xs[i]={SZ(Q[i])?Q[i].top():-Inf,i};
    }
    sort(xs.rbegin(),xs.rend());
    if(xs[1].first==-Inf&&xs[2].first==-Inf) break;
    res+=xs[0].first*xs[1].first;
    REP(i,2) Q[xs[i].second].pop();
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>R>>G>>B;
  REP(i,R) cin>>r[i];
  REP(i,G) cin>>g[i];
  REP(i,B) cin>>b[i];
  solve();

  return 0;
}
