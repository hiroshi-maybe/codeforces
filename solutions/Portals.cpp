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

// $ cp-batch Portals | diff Portals.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Portals.cpp && ./a.out

/*
 
 12/15/2019
 
 2:13-3:25 give up
 17:40-19:00 read contestant's solutions and got AC

 https://twitter.com/hanseilimak/status/1206411130718937090
 https://codeforces.com/contest/1271/submission/66946806 by @scott_wu
 https://codeforces.com/contest/1271/submission/66949829 by @betrue12
 
 */

const int MAX_N=5000+1;
int A[MAX_N],B[MAX_N],C[MAX_N];
int N,K;

VI G[MAX_N],X[MAX_N];
int dp[MAX_N][MAX_N];
const int Inf=1e9;
void solve() {
  REP(i,MAX_N)REP(j,MAX_N)dp[i][j]=-Inf;
  dp[0][K]=0;
  VI last(N); REP(i,N)last[i]=i;
  REP(u,N)FORR(v,G[u]) SMAX(last[u],v);
  REP(u,N)X[last[u]].push_back(u);
  REP(i,N){
    FOR(k,A[i],MAX_N) if(dp[i][k]>=0&&k+B[i]<MAX_N) dp[i+1][k+B[i]]=dp[i][k];
//    dump(i);
//    dumpc(X[i]);
    FORR(v,X[i]) REP(k,MAX_N) if(dp[i+1][k]>=0) {
      SMAX(dp[i+1][k-1],dp[i+1][k]+C[v]);
    }
  }
  int res=-1;
  REP(k,MAX_N) SMAX(res,dp[N][k]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int M; cin>>N>>M>>K;
  REP(i,N) cin>>A[i]>>B[i]>>C[i];
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[v].push_back(u);
  }
  solve();
  
  return 0;
}
