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

// $ cp-batch AddOnATreeRevolution | diff AddOnATreeRevolution.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AddOnATreeRevolution.cpp && ./a.out

/*
 
 7/5/2019
 
 9:08-9:45 give up
 14:00-15:12 read code by @kmjp and got AC
 
 https://codeforces.com/contest/1188/submission/56592028
 
 Constructive problem => Construct each condition independently and cancel redundant impact
 Tree => Enumerate edges especially if condition is about edges
 Constraint is EVEN => Do something TWICE
 
 https://codeforces.com/blog/entry/68079
 
 */

const int MAX_N=1e4+1;
int N;

vector<II> G[MAX_N];

void dfs(int u, int pre, VI &res) {
  int c=0;
  FORR(p,G[u])if(p.second!=pre) ++c,dfs(p.second,u,res);
  if(c==0) res.push_back(u);
}

void nope() {
  println("NO");
  exit(0);
}
void solve() {
  REP(i,N) if(SZ(G[i])==2) nope();
  vector<III> res;
  REP(u,N) FORR(p,G[u]) {
    int v=p.second,w=p.first;
    if(u>v) continue;
//    dump(u,v);
    VI ls1,ls2;
    dfs(u,v,ls1),dfs(v,u,ls2);
//    dumpc(ls1);
//    dumpc(ls2);
    assert(SZ(ls1)>=1&&SZ(ls2)>=1);
    int ls1a=ls1.front(),ls1b=SZ(ls1)>1?ls1.back():ls1a;
    int ls2a=ls2.front(),ls2b=SZ(ls2)>1?ls2.back():ls2a;
    res.emplace_back(ls1a,ls2a,w/2);
    res.emplace_back(ls1b,ls2b,w/2);
    if(ls1a!=ls1b) res.emplace_back(ls1a,ls1b,-w/2);
    if(ls2a!=ls2b) res.emplace_back(ls2a,ls2b,-w/2);
  }
  println("YES");
  println("%d", SZ(res));
  REP(i,SZ(res)) {
    int u,v,w; tie(u,v,w)=res[i];
    println("%d %d %d", u+1, v+1, w);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N-1) {
    int u,v,w; cin>>u>>v>>w;
    --u,--v;
    G[u].emplace_back(w,v);
    G[v].emplace_back(w,u);
  }
  solve();
  
  return 0;
}
