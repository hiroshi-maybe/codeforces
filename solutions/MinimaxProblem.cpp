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

// $ cp-batch MinimaxProblem | diff MinimaxProblem.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MinimaxProblem.cpp && ./a.out

/*
 
 1/14/2020
 
 8:22-8:35 give up
 
 1/18/2020
 
 12:50-14:10 read editorials
 
 https://codeforces.com/blog/entry/73105
 https://twitter.com/hanseilimak/status/1218651314894209024
 
 */

const int MAX_N=1e6+1,MAX_M=10;
int A[MAX_N][MAX_M];
int N,M;

II f(int x) {
  VI cnt(1<<M,-1);
  REP(i,N) {
    int mask=0;
    REP(j,M) mask|=((A[i][j]>=x)<<j);
    cnt[mask]=i;
  }
  int fmask=(1<<M)-1;
  REP(a,1<<M) REP(b,1<<M) if(cnt[a]>=0&&cnt[b]>=0) {
    if((a|b)<fmask) continue;
    return {cnt[a],cnt[b]};
  }
  return {-1,-1};
}

void solve() {
  int good=0,bad=1e9+1;
  while(abs(good-bad)>1) {
    int mid=(good+bad)/2;
    II res=f(mid);
    (res.first>=0?good:bad)=mid;
  }
  II res=f(good);
  println("%d %d", res.first+1,res.second+1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N)REP(j,M) cin>>A[i][j];
  solve();
  
  return 0;
}
