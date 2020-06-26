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

// $ cp-batch MaximumSumOnEvenPositions | diff MaximumSumOnEvenPositions.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MaximumSumOnEvenPositions.cpp && ./a.out

/*

 6/25/2020

 8:35-10:00 solve by dp after the contest

 6/26/2020

 10:00-10:30 add a solution by cumulative sum

 https://twitter.com/hanseilimak/status/1276574967388270593
 https://codeforces.com/blog/entry/79376
 https://codeforces.com/contest/1373/submission/85019650
  - beautiful solution by @betrue12

 https://twitter.com/tsutaj/status/1276199543890079744
 https://twitter.com/n_vip/status/1276201449190354944
 https://twitter.com/kuuso1/status/1276200779292921857
 https://twitter.com/kyort0n/status/1276199875068088321
 https://twitter.com/laycrs/status/1276195547959812097
 https://twitter.com/kzyKT_M/status/1276192329271963648

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void solve() {
  LL base=0;
  REP(i,N) if(i%2==0) base+=A[i];
  LL mx=0,sum=0;
  LL mn[2]={0,0};
  REP(i,N) {
    sum+=i%2==0?-A[i]:A[i];
    SMAX(mx,sum-mn[i%2]);
    SMIN(mn[i%2],sum);
  }
  cout<<base+mx<<endl;
}

LL f(vector<LL> bs) {
  int N=SZ(bs);
  LL cur=0,mn=0,res=0;
  REP(i,N) {
    cur+=bs[i];
    SMAX(res,cur-mn);
    SMIN(mn,cur);
  }
  //dumpc(bs);
  //dump(res);
  return res;
}

void solve_mucumsum() {
  LL base=0;
  REP(i,N) if(i%2==0) base+=A[i];
  vector<LL> bs;
  REP(i,N/2) bs.push_back(A[2*i+1]-A[2*i]);
  LL res=base;
  //dump(base);
  SMAX(res,base+f(bs));
  bs.clear();
  FORE(i,1,(N-1)/2) bs.push_back(A[2*i-1]-A[2*i]);
  SMAX(res,base+f(bs));
  cout<<res<<endl;
}

const LL Inf=1e18;
LL dp[MAX_N][4];
void solve_dp() {
  REPE(i,N)REP(j,4) dp[i][j]=-Inf;
  dp[0][0]=dp[0][2]=dp[0][3]=0;
  REP(i,N) REP(j,4) {
    if(j==0) {
      if(i%2==0) {
        SMAX(dp[i+1][j],dp[i][j]+A[i]);
        SMAX(dp[i+1][1],dp[i][j]+A[i]);
      } else {
        SMAX(dp[i+1][j],dp[i][j]);
        SMAX(dp[i+1][2],dp[i][j]);
      }
    }
    if(j==1||j==2) {
      if(i%2==0) {
        SMAX(dp[i+1][j],dp[i][j]);
        if(j==1)SMAX(dp[i+1][3],dp[i][j]);
      } else {
        SMAX(dp[i+1][j],dp[i][j]+A[i]);
        if(j==2)SMAX(dp[i+1][3],dp[i][j]+A[i]);
      }
    }
    if(j==3) {
      if(i%2==0) {
        SMAX(dp[i+1][j],dp[i][j]+A[i]);
      } else {
        SMAX(dp[i+1][j],dp[i][j]);
      }
    }
  }

  LL res=0;
  if(N%2==0) dp[N][1]=-Inf;
  REP(j,4) {
    //dump(j,dp[N][j]);
    SMAX(res,dp[N][j]);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N) cin>>A[i];
    solve();
  }

  return 0;
}
