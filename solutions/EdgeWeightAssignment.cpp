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
vector<int> findCenter(vector<vector<int>> &G) {
  int N=G.size();
  vector<int> deg(N,0);
  queue<int> Q;
  for(int u=0; u<N; ++u) {
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
// $ cp-batch EdgeWeightAssignment | diff EdgeWeightAssignment.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EdgeWeightAssignment.cpp && ./a.out

/*
 
 4/12/2020
 
 8:07-9:10 WA
 10:00-10:14 fixed a bug and got AC
 
 https://codeforces.com/blog/entry/75913
 https://twitter.com/laycrs/status/1249369183738941440
 https://twitter.com/hanseilimak/status/1249933328674721799
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.4ps0ohu0py
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.i2tvvtc7fi8
 
 */

//const int MAX_N=1e6+1;
int N;

SETI ls;
VV<int> G;
int dup=0;
VI ds;
void dfs(int u, int pre, int d) {
  dump(u,d);
  int tot=0,cntl=0;
  FORR(v,G[u]) if(v!=pre) {
    ++tot;
    cntl+=ls.count(v);
    dfs(v,u,d+1);
  }
  if(tot==0) ds.push_back(d);
  if(cntl>=2) dup+=cntl-1;
}

void solve() {
  VI cs=findCenter(G);
  REP(i,N) if(SZ(G[i])==1) ls.emplace(i);
//  dump(cs[0]);
  dfs(cs[0],-1,0);
//  dfs(0,-1,0);
  
  bool alleven=1;
  FORR(d,ds) alleven&=(d%2==0);
  bool allodd=1;
  FORR(d,ds) allodd&=(d%2==1);
  
  /*if(N==3) {
    println("%d %d",1,1);
  } else if(count(ALL(ds),1)==SZ(ds)) {
    println("%d %d",1,1);
  } else */if(alleven||allodd) {
    println("%d %d",1,N-1-dup);
  } else {
    println("%d %d",3,N-1-dup);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  G=VV<int>(N);
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
  solve();
  
  return 0;
}
