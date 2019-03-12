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

#define UNIQUE(A) sort((A).begin(),(A).end()),(A).erase(std::unique((A).begin(), (A).end()), (A).end());

// $ cp-batch Skyscrapers | diff Skyscrapers.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Skyscrapers.cpp && ./a.out

/*
 
 3/8/2019
 
 19:06-19:49 I got WA on test case #4 and gave up
 
 3/12/2019
 
 14:50-15:13 got AC
 
 https://codeforces.com/blog/entry/65825
 
 This is a problem to merge two ranks.
 In order to adjust based on two ranks, we take more smaller values and more larger values.
 Thus max(L_row, L_col) + max(G_row, G_col) + 1 is the answer
 
 */

const int MAX_N=1e3+1;
LL A[MAX_N][MAX_N];
int N,M;

int rrank[MAX_N][MAX_N],crank[MAX_N][MAX_N],rmax[MAX_N],cmax[MAX_N];
void solve() {
  REP(i,N) {
    vector<LL> X(M);
    REP(j,M) X[j]=A[i][j];
    UNIQUE(X);
//    dumpc(X);
    MAPII mp; REP(i,SZ(X)) mp[X[i]]=i;
    REP(j,M) rrank[i][j]=mp[A[i][j]]+1;
    rmax[i]=SZ(X);
  }
  REP(j,M) {
    vector<LL> X(N);
    REP(i,N) X[i]=A[i][j];
    UNIQUE(X);

    MAPII mp; REP(i,SZ(X)) mp[X[i]]=i;
    REP(i,N) crank[i][j]=mp[A[i][j]]+1;
    cmax[j]=SZ(X);
  }
  REP(i,N){
    REP(j,M) {
//      dump(rrank[i][j],crank[i][j],rmax[i],cmax[j]);
      int x=max(rrank[i][j],crank[i][j]);
      int a=(x-rrank[i][j])+rmax[i];
      int b=(x-crank[i][j])+cmax[j];
//      dump(i,j,rrank[i][j],crank[i][j],x,a,b);
      printf("%d ", max(a,b));
      /*
      if(rrank[i][j]!=rmax[i]&&crank[i][j]!=cmax[j]) printf("%d ", max(rmax[i],cmax[j]));
      else if(rrank[i][j]==rmax[i]) printf("%d ", rmax[i]+(cmax[j]-crank[i][j]));
      else printf("%d ", cmax[j]+(rmax[i]-rrank[i][j]));
       */
    }
    println("");
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N)REP(j,M) cin>>A[i][j];
  solve();
  
  return 0;
}
