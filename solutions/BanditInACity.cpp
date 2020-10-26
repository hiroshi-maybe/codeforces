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

// $ cp-batch BanditInACity | diff BanditInACity.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BanditInACity.cpp && ./a.out

/*

 10/24/2020

 8:22-9:10 AC

 https://twitter.com/hanseilimak/status/1320597470485725184
 https://codeforces.com/blog/entry/84024

 https://twitter.com/n_vip/status/1320037253779910658
 https://twitter.com/tsutaj/status/1320037061978509312
 https://twitter.com/laycrs/status/1320037040856076288
 https://twitter.com/kzyKT_M/status/1320036334828879873

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

const LL Inf=1e15;
int G[MAX_N];
int D[MAX_N];
LL ub[MAX_N];
bool ok(LL t) {
  //dump(t);
  queue<int> Q;
  VI deg(D,D+N);
  REP(i,N) ub[i]=0;
  REP(i,N) if(deg[i]==0) {
    Q.emplace(i),ub[i]=t-A[i];
    //dump(i,ub[i],A[i]);;
    if(ub[i]<0) return false;
  }
  //dumpC(ub,ub+N);
  //dumpc(deg);
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
    int p=G[u];
    //dump(u,p);
    if(p==-1) continue;
    ub[p]+=ub[u],deg[p]--;
    SMIN(ub[p],Inf);
    if(deg[p]==0) {
      ub[p]-=A[p];
      //dump(p,ub[p]);
      if(ub[p]<0) return false;
      Q.emplace(p);
    }
  }
  assert(deg[0]==0);
  return ub[0]>=0;
}

void solve() {
  LL good=1e15,bad=-1;
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2;
    bool res=ok(m);
    //dump(m,res);
    (res?good:bad)=m;
  }
  cout<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  MINUS(G);
  REP(i,N-1) {
    int p; cin>>p;
    --p;
    G[i+1]=p;
    D[p]++;
  }
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
