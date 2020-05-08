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

// $ cp-batch MonopoleMagnets | diff MonopoleMagnets.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MonopoleMagnets.cpp && ./a.out

/*
 
 5/6/2020
 
 8:14-9:16 problem statement is impossible to understand
 
 5/8/2020
 
 14:20-16:20 read editorial
 
 https://twitter.com/laycrs/status/1258077665442983936
 https://twitter.com/hanseilimak/status/1258892306041561089
 https://codeforces.com/blog/entry/76819
 
 */

const int MAX_N=1e3+1;
string A[MAX_N];
int N,M;

void nope() {
  cout<<-1<<endl;
  exit(0);
}

int viz[MAX_N][MAX_N];
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
void dfs(int i, int j) {
  if(viz[i][j]) return;
  viz[i][j]=1;
  for(auto m : moves) {
    int ii=i+m.first,jj=j+m.second;
    if(ii<0||ii>=N||jj<0||jj>=M) continue;
    if(A[ii][jj]!='#') continue;
    dfs(ii,jj);
  }
}

void solve() {
  REP(i,N) {
    VI xs;
    REP(j,M) if(A[i][j]=='#') xs.push_back(j);
    REP(i,SZ(xs)-1) if(xs[i+1]-xs[i]>1) nope();
  }
  REP(j,M) {
    VI xs;
    REP(i,N) if(A[i][j]=='#') xs.push_back(i);
    REP(i,SZ(xs)-1) if(xs[i+1]-xs[i]>1) nope();
  }
  bool norow=false,nocol=false;
  REP(i,N) {
    bool ok=true;
    REP(j,M) if(A[i][j]=='#') ok=false;
    norow|=ok;
  }
  REP(j,M) {
    bool ok=true;
    REP(i,N) if(A[i][j]=='#') ok=false;
    nocol|=ok;
  }
  if(norow^nocol) nope();
  int res=0;
  REP(i,N)REP(j,M)if(A[i][j]=='#'&&!viz[i][j]) {
    ++res;
    dfs(i,j);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
