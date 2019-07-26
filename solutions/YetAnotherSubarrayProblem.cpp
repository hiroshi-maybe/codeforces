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

// $ cp-batch YetAnotherSubarrayProblem | diff YetAnotherSubarrayProblem.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address YetAnotherSubarrayProblem.cpp && ./a.out

/*
 
 7/25/2019
 
 13:40-14:20 give up
 
 15:30-15:47, 16:30-18:05, 20:10-21:35 read editorial
 
 7/26/2019
 
 8:15-9:55 read editorials and got AC

 http://tsutaj.hatenablog.com/entry/2019/07/23/194446
 https://codeforces.com/blog/entry/68615
 https://twitter.com/hanseilimak/status/1154793006353903621
 
 Tons of analysis that I could not figure out by myself 😞
 Formula transformation with cum[0..l] and cum[0..r] is typical way I couldn't reach. If this comes up, moving right boundary makes sense.
 Finding M window step from the formula was also what I couldn't find.
 
 Key:
  - brute-force right end
  - formula transformation to leverage cumulative sum
  - (r-l)/M makes M window of equal cost
  - M window makes M monotonic groups
   - we can remember only minimum in each group because K increases monotonically
   - we need to remember minimum of all M groups because each group can be updated in different index
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N],cum[MAX_N];
LL K;
int N,M;

const LL Inf=1e18;
void solve() {
  REP(i,N) cum[i+1]=cum[i]+A[i];
  vector<LL> mins(M,Inf);
  LL res=0;
  REP(i,N) {
    mins[i%M]=min(mins[i%M]+K,cum[i]+K);
    REP(m,M) SMAX(res,cum[i+1]-mins[m]);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>K;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
