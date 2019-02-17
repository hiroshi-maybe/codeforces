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

// $ cp-batch LunarNewYearAndRedEnvelopes | diff LunarNewYearAndRedEnvelopes.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LunarNewYearAndRedEnvelopes.cpp && ./a.out

/*
 
 2/15/2019
 
 12:57-13:43 AC
 
 https://codeforces.com/blog/entry/64928
 http://kmjp.hatenablog.jp/entry/2019/02/01/0900
 https://naoyat.hatenablog.jp/entry/CodeforcesRound536Div2
 https://twitter.com/satanic0258/status/1090994482634358784
 
 */

const int MAX_N=1e5+1;
LL W[MAX_N];
int S[MAX_N],T[MAX_N],D[MAX_N];
int N,M,K;

const LL Inf=1e17;
LL dp[MAX_N+10][210];
int X[MAX_N];
void solve() {
  map<int,VI> Y;
  REP(i,K) {
    Y[S[i]].push_back(i);
  }
  priority_queue<tuple<LL,int,int>> Q;
  MINUS(X);
  FORE(t,1,N) {
    FORR(i,Y[t]) {
      Q.emplace(W[i],D[i],i);
    }
    while(SZ(Q)) {
      int i; tie(ignore,ignore,i)=Q.top();
      if(T[i]<t) Q.pop();
      else break;
    }
    if(SZ(Q)) X[t]=get<2>(Q.top());
  }
  
  REPE(i,N+1)REPE(j,M) dp[i][j]=Inf;
  dp[1][0]=0;
  FORE(t,1,N)REPE(m,M) {
    if(X[t]<0) {
      SMIN(dp[t+1][m],dp[t][m]);
    } else {
      int k=X[t];
      SMIN(dp[D[k]+1][m],dp[t][m]+W[k]);
      if(m<M) SMIN(dp[t+1][m+1],dp[t][m]);
    }
  }
  LL res=Inf;
  REPE(m,M) SMIN(res,dp[N+1][m]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>K;
  REP(i,K) {
    cin>>S[i]>>T[i]>>D[i]>>W[i];
  }
  solve();
  
  return 0;
}
