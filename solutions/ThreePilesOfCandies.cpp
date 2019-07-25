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

// $ cp-batch ThreePilesOfCandies | diff ThreePilesOfCandies.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ThreePilesOfCandies.cpp && ./a.out

/*
 
 7/24/2019
 
 16:10-16:27 AC
 
 https://codeforces.com/blog/entry/68642
 https://codeforces.com/blog/entry/68655
 
 */

//const int MAX_N=1e6+1;
LL A[3];

bool ith(int i, int mask) {
  return (mask>>i)&1;
}
LL dfs(int t, int mask, LL a, LL b) {
  if(__builtin_popcount(mask)==2) {
    LL rest=0;
    REP(i,3) if(!ith(i,mask)) {
      rest=A[i];
    }
    LL dif=min(abs(a-b),rest);
    if(a>b) b+=dif,rest-=dif;
    else a+=dif,rest-=dif;
    if(rest) a+=rest/2,b+=rest/2;
//    assert(a==b);
    return min(a,b);
  }
  LL res=0;
  REP(i,3) if(!ith(i,mask)) {
    if(t==0) SMAX(res,dfs(t+1,mask|(1<<i),a+A[i],b));
    else SMAX(res,dfs(t+1,mask|(1<<i),a,b+A[i]));
  }
  return res;
}
void solve() {
//  sort(A,A+3);
  LL res=dfs(0,0,0,0);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int Q; cin>>Q;
  while(Q--) {
    REP(j,3) cin>>A[j];
    solve();
  }
  
  return 0;
}
