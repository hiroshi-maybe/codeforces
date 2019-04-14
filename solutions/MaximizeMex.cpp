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

// $ cp-batch MaximizeMex | diff MaximizeMex.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MaximizeMex.cpp && ./a.out

/*
 
 4/12/2019
 
 9:25-10:16 give up
 
 We need to choose each bucket at most once for P[i] from 0 to make mex.
 To satisfy the condition, I imagined to solve by dp or graph. However I didn't have further idea...
 
 4/14/2019
 
 11:45-13:30 read editorials and got AC

 https://codeforces.com/blog/entry/66101
 https://cinnamo-coder.hatenablog.com/entry/2019/03/22/024140
 https://twitter.com/ei1333/status/1108784170220707840
 https://twitter.com/n_vip/status/1108785061459943424
 https://twitter.com/kyort0n/status/1108785880653651968
 
 This problem can be reduced to graph problem.
 It's easy to add edges instead of removing edges. Let's look at queries backward.
 
 Condition:
  - Potential `p` <-> set of clubs (as long as student remains)
  - One club is chosen for a potential `p`
  - One club cannot be chosen twice
 
 Unknown: max mex
 
 We form bipartite graph with clubs C (left) and potentials P (right).
 However general maximum matching may not guarantee max mex.
 We cannot miss `x` to achieve mex K (0<=x<=K).
 Thus we can make matching from 0 to K to maximize mex.
 If we cannot make it, we've got maximum mex.
 
 */

const int MAX_V=101010;
template<class V> class Dinic {
public:
  void addEdge(int from, int to, V cap) {
    E[from].push_back((Edge){  to, (int)E[  to].size()  , cap});
    E[  to].push_back((Edge){from, (int)E[from].size()-1,   0}); // cancellation edge in residual graph
  }
  
  V maxFlow(int s, int t) {
    V res=0;
    while(true) {
      bfs(s);
      if(dist[t]<0) return res; // t is unreachable
      memset(iter,0,sizeof(iter));
      V f;
      while((f=dfs(s,t,Inf))>0) res+=f;
    }
    
    return res;
  }
private:
  const V Inf=numeric_limits<V>::max();
  struct Edge { int to, rev; V cap; };
  vector<Edge> E[MAX_V]; // Graph
  int dist[MAX_V]; // distance from `s`
  int iter[MAX_V];
  
  // initialize shoftest path and store in `level`
  void bfs(int s) {
    memset(dist,-1,sizeof(dist));
    
    queue<int> Q;
    dist[s]=0;
    Q.push(s);
    
    while(Q.size()) {
      int u=Q.front(); Q.pop();
      
      for(int i=0; i<E[u].size(); ++i) {
        Edge &e=E[u][i];
        int v=e.to;
        if(e.cap<=0) continue;
        if(dist[v]>=0) continue; // visited
        
        dist[v]=dist[u]+1;
        Q.push(v);
      }
    }
  }
  
  // find augmenting path in residual network and update f
  V dfs(int u, int t, V f) {
    if(u==t) return f;
    for(int &i=iter[u]; i<E[u].size(); ++i) { // visit E[u] only once
      Edge &e=E[u][i];
      int v=e.to;
      if(e.cap<=0) continue;
      if(dist[u]>=dist[v]) continue;
      
      V d=dfs(v,t,min(f,e.cap));
      if(d<=0) continue;
      e.cap-=d;
      E[v][e.rev].cap+=d; // cancellation increases
      return d;
    }
    
    return 0;
  }
};

const int MAX_N=1e4+1;
int P[MAX_N],C[MAX_N],K[MAX_N];
int N,M,Q;

void solve() {
  int S=0,T=1e4+10,base=5001;
  Dinic<int> D;
  REP(i,M) D.addEdge(S,1+i,1);
  D.addEdge(base,T,1);
  VI rem(N+1,0);
  REP(i,Q) rem[K[i]-1]=1;
  REP(i,N) if(!rem[i]) D.addEdge(C[i],base+P[i],1);
  VI res(Q+1,0);
  for(int i=Q-1; i>=0; --i) {
    res[i]=res[i+1];
    while(int x=D.maxFlow(S,T)) {
      ++res[i],D.addEdge(base+res[i],T,1);
//      dump(i,res[i],x);
    }
    int j=K[i]-1;
    D.addEdge(C[j],base+P[j],1);
  }
  REP(i,Q) println("%d",res[i]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>P[i];
  REP(i,N) cin>>C[i];
  cin>>Q;
  REP(i,Q) cin>>K[i];
  solve();
  
  return 0;
}
