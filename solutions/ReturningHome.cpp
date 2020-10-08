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

// $ cp-batch ReturningHome | diff ReturningHome.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ReturningHome.cpp && ./a.out

/*

 10/4/2020

 9:54-11:01 AC

 https://twitter.com/hanseilimak/status/1314090732316061698
 https://codeforces.com/blog/entry/83452

 https://twitter.com/kzyKT_M/status/1312816379024662528
 https://twitter.com/laycrs/status/1312816623384838144
 https://twitter.com/n_vip/status/1312816870085390336

 */

const int MAX_N=1e5+10;
II P[MAX_N];
int N,M;

const long long Inf=2e18;
const int MAX_V=MAX_N;
long long D[MAX_V];
using Edge=pair<long long, int>;
vector<Edge> G[MAX_V];
void dijkstra(int V, int st) {
  for(int i=0; i<V; ++i) D[i]=Inf;
  priority_queue<Edge,vector<Edge>,greater<Edge>> Q; Q.emplace(0,st); D[st]=0;
  while(Q.size()>0) {
    long long d; int u;
    tie(d,u)=Q.top(),Q.pop();
    if(d!=D[u]) continue;
    for(auto p : G[u]) {
      int v; long long w; tie(w,v)=p;
      if(d+w<D[v]) D[v]=d+w,Q.emplace(d+w,v);
    }
  }
}

void solve() {
  vector<II> xs,ys;
  REP(i,M) xs.emplace_back(P[i].first,i),ys.emplace_back(P[i].second,i);
  sort(ALL(xs)),sort(ALL(ys));

  for(auto &xs : {xs,ys}) {
    REP(i,SZ(xs)-1) {
      auto u=xs[i],v=xs[i+1];
      G[u.second].emplace_back(abs(v.first-u.first),v.second);
      G[v.second].emplace_back(abs(v.first-u.first),u.second);
    }
  }
  auto ps=P[M],pe=P[M+1];
  auto mdist=[&](II p1, II p2) -> LL { return (LL)abs(p1.first-p2.first)+(LL)abs(p1.second-p2.second); };
  G[M].emplace_back(mdist(ps,pe),M+1);
  dump(mdist(ps,pe));
  REP(i,M) {
    auto p=P[i];
    LL d=min(abs(ps.first-p.first),abs(ps.second-p.second));
    G[M].emplace_back(d,i);
  }
  REP(i,M) {
    auto p=P[i];
    G[i].emplace_back(mdist(p,pe),M+1);
  }

  dijkstra(M+5,M);
  cout<<D[M+1]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  cin>>P[M].first>>P[M].second>>P[M+1].first>>P[M+1].second;
  REP(i,M) cin>>P[i].first>>P[i].second;
  solve();

  return 0;
}
