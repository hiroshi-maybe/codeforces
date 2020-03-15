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

// $ cp-batch EhabAndPatheticMEXs | diff EhabAndPatheticMEXs.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EhabAndPatheticMEXs.cpp && ./a.out

/*
 
 3/14/2020
 
 8:03-8:26 TLE
 8:41 AC
 
 https://codeforces.com/blog/entry/74235
 
 */

const int MAX_N=1e6+1;
int N;

vector<II> G[MAX_N];
int D[MAX_N];
int viz[MAX_N];
void solve() {
  ZERO(viz);
  VI res(N-1,-1);
  queue<int> Q;
  REP(u,N) if(D[u]==1) Q.emplace(u),viz[u]=true;
  int cnt=0;
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
//    dump(u);
    FORR(p,G[u]) {
      int v,ei; tie(v,ei)=p;
      if (res[ei]==-1) res[ei]=cnt++;
      if(viz[v]) continue;
      viz[v]=true;
      Q.emplace(v);
    }
  }
  assert(cnt==N-1);
  REP(i,N-1) println("%d",res[i]);
//  dump("foo");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
    
  scanf("%d", &N);
  REP(i,N-1) {
    int u,v; scanf("%d %d",&u,&v);
    --u,--v;
    G[u].emplace_back(v,i),G[v].emplace_back(u,i);
    D[u]++,D[v]++;
  }
  solve();
  
  return 0;
}
