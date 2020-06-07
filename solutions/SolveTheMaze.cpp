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

// $ cp-batch SolveTheMaze | diff SolveTheMaze.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SolveTheMaze.cpp && ./a.out

/*

 6/7/2020

 8:19-8:51 WA
 9:30 AC

 https://codeforces.com/blog/entry/78504

 */

const int MAX_N=50+1;
string A[MAX_N];
int N,M;

vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
const int  Inf=1e8;
int D[MAX_N][MAX_N];
bool solve() {
  REP(i,N)REP(j,M)if(A[i][j]=='B') {
    for(auto m : moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(A[ii][jj]=='G') return false;
      if(A[ii][jj]=='.') A[ii][jj]='#';
    }
  }

  REP(i,N)REP(j,M) D[i][j]=Inf;
  queue<II> Q;
  if(A[N-1][M-1]=='.') Q.emplace(N-1,M-1),D[N-1][M-1]=0;
  while(SZ(Q)) {
    int i,j; tie(i,j)=Q.front(); Q.pop();
    for(auto m : moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(A[ii][jj]=='#') continue;
      if(D[ii][jj]>D[i][j]+1) D[ii][jj]=D[i][j]+1,Q.emplace(ii,jj);
    }
  }

  REP(i,N) {
    dump(A[i]);
  }

  REP(i,N)REP(j,M) {
    if(A[i][j]=='B') assert(D[i][j]=Inf);
    if(A[i][j]=='G') if(D[i][j]==Inf) {
      dump(i,j,D[i][j]);
      return false;
    }
  }
  return true;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
void test() {
  N=genRandNum(1,5),M=genRandNum(1,5);
  vector<string> aa(N,string(M,'.'));
  REP(i,N) A[i]=string(M,'.');
  REP(i,N)REP(j,M) if(i!=N-1&&j!=M-1) {
    const string s=".#GB";
    A[i][j]=s[genRandNum(0,4)];
    aa[i][j]=A[i][j];
  }
  cout<<N<<" "<<M<<endl;
  REP(i,N) cout<<A[i]<<endl;

  vector<II> es;
  REP(i,N)REP(j,M) if(aa[i][j]=='.') {
    es.emplace_back(i,j);
  }

  bool exp=false;
  REP(mask,1<<SZ(es)) {
    int L=SZ(es);
    vector<string> aaa=aa;
    REP(k,L) if((mask>>k)&1) {
      aaa[es[k].first][es[k].second]='#';
    }

    bool res=true;
    queue<II> Q;
    VV<int> ds(N,VI(M,Inf));
    if(aaa[N-1][M-1]=='.') Q.emplace(N-1,M-1),ds[N-1][M-1]=0;
    while(SZ(Q)) {
      int i,j; tie(i,j)=Q.front(); Q.pop();
      for(auto m : moves) {
        int ii=i+m.first,jj=j+m.second;
        if(ii<0||ii>=N||jj<0||jj>=M) continue;
        if(aaa[ii][jj]=='#') continue;
        if(ds[ii][jj]>ds[i][j]+1) ds[ii][jj]=ds[i][j]+1,Q.emplace(ii,jj);
      }
    }

    REP(i,N)REP(j,M) {
      if(aaa[i][j]=='B'&&ds[i][j]!=Inf) res=false;
      if(aaa[i][j]=='G'&&ds[i][j]==Inf) res=false;
    }
    if(res) {
      exp=true;
      break;
    }
  }

  bool act=solve();
  if(exp!=act) {
    dump(exp,act);
  }
  assert(exp==act);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int t; cin>>t;
  while(t--) {
    cin>>N>>M;
    REP(i,N) cin>>A[i];
    cout<<(solve()?"Yes":"No")<<endl;
  }

  return 0;
}
