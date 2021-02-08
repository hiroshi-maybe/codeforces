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

// $ cp-batch PaintingTheArrayI | diff PaintingTheArrayI.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PaintingTheArrayI.cpp && ./a.out

/*

 2/7/2021

 8:23-8:30 WA
 9:00 give up

 18:35-20:55 read editorial and got AC

 https://codeforces.com/blog/entry/87598
 https://twitter.com/kzyKT_M/status/1358458396307955712
 https://twitter.com/laycrs/status/1358459297265426432
 https://twitter.com/kiri8128/status/1358459010760855553
 https://twitter.com/Rubikun_pro/status/1358459402680889347

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

void solve() {
  VV<int> xs(2,VI(1,0));
  map<int,queue<int>> pos;
  REP(i,N) pos[A[i]].emplace(i);
  REP(i,N) {
    int a=A[i];
    int last0=xs[0].back(),last1=xs[1].back();
    if(a==last0) xs[1].push_back(a);
    else if(a==last1) xs[0].push_back(a);
    else {
      int nex0=SZ(pos[last0])?pos[last0].front():MAX_N;
      int nex1=SZ(pos[last1])?pos[last1].front():MAX_N;
      if(nex0<nex1) xs[0].push_back(a);
      else xs[1].push_back(a);
    }
    pos[a].pop();
  }

  int res=0;
  REP(l,2) {
    REP(i,SZ(xs[l])) {
      if(i==0||xs[l][i-1]!=xs[l][i]) ++res;
    }
  }
  cout<<res-2<<endl;
}

void solve_wrong() {
  vector<II> rl;
  REP(i,N) {
    if(i==0||A[i-1]!=A[i]) rl.emplace_back(A[i],0);
    rl.back().second++;
  }

  //dumpc(rl);
  VV<int> xs(2);
  FORR(p,rl) {
    int a=p.first,cnt=p.second;
    if(cnt==1) {
      if(xs[0].empty()||xs[0].back()!=a) xs[0].push_back(a);
      else xs[1].push_back(a);
    } else {
      xs[0].push_back(a),xs[1].push_back(a);
    }
  }
  int res=0;
  REP(l,2) {
    dumpc(xs[l]);
    REP(i,SZ(xs[l])) {
      if(i==0||xs[l][i-1]!=xs[l][i])++res;
    }
  }

  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
