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

// $ cp-batch LinkCutCentroids | diff LinkCutCentroids.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LinkCutCentroids.cpp && ./a.out

/*

 9/12/2020

 7:14-7:48 AC

 https://codeforces.com/blog/entry/82560
 https://twitter.com/hanseilimak/status/1304957358347448322

 https://twitter.com/kzyKT_M/status/1304808460408614913
 https://twitter.com/laycrs/status/1304808439915278336

 */

vector<int> findCentroids(vector<vector<int>> G) {
  int N=G.size();
  vector<int> cnt(N);
  vector<int> res;
  auto dfs=[&](auto &&self, int u, int p) -> void {
    cnt[u]=1;
    bool ok=true;
    for(auto v: G[u]) if(p!=v) {
      self(self,v,u);
      cnt[u]+=cnt[v];
      ok&=cnt[v]<=N/2;
    }
    ok&=N-cnt[u]<=N/2;
    if(ok) res.push_back(u);
  };
  dfs(dfs,0,-1);
  return res;
}

int N;
VV<int> G;
void solve() {
  auto cs=findCentroids(G);
  assert(SZ(cs)>0);
  vector<II> res;
  if(SZ(cs)==1) {
    assert(SZ(G[0])>0);
    res.emplace_back(0,G[0].back());
    res.emplace_back(0,G[0].back());
  } else {
    int c=cs[0];
    FORR(v,G[c]) if(v!=cs[1]) {
      res.emplace_back(c,v);
      res.emplace_back(cs[1],v);
      break;
    }
  }
  assert(SZ(res)==2);
  FORR(p,res) cout<<p.first+1<<" "<<p.second+1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N;
    G.resize(N);
    REP(i,N) G[i].clear();
    REP(i,N-1) {
      int u,v; cin>>u>>v;
      --u,--v;
      G[u].push_back(v),G[v].push_back(u);
    }
    solve();
  }

  return 0;
}
