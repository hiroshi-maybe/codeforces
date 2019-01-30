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

// $ cp-batch MinimalDiameterForest | diff MinimalDiameterForest.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MinimalDiameterForest.cpp && ./a.out

/*
 
 1/28/2019
 
 11:14-11:55 WA on test case #6 (corner case without any edges)
 12:02 got AC
 
 https://codeforces.com/blog/entry/63961
  - center is a vertex `u` where dist(u,a)=D/2 and dist(u,b)=D-D/2 (a and b are leaves which form diameter)
 http://tsutaj.hatenablog.com/entry/2018/12/28/134816
  - center is a vertex `u` which minimizes max(dist(u,a),dist(u,b)) (a and b are leaves which form diameter)
 
 */

const int MAX_N=1e3+1;
VV<int> G;
int N,M;

/*
void dfsdfs(int u, int pre, int d, VVI &G, VI &D) {
  D[u]=d;
  for(auto v: G[u]) if(v!=pre) dfsdfs(v,u,d+1,G,D);
};*/
int compDiameter(vector<vector<int>> &G, int u=0) {
  int N=G.size();
  vector<int> D(N,0);
  
  function<void(int,int,int)> dfs=[&](int u, int pre, int d) -> void {
    D[u]=d;
    for(auto v: G[u]) if(v!=pre) dfs(v,u,d+1);
  };
  dfs(u,-1,0);
  int a=max_element(D.begin(),D.end())-D.begin();
  
  D=vector<int>(N,0);
  dfs(a,-1,0);
  int b=max_element(D.begin(),D.end())-D.begin();;
  
  // (a,b) is pair of vertices which form diameter
  //  printf("%d-%d: %d\n",a,b,D[b]);
  return D[b];
}

vector<int> findCenter(vector<vector<int>> &G, set<int> &S) {
  int N=G.size();
  vector<int> deg(N,0);
  queue<int> Q;
  for(int u: S) {
    int x=G[u].size();
    deg[u]=x;
    if(x<=1) Q.emplace(u);
  }
  int d=0;
  vector<int> res;
  while(Q.size()) {
    int L=Q.size();
    res=vector<int>();
    while(L--) {
      int u=Q.front(); Q.pop();
      res.emplace_back(u);
      --deg[u];
      for(auto v : G[u]) {
        --deg[v];
        if(deg[v]==1) Q.emplace(v);
      }
    }
    ++d;
  }
  assert(1<=res.size()&&res.size()<=2);
  return res;
}

int viz[MAX_N];

void dfs(int u, int pre, VI &vs) {
  if(viz[u]) return;
  viz[u]=1;
  vs.push_back(u);
  FORR(v,G[u]) if(v!=pre) dfs(v,u,vs);
}

void solve() {
  ZERO(viz);
  vector<II> cs;
  REP(u,N) if(!viz[u]) {
    VI vs; dfs(u,-1,vs);
    set<int> S(ALL(vs));
    int d=compDiameter(G,u);
    VI c=findCenter(G,S);
    cs.emplace_back(d,c.front());
  }
  sort(cs.rbegin(),cs.rend());
  int c=cs.front().second;
  
  vector<II> res;
  FOR(i,1,SZ(cs)) {
    int u,d; tie(d,u)=cs[i];
    res.emplace_back(c,u);
    G[u].push_back(c);
    G[c].push_back(u);
  }
  println("%d",compDiameter(G));
  REP(i,SZ(res)) println("%d %d",res[i].first+1,res[i].second+1);
}

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " = " << a << endl;
  err(++it, args...);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  G=VV<int>(N);
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  solve();
  
  return 0;
}
