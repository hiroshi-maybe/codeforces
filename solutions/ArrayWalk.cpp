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

// $ cp-batch ArrayWalk | diff ArrayWalk.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ArrayWalk.cpp && ./a.out

/*

 7/29/2020

 7:42-8:14 WA
 8:40 AC

 https://codeforces.com/blog/entry/80809
 https://twitter.com/hanseilimak/status/1290149834582679552

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,K,Z;

LL dp[MAX_N][10][2];
void solve() {
  dp[0][0][0]=A[0];
  REPE(j,Z)REP(rok,2)for(int i=N; i>=0; --i) {
    SMAX(dp[i+1][j][1],dp[i][j][rok]+A[i+1]);
    if(i>0&&rok) SMAX(dp[i-1][j+1][0],dp[i][j][rok]+A[i-1]);
  }

  LL res=0;
  REP(i,N)REPE(j,Z)REP(rok,2) {
    dump(i,j,rok,dp[i][j][rok]);
    if(rok&&i+2*j<=K) SMAX(res,dp[i][j][rok]);
    else if(!rok&&i+2*j<=K) SMAX(res,dp[i][j][rok]);
  }
  cout<<res<<endl;
}

void solve_greedy() {
  LL res=0;
  int p=0;
  LL sum=0;
  REP(i,N) if(i<=K) {
    sum+=A[i];
    if(i>0) {
      if(A[p]+A[p+1]<A[i-1]+A[i]) p=i-1;
    }

    LL ans;
    if((K-i)%2==0) {
      int z=(K-i)/2;
      if(z>Z) continue;
      if(z<0) continue;
      ans=sum+(A[p]+A[p+1])*z;
    } else {
      if(i<1) continue;
      if(K-i+1<2) continue;
      int z=(K-i+1)/2;
      if(z>Z||z<0) continue;
      ans=sum+A[i-1]*z+A[i]*(z-1);
    }
      //dump(i,z,sum,p,ans);
      SMAX(res,ans);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>K>>Z;
    REP(i,N) cin>>A[i];
    solve();
  }

  return 0;
}
