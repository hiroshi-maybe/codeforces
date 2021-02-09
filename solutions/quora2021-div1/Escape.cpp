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

// $ cp-batch Escape | diff Escape.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Escape.cpp && ./a.out

/*

 2/6/2021

 6:50-7:20 TLE?
 7:58 AC (100/100)

 https://codeforces.com/blog/entry/86539

 */
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
const int MAX_N=1e4+1;
string A[MAX_N];
II G[MAX_N];
int D[MAX_N];
int N,M,K;

const int Inf=1e8;
VI bfs(int r, int c, int maxd) {
  VI D(N*M,Inf);
  VI res;
  queue<int> Q;
  Q.emplace(r*M+c),D[r*M+c]=0,res.push_back(r*M+c);
  while(SZ(Q)) {
    int p=Q.front(); Q.pop();
    int i=p/M,j=p%M;
    for(auto m : moves) {
     int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(A[ii][jj]=='#') continue;
      int pp=ii*M+jj;
      int dd=D[p]+1;
      if(D[pp]>dd&&dd<=maxd) {
        Q.emplace(pp),D[pp]=D[p]+1;
        res.push_back(pp);
      }
    }
  }
  return maxd<Inf?res:D;
}
void nope() {
  println("IMPOSSIBLE");
  exit(0);
}
void solve() {
  queue<III> Q;
  REP(i,K) {
    int r=G[i].first,c=G[i].second;
    Q.emplace(r*M+c,0,i),A[r][c]='#';
  }
  while(SZ(Q)) {
    int p,d,k; tie(p,d,k)=Q.front(); Q.pop();
    int i=p/M,j=p%M;
    for(auto m : moves) {
     int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(A[ii][jj]=='#') continue;
      int pp=ii*M+jj;
      if(d+1<=D[k]) {
        A[ii][jj]='#';
        Q.emplace(pp,d+1,k);
      }
    }
  }

  int st=-1,g=-1;
  REP(i,N)REP(j,M) {
    if(A[i][j]=='S') st=i*M+j;
    if(A[i][j]=='E') g=i*M+j;
  }
  if(st==-1||g==-1) nope();
  VI ds=bfs(st/M,st%M,Inf);
  if(ds[g]==Inf) nope();
  println("%d",ds[g]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  scanf("%d %d %d",&N,&M,&K);
  REP(i,N) {
    char str[MAX_N];
    scanf("%s", str);
    A[i]=str;
  }
  REP(i,K) {
    int r,c,d;
    scanf("%d %d %d",&r,&c,&d);
    G[i]={r-1,c-1},D[i]=d;
  }
  solve();

  return 0;
}
