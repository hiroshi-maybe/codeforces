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

// $ cp-batch MinimumEulerCycle | diff MinimumEulerCycle.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MinimumEulerCycle.cpp && ./a.out

/*
 
 4/10/2020
 
 9:20-9:35 give up
 18:00-18:51 read editorials and got AC
 
 https://codeforces.com/blog/entry/75877
 https://twitter.com/hanseilimak/status/1249154318198026240
 https://twitter.com/kimiyuki_u/status/1248652095487524866
 https://twitter.com/camypaper/status/1248651233675493376
 https://twitter.com/ngtkana/status/1248652357874810882
 https://twitter.com/laycrs/status/1248654727912378368
 
 */

int N;
LL L,R;

struct DirectedEulereanPath {
public:
  // input
  int V;
  vector<multiset<int>> G;
  DirectedEulereanPath() {}
  DirectedEulereanPath(int V): V(V), G(V) {}
  void edge(int u, int v) {
    assert(u<V&&v<V);
    G[u].emplace(v);
  }
  vector<int> solve(int u) {
    vector<int> res;
    dfs(u,res);
    return vector<int>(res.rbegin(),res.rend());
  }
private:
  void dfs(int u, vector<int> &res) {
    while(G[u].size()>0) {
      auto it=G[u].begin();
      int v=*it;
      G[u].erase(it);
      dfs(v,res);
    }
    res.push_back(u);
  }
};
void experiment() {
  DirectedEulereanPath eu(N);
  REP(v,N) REP(u,v) eu.edge(u,v),eu.edge(v,u);
  VI cycle=eu.solve(0);
  dumpc(cycle);
}

VI res;
void dfs(int d, LL l, LL r) {
  dump(d,l,r);
  assert(d<=N);
  if(l>r) return;
  
  if(d==N) {
    assert(l==1&&r==1);
    res.push_back(1);
    return;
  }
  
  LL cnt=2LL*(N-d);
  if(cnt>=l) {
    LL rr=min(r,cnt);
    FORE(i,l,rr) {
      if(i%2==1) res.push_back(d);
      else res.push_back(d+i/2);
    }
    l=1,r=max(r-cnt,0LL);
  } else {
    l-=cnt,r-=cnt;
  }
  dfs(d+1,l,r);
}

void solve() {
  res.clear();
  dfs(1,L,R);
  dumpc(res);
  assert(SZ(res)==R-L+1);
  REP(i,SZ(res)) printf("%d ",res[i]);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(i,T) {
    cin>>N>>L>>R;
    solve();
  }
  
  return 0;
}
