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

// $ cp-batch BeautifulRegionalContest | diff BeautifulRegionalContest.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BeautifulRegionalContest.cpp && ./a.out

/*
 
 12/5/2019
 
 6:52-7:27 AC
 
 https://codeforces.com/blog/entry/71995
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void solve() {
  vector<LL> res(3,0);
  vector<pair<int,LL>> X;
  REP(i,N) {
    if(X.empty()||X.back().first!=A[i]) X.emplace_back(A[i],0);
    X.back().second++;
  }
  if(SZ(X)<3) {
    println("0 0 0");
    return;
  }
  
  int M=SZ(X);
  vector<LL> cum(M+1,0);
  REP(i,M) cum[i+1]=cum[i]+X[i].second;
  res[0]=X[0].second;
  int k=0;
  REPE(i,M)if(cum[i]*2<=N) k=i;
    
  FOR(i,1,M) {
    LL a=cum[i]-cum[1],b=cum[k]-cum[i];
    if(a>res[0]&&b>res[0]) {
      res[1]=a,res[2]=b;
      break;
    }
  }
  if(res[1]<=res[0]||res[2]<=res[0]||accumulate(ALL(res),0LL)*2>N) {
    println("0 0 0");
    return;
  }
//  dumpc(res);
  assert(res[1]>res[0]);
  assert(res[2]>res[0]);

  println("%lld %lld %lld",res[0],res[1],res[2]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(_,T) {
    cin>>N;
    REP(i,N)cin>>A[i];
    solve();
  }
  
  return 0;
}
