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

// $ cp-batch KoaAndTheBeach | diff KoaAndTheBeach.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address KoaAndTheBeach.cpp && ./a.out

/*

 7/24/2020

 7:54-8:21 give up

 7/26/2020

 16:05-17:40 read editorials and B1 is accepted by DP
 19:05 AC after reading editorials
 19:25 complete proof

 https://twitter.com/hanseilimak/status/1287549312545640448
 https://codeforces.com/blog/entry/80562?#comment-668606

 */

const int MAX_N=1e6+1;
LL D[MAX_N],L;
int N,K;

LL f(int t) {
  int tt=t%(2*K);
  if(tt<K) return tt%(2*K);
  else return K-(t%K);
}
LL dep(int i, int t) {
  return D[i]+f(t);
}

bool solve() {
  VI safe;
  REP(i,N+2) if(D[i]+K<=L) safe.push_back(i);

  REP(i,SZ(safe)-1) {
    int l=safe[i]+1,r=safe[i+1]-1;
    //dump(i,l,r);
    LL tide=K,down=true;
    FORE(j,l,r) {
      tide+=down?-1:1;
      if(down) {
        LL delta=max(0LL, D[j]+tide-L);
        tide-=delta;
        if(tide<0) return false;
        if(tide==0) down=false;
      } else {
        if(D[j]+tide>L) return false;
      }
      //dump(j,tide,D[j]+tide,down);
    }
  }

  return true;
}

bool solve_small() {
  VV<int> dp(N+2,VI(2*K,0));
  dp[0][0]=1;
  REP(i,N+1)REP(j,2*K) {
    int jj=(j+1)%(2*K);
    if(dep(i+1,jj)<=L) dp[i+1][jj]|=dp[i][j];
    if(dep(i,jj)<=L) dp[i][jj]|=dp[i][j];
    //dump(i,j,dp[i][j]);
  }

  bool res=false;
  REP(i,2*K) res|=dp[N+1][i];
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>K>>L;
    D[0]=D[N+1]=-K;
    REP(i,N) cin>>D[i+1];
    cout<<(solve()?"Yes":"No")<<endl;
  }

  return 0;
}
