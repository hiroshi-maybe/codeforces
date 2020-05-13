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

// $ cp-batch OracAndLCM | diff OracAndLCM.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address OracAndLCM.cpp && ./a.out

/*
 
 5/12/2020
 
 5:55-6:13 AC
 
 https://codeforces.com/blog/entry/77284
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

LL power(LL x, LL n) {
  LL res=1;
  while(n>0) {
    if(n&1) res*=x;
    x*=x,n>>=1;
  }
  return res;
}
map<LL,int> primeFactors(LL n) {
  assert(n>=1);
  map<LL,int> res;
  for(LL p=2; p*p<=n; ++p) while(n%p==0) {
    res[p]++;
    n/=p;
  }
  if(n>1) res[n]++;
  return res;
}
void solve() {
  map<LL,VI> pcnts;
  REP(i,N) {
    LL a=A[i];
    auto ps=primeFactors(a);
    FORR(kvp,ps) pcnts[kvp.first].push_back(kvp.second);
  }
  LL res=1;
  FORR(kvp,pcnts) {
    LL p=kvp.first;
    VI cnts=kvp.second;
    
    LL n=0;
    if(SZ(cnts)<N-1) n=0;
    else if(SZ(cnts)==N-1) n=*min_element(ALL(cnts));
    else {
      sort(ALL(cnts));
      n=cnts[1];
    }
    res*=power(p,n);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
