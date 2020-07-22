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

// $ cp-batch Unmerge | diff Unmerge.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Unmerge.cpp && ./a.out

/*

 7/21/2020

 8:37-9:49 WA
 21:31-21:44 transform input to pure subset-sum and got AC
 22:10 found a bug in the original code, fixed it and got AC

 https://codeforces.com/blog/entry/80427
 https://twitter.com/hanseilimak/status/1285983918760460288

 */

const int MAX_N=2010+1;
int P[MAX_N*2];
int N,L;

bool solve() {
  L=2*N;
  vector<II> xs={{P[0],1}};
  FOR(i,1,L) {
    if(P[i]>xs.back().first) xs.emplace_back(P[i],0);
    xs.back().second++;
  }

  int M=SZ(xs);
  VI A(M); REP(i,M) A[i]=xs[i].second;
  VI dp(N+1,0);
  dp[0]=1;
  REP(i,M) for(int cnt=N; cnt>=0; --cnt) {
    if(cnt+A[i]<=N) dp[cnt+A[i]]|=dp[cnt];
  }

  return dp[N];
}

bool dp[MAX_N*2][2][MAX_N*2];
bool solve_org() {
  L=2*N;
  VI ps(L,0);
  int maxp=P[0];
  FOR(i,1,L) {
    if(P[i]>maxp) ps[i]=1;
    SMAX(maxp,P[i]);
  }

  REPE(i,L)REP(j,2)REPE(k,L) dp[i][j][k]=0;
  dp[0][0][0]=1;
  REP(i,L) REP(j,2) REP(cnt,L) {
    //if(dp[i][j][cnt]) dump(i,j,cnt,dp[i][j][cnt]);
    if(i<L-1&&ps[i+1]&&i-cnt>=0) {
      dp[i+1][j^1][i-cnt]|=dp[i][j][cnt];
    }
    dp[i+1][j][cnt+1]|=dp[i][j][cnt];
  }
  //dump(dp[6][1][3]);
  //REPE(i,N) dump(i,dp[L][0][i],dp[L][1][L-i]);
  return dp[L][0][N]||dp[L][1][N];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N*2) cin>>P[i];
    cout<<(solve()?"YES":"NO")<<endl;
  }

  return 0;
}
