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

// $ cp-batch PaintTheTree | diff PaintTheTree.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PaintTheTree.cpp && ./a.out

/*
 
 10/6/2019
 
 9:54-10:10 give up
 
 10/13/2019
 
 15:05-16:05 AC
 
 https://codeforces.com/blog/entry/70358
 
 If child is not paited by the same color, f(v,0) is free.
 If child is taken by the same color, delta = f(v,1)+w(u,v)-f(v,0) is obtained.
 We can take K or K-1 children. Greedily taking largest deltas gives optimal solution.
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int Q,N,K;

LL memo[MAX_N][2];
vector<pair<LL,int>> G[MAX_N];
LL f(int u, bool taken, int pre) {
  LL &res=memo[u][taken];
  if(res>=0) return res;
  res=0;
  vector<LL> ds;
  FORR(p,G[u]) if(p.second!=pre) {
    int v=p.second; LL w=p.first;
    LL notake=f(v,false,u),take=f(v,true,u)+w;
    res+=notake;
    if(take-notake>0)ds.push_back(take-notake);
  }
  sort(ALL(ds)),reverse(ALL(ds));
  int KK=min(K-taken,SZ(ds));
  res+=accumulate(ds.begin(),ds.begin()+KK,0LL);
  return res;
}
void solve() {
  REP(i,N)REP(j,2) memo[i][j]=-1;
  LL res=max(f(0,0,-1),f(0,1,-1));
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>Q;
  REP(i,Q) {
    cin>>N>>K;
    REP(j,N) G[j].clear();
    REP(j,N-1) {
      int u,v; LL w; cin>>u>>v>>w;
      --u,--v;
      G[u].emplace_back(w,v);
      G[v].emplace_back(w,u);
    }
    solve();
  }
  
  return 0;
}
