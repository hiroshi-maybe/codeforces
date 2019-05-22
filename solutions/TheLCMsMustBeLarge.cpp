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

// $ cp-batch TheLCMsMustBeLarge | diff TheLCMsMustBeLarge.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheLCMsMustBeLarge.cpp && ./a.out

/*
 
 5/17/2019
 
 9:53-10:20 give up
 
 5/22/2019
 
 11:20-13:00 read editorial and got AC
 
 https://codeforces.com/blog/entry/67081
 https://twitter.com/ajis_ka/status/1129433902253129728
 https://twitter.com/armeria_betrue/status/1129434461391560704
 https://twitter.com/armeria_betrue/status/1129436259011649537
 https://twitter.com/risujiroh/status/1129433096070213634
 
 Proof: https://twitter.com/tempura_cpp/status/1129438544525578240
 
 Problem is not asking to construct => Elements in a solution is huge
 
 The first step is noticing necessary condition from observation.
 
   If D[i] and D[j] are disjoint, impossible to construct A.
 
 Summary:
  - Think about explicit impossible condition which is necessary condition
  - It's typical to prove that necessary condition is sufficient by constructing steps
 
 */

const int MAX_N=50+1;
VI X[MAX_N];
int N,M;

void solve() {
  bool ok=true;
  REP(j,M) REP(i,j) {
    bitset<100000> S,T;
    REP(k,SZ(X[i])) S[X[i][k]]=1;
    REP(k,SZ(X[j])) T[X[j][k]]=1;
    
    int a=(S&T).count();
    ok&=a>0;
  }
  cout<<(ok?"possible":"impossible")<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>M>>N;
  REP(i,M) {
    int K; cin>>K;
    X[i].resize(K);
    REP(j,K) cin>>X[i][j];
  }
  solve();
  
  return 0;
}
