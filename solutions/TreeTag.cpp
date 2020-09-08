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

int treeDiameter(vector<vector<int>> &G, int u=0) {
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
// $ cp-batch TreeTag | diff TreeTag.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TreeTag.cpp && ./a.out

/*

 9/6/2020

 8:42-9:35 give up

 9/7/2020

 17:10-18:18 Read editorials and got AC

 https://twitter.com/hanseilimak/status/1303124007512731649
 https://codeforces.com/blog/entry/82366

 https://scrapbox.io/snuke/Codeforces_Round_%23668
 https://twitter.com/yamerarenaku/status/1302647689914449931
 https://twitter.com/uwitenpen/status/1302649074827452418?s=20
 https://twitter.com/heno_code/status/1302648811265748993
 https://twitter.com/kzyKT_M/status/1302646609260343298
 https://twitter.com/n_vip/status/1302646984579248128
 https://twitter.com/laycrs/status/1302646593519104000
 https://twitter.com/ajis_ka/status/1302647536151179264
 https://twitter.com/ngtkana/status/1302648455341338625
 https://twitter.com/kiri8128/status/1302648086569730049

 */

const int MAX_N=1e6+1;
const int Inf=MAX_N;
int N,s0,s1,d0,d1;

bool solve(VV<int> &G) {
  VI D(N,Inf);
  auto dfs = [&](auto &&self, int u, int pre, int d) {
    if(D[u]<=d) return;
    D[u]=d;
    FORR(v,G[u]) if(v!=pre) {
      self(self, v, u, d+1);
    }
  };

  dfs(dfs, s0,-1,0);
  if(D[s1]<=d0) return true;
  int dia=treeDiameter(G);
  if(dia<=2*d0) return true;
  if(2*d0<d1) return false;
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>s0>>s1>>d0>>d1;
    VV<int> G(N);
    s0-=1,s1-=1;
    REP(_,N-1) {
      int u,v; cin>>u>>v;
      --u,--v;
      G[u].push_back(v),G[v].push_back(u);
    }
    cout<<(!solve(G)?"Bob":"Alice")<<endl;
  }

  return 0;
}
