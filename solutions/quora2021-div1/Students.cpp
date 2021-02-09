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

class MaxBipartiteMatching {
public:
  MaxBipartiteMatching(int V) : V(V) {
    E=VV<int>(V);
    match=VI(V,-1);
    viz=VI(V);
  }

  void addEdge(int u, int v) {
    assert(u<V&&v<V);
    E[u].push_back(v);
    E[v].push_back(u);
  }

  int solve() {
    int res=0;
    for(int u=0; u<V; ++u) if(match[u]<0) {
      viz=VI(V);
      res+=dfs(u);
    }

    return res;
  }
private:
  int V;
  VV<int> E;
  VI match;
  VI viz;

  // find augmenting path in residual network
  bool dfs(int u) {
    viz[u]=true;
    for(auto v : E[u]) {
      int w=match[v];
      if(w<0||(!viz[w]&&dfs(w))) {
        match[v]=u;
        match[u]=v;
        return true;
      }
    }
    return false;
  }
};

// $ cp-batch Students | diff Students.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Students.cpp && ./a.out

/*

 2/6/2021

 7:58-8:36 WA
 9:02 AC for N<=100 but MLE for N<=3e3

 https://codeforces.com/blog/entry/86539?#comment-758146

 I didn't know that Dinic's algorithm works in O(E*√V) for bipartite graph

 */

int N,M;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  MaxBipartiteMatching ma(N*N);

  REP(i,M) {
    int r1,c1,r2,c2; cin>>r1>>c1>>r2>>c2;
    --r1,--c1,--r2,--c2;
    int u=r1*N+c1,v=r2*N+c2;
    ma.addEdge(u,v);
  }
  int minvc=ma.solve();
  cout<<N*N-minvc<<endl;

  return 0;
}
