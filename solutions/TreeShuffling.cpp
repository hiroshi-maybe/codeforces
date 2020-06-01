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

// $ cp-batch TreeShuffling | diff TreeShuffling.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TreeShuffling.cpp && ./a.out

/*

 5/31/2020

 8:56-9:30 WA
 9:35 give up

 20:25-20:38 AC

 https://twitter.com/hanseilimak/status/1267256698290335750
 https://codeforces.com/blog/entry/78202

 https://twitter.com/satanic0258/status/1267134835279028224
 https://twitter.com/ajis_ka/status/1267133361228660737
 https://twitter.com/laycrs/status/1267132642908008450
 https://twitter.com/kzyKT_M/status/1267132847757787136

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,B[MAX_N],C[MAX_N];

VI G[MAX_N];
void dfs1(int u, int pre, LL minc) {
  SMIN(A[u],minc);
  SMIN(minc,A[u]);
  FORR(v,G[u])if(v!=pre) dfs1(v,u,minc);
}
LL res=0;
vector<LL> dfs2(int u, int pre) {
  vector<LL> ans(2);
  if(B[u]!=C[u]) ans[B[u]]++;
  FORR(v,G[u])if(v!=pre) {
    auto xs=dfs2(v,u);
    REP(i,2) ans[i]+=xs[i];
  }
  if(pre==-1||A[u]<A[pre]) {
    LL pair=min(ans[0],ans[1]);
    res+=A[u]*pair*2;
    REP(i,2) ans[i]-=pair;
  }
  return ans;
}
void solve() {
  dfs1(0,-1,A[0]);
  dfs2(0,-1);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i]>>B[i]>>C[i];
  int x=0,y=0;
  REP(i,N) x+=(B[i]==0),y+=(C[i]==0);
  if(x!=y) {
    cout<<-1<<endl;
    return 0;
  }
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
  solve();

  return 0;
}
