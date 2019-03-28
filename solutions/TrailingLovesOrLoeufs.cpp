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

// $ cp-batch TrailingLovesOrLoeufs | diff TrailingLovesOrLoeufs.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TrailingLovesOrLoeufs.cpp && ./a.out

/*
 
 3/27/2019
 
 15:11-15:33 WA on test case #7
 15:52 give up
 16:55-17:03 AC after fixing overflow. fuck.
 
 https://codeforces.com/blog/entry/65136
 
 */

LL N,B;

LL f(pair<LL,int> pii) {
  LL cnt=0;
  LL p=pii.first;
  /*
  while(p<=N) {
    cnt+=N/p;
    // overflow. fuck.
    double x=(double)p*pii.first;
    if(x>1e18) break;
    p*=pii.first;
  }*/
  LL n=N;
  while(n>0) cnt+=n/p,n/=p;
//  dump(pii.first,pii.second,cnt);
  cnt/=pii.second;
//  dump(pii.first,pii.second,cnt);
  return cnt;
}
void solve() {
  vector<LL> ps;
  LL b=B;
  map<LL,int> M;
  for(LL p=2; p*p<=b; ++p) if(b%p==0) {
    while(b%p==0) b/=p,M[p]++;
  }
  if(b>1) M[b]++;
  const LL Inf=1e18;
  LL res=Inf;
  FORR(kvp,M) SMIN(res,f(kvp));
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>B;
  solve();
  
  return 0;
}
