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

// $ cp-batch Potions | diff Potions.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Potions.cpp && ./a.out

/*

 5/28/2021

 7:46-7:57 the small AC
 8:25 give up the hard
 9:00-9:36 WA

 15:30-16:40 read editorials and got AC

 https://codeforces.com/blog/entry/91195

 https://twitter.com/kzyKT_M/status/1398317299552063496
 https://twitter.com/n_vip/status/1398318402775621636
 https://twitter.com/laycrs/status/1398318855294840834

 */

const int MAX_N=1e6+1+1;
LL A[MAX_N];
int N;

void solve() {
  LL sum=0;
  priority_queue<LL, vector<LL>, greater<LL>> Q;
  REP(i,N) {
    sum+=A[i],Q.emplace(A[i]);
    while(sum<0&&SZ(Q)) {
      LL x=Q.top(); Q.pop();
      sum-=x;
    }
  }
  cout<<SZ(Q)<<endl;
}

vector<II> ps;
bool ok(int K) {
  set<int> take;
  REP(i,K) take.emplace(ps[i].second);
  LL sum=0;
  REP(i,N) {
    if(A[i]>=0||take.count(i)) sum+=A[i];
    if(sum<0) return false;
  }
  return true;
}

void solve_wa() {
  int ncnt=0;
  REP(i,N) if(A[i]<0) {
    ++ncnt;
    ps.emplace_back(A[i],i);
  }
  sort(ALL(ps)),reverse(ALL(ps));

  int good=0,bad=ncnt+1;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    bool res=ok(m);
    //dump(m,res);
    (res?good:bad)=m;
  }

  cout<<N-ncnt+good<<endl;
}

const LL Inf=1e17;
void solve_() {
  VV<LL> dp(N+1,vector<LL>(N+1));
  REPE(i,N)REPE(j,N) dp[i][j]=-Inf;
  dp[0][0]=0;
  REP(i,N)REPE(cnt,N) {
    SMAX(dp[i+1][cnt],dp[i][cnt]);
    LL x=dp[i][cnt]+A[i];
    if(x>=0) SMAX(dp[i+1][cnt+1],x);
  }
  int res=0;
  REPE(cnt,N) if(dp[N][cnt]>=0) res=cnt;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
