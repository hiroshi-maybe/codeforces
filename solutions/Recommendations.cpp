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

// $ cp-batch Recommendations | diff Recommendations.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Recommendations.cpp && ./a.out

/*
 
 2/23/2020
 
 8:59-9:35 WA
 9:47 WA
 10:16 AC
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N],T[MAX_N];
int N;

void solve() {
  map<LL,vector<pair<LL,LL>>> X;
  REP(i,N) X[A[i]].emplace_back(T[i],A[i]);
  vector<LL> B;
  FORR(kvp,X) {
    sort(kvp.second.rbegin(),kvp.second.rend());
    B.push_back(kvp.first);
  }
  const LL Inf=1e10;
  B.push_back(Inf);
  dumpc(B);
  int M=SZ(B);
  LL res=0;
  priority_queue<pair<LL,LL>> Q;
  REP(i,M-1) {
    auto ts=X[B[i]];
    FORR(t,ts) Q.emplace(t);
    dump(i,B[i],SZ(Q),min(B[i+1]-B[i],(LL)SZ(Q)));
    LL cnt=min(B[i+1]-B[i],(LL)SZ(Q));
    for(LL j=0; j<cnt; ++j) {
      LL pos=B[i]+j;
      auto p=Q.top(); Q.pop();
      res+=(pos-p.second)*p.first;
      dump(j,pos,p.first,p.second,res);
    }
  }
  assert(SZ(Q)==0);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N) cin>>T[i];
  solve();
  
  return 0;
}
