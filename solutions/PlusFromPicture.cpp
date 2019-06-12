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

// $ cp-batch PlusFromPicture | diff PlusFromPicture.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PlusFromPicture.cpp && ./a.out

/*
 
 6/11/2019
 
 6:08-6:24 AC
 
 https://codeforces.com/blog/entry/67614
 
 Condition is simpler because YES only when one cross exists
 
 One cross exists <=> Only one center exists <=> If one cross is found, entire board is searched only once
 
 */

const int MAX_N=510+1;
string A[MAX_N];
int N,M;
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
vector<II> X;
void dfs(int i, int j) {
  for(auto m : moves) {
    int ii=i+m.first,jj=j+m.second;
    if(ii<0||ii>=N||jj<0||jj>=M) continue;
    if(A[ii][jj]=='*') {
      A[ii][jj]='.',X.emplace_back(ii,jj);
      dfs(ii,jj);
    }
  }
}

bool check() {
  map<int,int> R,C;
  FORR(p,X) R[p.first]++,C[p.second]++;
  set<int>RR,CC;
  FORR(kvp,R) if(kvp.second>1) RR.emplace(kvp.first);
  FORR(kvp,C) if(kvp.second>1) CC.emplace(kvp.first);
  if(SZ(RR)!=1||SZ(CC)!=1) return false;
  int r=*RR.begin(),c=*CC.begin();
  set<II> B(ALL(X));
  return (B.count({r,c})&&B.count({r-1,c})&&B.count({r+1,c})&&B.count({r,c-1})&&B.count({r,c+1}));
}

void solve() {
  int comp=0, cnt=0;
  REP(i,N)REP(j,M) if(A[i][j]=='*') {
    X.clear();
    ++comp;
    A[i][j]='.',X.emplace_back(i,j);
    dfs(i,j);
    cnt+=check();
  }
  bool res=comp==1&&cnt==1;
  cout<<(res?"YES":"NO")<<endl;
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
