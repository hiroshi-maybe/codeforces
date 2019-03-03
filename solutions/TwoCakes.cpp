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

// $ cp-batch TwoCakes | diff TwoCakes.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TwoCakes.cpp && ./a.out

/*
 
 2/24/2019
 
 7:58-8:16 AC
 
 https://codeforces.com/blog/entry/65520
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

LL dp[MAX_N][2];
// dp
void solve_org() {
  vector<II> X(2*N);
  REP(i,2*N)X[i]={A[i],i};
  sort(ALL(X));
//  dumpc(X);
  
  const LL Inf=1e17;
  REPE(i,N)REP(j,2) dp[i][j]=Inf;
  dp[0][0]=dp[0][1]=0;
  REP(i,N)REP(j,2) {
    int pre[2]={i==0?0:X[2*(i-1)+j].second,i==0?0:X[2*(i-1)+(1-j)].second};
    REP(k,2) {
      int cur[2]={X[2*i+k].second,X[2*i+(1-k)].second};
      SMIN(dp[i+1][k],dp[i][j]+abs(cur[0]-pre[0])+abs(cur[1]-pre[1]));
//      dump(i,j,k,dp[i+1][k]);
    }
  }
  cout<<min(dp[N][0],dp[N][1])<<endl;
}
void solve() {
  vector<II> X(2*N);
  REP(i,2*N)X[i]={A[i],i};
  sort(ALL(X));
  
  LL res=0;
  int a=0,b=0;
  REP(i,N) {
    int c=X[2*i].second,d=X[2*i+1].second;
    res+=min(abs(b-c)+abs(d-a),abs(d-b)+abs(c-a));
    a=c,b=d;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,2*N) cin>>A[i];
  solve();
  
  return 0;
}
