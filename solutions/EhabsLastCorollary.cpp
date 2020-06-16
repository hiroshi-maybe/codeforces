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

// $ cp-batch EhabsLastCorollary | diff EhabsLastCorollary.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EhabsLastCorollary.cpp && ./a.out

/*

 6/13/2020

 8:55-10:02 system test failed
 10:35 AC after bug fix

 https://codeforces.com/blog/entry/78781
 https://twitter.com/hanseilimak/status/1272569488005672960

 https://twitter.com/kyort0n/status/1271852048238010368
 https://twitter.com/armeria_betrue/status/1271852367265148929
 https://twitter.com/n_vip/status/1271853131681239040

 */

const int MAX_N=1e6+1;
int N,M,K;

VI res1[2];
VI G[MAX_N];
int viz[MAX_N];

void dfs(int u, VI &cur) {
  if(viz[u]!=-1) {
    int len=SZ(cur)-viz[u];
    if(3<=len&&len<=K) {
      cout<<2<<endl;
      cout<<SZ(cur)-viz[u]<<endl;
      FOR(i,viz[u],SZ(cur)) cout<<cur[i]+1<<" ";
      cout<<endl;
      exit(0);
    }
    return;
  }
  viz[u]=SZ(cur);
  cur.push_back(u);
  FORR(v,G[u]) dfs(v,cur);
  cur.pop_back();
}

void dfs1(int u, int col) {
  if(viz[u]) return;
  res1[col].push_back(u);
  viz[u]=1;
  FORR(v,G[u]) {
    dfs1(v,col^1);
  }
}
void solve() {
  VI cur;
  MINUS(viz);
  dfs(0,cur);

  ZERO(viz);
  dfs1(0,0);

  //dumpc(res1);
  VI ans=res1[0];
  if(SZ(res1[1])>SZ(ans)) ans=res1[1];
  assert(SZ(ans)>=(K+1)/2);
  cout<<1<<endl;
  REP(i,(K+1)/2) cout<<ans[i]+1<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>K;
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }

  solve();

  return 0;
}
