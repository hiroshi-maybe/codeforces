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

// $ cp-batch 505 | diff 505.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address 505.cpp && ./a.out

/*

 8/9/2020

 8:44-9:19 WA
 9:35 give up

 8/10/2020

 9:35-10:11 AC

 https://twitter.com/hanseilimak/status/1292872110772117509
 https://codeforces.com/blog/entry/81265

 https://twitter.com/laycrs/status/1292500328156262400?s=20
 https://twitter.com/kzyKT_M/status/1292499828606304256?s=20

 */

const int MAX_N=1e6+1;
string A[MAX_N];
int N,M;

const LL Inf=1e18;
LL dp[MAX_N][1<<3];
bool ith(int mask, int i) { return (mask>>i)&1; }
void solve() {
  VV<int> X;
  if(N>M) {
    X=VV<int>(M,VI(N,-1));
    REP(j,M)REP(i,N) X[j][i]=A[i][j]-'0';
    swap(N,M);
  } else {
    X=VV<int>(N,VI(M,-1));
    REP(i,N)REP(j,M) X[i][j]=A[i][j]-'0';
  }
  if(N==1||N>=4) {
    cout<<(N>=4?-1:0)<<endl;
    return;
  }

  set<II> oks;
  REP(mask,1<<N)REP(mask2,1<<N) {
    bool ok=true;
    for(int i=0; i+1<N; ++i) {
      int cnt=0;
      REP(o,2) cnt+=ith(mask,i+o)+ith(mask2,i+o);
      ok&=(cnt%2)!=0;
    }
    if(ok) oks.emplace(mask,mask2);
  }

  REP(i,M) REP(mask,1<<N) dp[i][mask]=Inf;
  REP(mask,1<<N) {
    dp[0][mask]=0;
    REP(i,N) if(ith(mask,i)!=X[i][0]) {
      dp[0][mask]++;
    }
  }

  REP(i,M-1)REP(mask1,1<<N) {
    REP(mask2,1<<N) if(oks.count({mask1,mask2})) {
      LL cnt=dp[i][mask1];
      REP(j,N) cnt+=(X[j][i+1]!=ith(mask2,j));
      SMIN(dp[i+1][mask2],cnt);
    }
  }
  LL res=Inf;
  REP(mask,1<<N) SMIN(res,dp[M-1][mask]);
  cout<<res<<endl;
}

void solve_wrong() {
  VV<int> X;
  if(N>M) {
    X=VV<int>(M,VI(N,-1));
    REP(j,M)REP(i,N) X[j][i]=A[i][j]-'0';
    swap(N,M);
  } else {
    X=VV<int>(N,VI(M,-1));
    REP(i,N)REP(j,M) X[i][j]=A[i][j]-'0';
  }
  //dump(N,M);
  // N<=M
  if(N==1||N>=4) {
    cout<<-1<<endl;
    return;
  }

  VV<int> P1={
    {0,0,1,1},
    {0,1,1,0},
    {1,1,0,0},
    {1,0,0,1}
  };
  VV<int> P2={
    {1,1,0,0},
    {0,1,1,0},
    {0,0,1,1},
    {1,0,0,1}
  };

  int res=N*M;
  REP(offi,4)REP(offj,4) {
    int ans1=0,ans2=0;
    REP(i,N)REP(j,M) {
      ans1+=X[i][j]!=P1[(i+offi)%4][(j+offj)%4];
      ans2+=X[i][j]!=P2[(i+offi)%4][(j+offj)%4];
    }
    SMIN(res,ans1);
    SMIN(res,ans2);
  }

  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
