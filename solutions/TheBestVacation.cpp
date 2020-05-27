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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch TheBestVacation | diff TheBestVacation.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheBestVacation.cpp && ./a.out

/*

 5/26/2020

 9:20-9:59 WA
 21:34-21:35 AC after fixing an overflowing bug

 */

const int MAX_N=1e6+1;
LL D[MAX_N],A[MAX_N],X;
int N;

LL cum1[MAX_N],cum2[MAX_N];
void solve() {
  LL res=0;
  REP(i,2*N) A[i]=D[i%N]*(D[i%N]+1)/2,D[i]=D[i%N];
  reverse(A,A+2*N),reverse(D,D+2*N);
  REP(i,2*N) cum2[i+1]=cum2[i]+A[i],cum1[i+1]=cum1[i]+D[i];
  dumpC(D,D+2*N);
  dumpC(cum1,cum1+2*N+1);
  dumpC(cum2,cum2+2*N+1);
  REP(i,2*N) {
    int j=upper_bound(cum1,cum1+2*N+1,cum1[i]+X)-cum1;
    if(j>2*N) continue;
    if(j<=0) continue;
    LL ans=cum2[j-1]-cum2[i];
    LL rem=X-(cum1[j-1]-cum1[i]);
    LL d=D[j-1];
    ans+=rem*(d+d-rem+1)/2;
    //dump(i,j,cum2[j-1]-cum2[i],rem);
    SMAX(res,ans);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>X;
  REP(i,N) cin>>D[i];
  solve();

  return 0;
}
