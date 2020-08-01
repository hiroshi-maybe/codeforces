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

// $ cp-batch UncleBogdanAndCountryHappiness | diff UncleBogdanAndCountryHappiness.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address UncleBogdanAndCountryHappiness.cpp && ./a.out

/*

 7/30/2020

 8:32-9:35 give up
 22:00-23:30 pause

 7/31/2020

 9:35-10:35 WA
 20:55-21:31 WA has happening due to implementation mistake. Got AC

 8/1/2020

 12:00-13:10 Look at editorial and improve the code

 https://twitter.com/hanseilimak/status/1289646901986390016
 https://codeforces.com/blog/entry/80828

 */

const int MAX_N=1e6+1;
int P[MAX_N],H[MAX_N];
int N,M;

VI G[MAX_N];

II dfs(int u, int pre) {
  int cnt=P[u],gu=0;

  FORR(v,G[u]) if(v!=pre) {
    auto p=dfs(v,u);
    if(p.first==-1) return {-1,-1};
    cnt+=p.first,gu+=p.second;
  }

  int res=H[u]+cnt;
  if((res%2)!=0) return {-1,-1};
  res/=2;

  int lb=max(0,gu),hb=cnt;
  if(lb<=res&&res<=hb) return {cnt,res};
  return {-1,-1};

  /*
  if(abs(H[u])>cnt) return {-1,-1};

  int lb=(2*P[u]+H[u]-cnt+1)/2;
  int hb=(cnt+H[u]-2*gu)/2;
  SMAX(lb,0),SMIN(hb,P[u]);
  if(lb>hb) return {-1,-1};

  return {cnt,x/2};*/
}

void solve() {
  II a=dfs(0,-1);
  cout<<(a.first==-1?"NO":"YES")<<endl;
}

III dfswrong(int u, int pre) {
  int cnt=0;
  int L=0,R=0;
  FORR(v,G[u]) if(v!=pre) {
    III t=dfswrong(v,u);
    int c,l,r; tie(c,l,r)=t;
    if(l==-1) return {-1,-1,-1};
    cnt+=c,L+=l,R+=r;
  }

  int resl=(P[u]+H[u]-cnt+1)/2;
  int resr=(P[u]+H[u]-(2*L-cnt))/2;
  SMAX(resl,0);
  SMIN(resr,P[u]);

  cnt+=P[u];

  //dump(u,cnt,resl,resr,P[u],H[u]);
  if(resl>resr) return {-1,-1,-1};
  if(abs(H[u])>cnt) return {-1,-1,-1};

  return {cnt,resl,resr};
}

void solve_wrong() {
  III res=dfswrong(0,-1);
  int p; tie(ignore,p,ignore)=res;
  if(p==-1) {
    cout<<"NO"<<endl;
  } else {
    cout<<"YES"<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>M;
    REP(i,N) G[i].clear();
    REP(i,N) cin>>P[i];
    REP(i,N) cin>>H[i];
    REP(_,N-1) {
      int u,v; cin>>u>>v;
      --u,--v;
      G[u].push_back(v),G[v].push_back(u);
    }
    solve();
  }

  return 0;
}
