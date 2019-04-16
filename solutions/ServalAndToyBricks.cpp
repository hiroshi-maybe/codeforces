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

// $ cp-batch ServalAndToyBricks | diff ServalAndToyBricks.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ServalAndToyBricks.cpp && ./a.out

/*
 
 4/13/2019
 
 7:16-7:53 AC
 
 DO NOT allocate too much memory 😡. Linked throws an error.
 I wasted a lot of time to fix the error.
 
 https://codeforces.com/blog/entry/66539
 https://cinnamo-coder.hatenablog.com/entry/2019/04/14/183311
 http://perogram.hateblo.jp/entry/cf_1153

 If H[i][j]>0, H[i][j]<=min(A[i],B[j]) is necessary to satisfy.
 
 
 */

const int MAX_N=100+1;
int A[MAX_N],B[MAX_N],H[MAX_N][MAX_N];
int N,M,maxH;
void solve() {
  REP(i,N)REP(j,M)if(H[i][j]>0) H[i][j]=min(A[i],B[j]);
  REP(i,N) {
    int a=0;
    REP(j,M) SMAX(a,H[i][j]);
    assert(a==A[i]);
  }
  REP(j,M) {
    int b=0;
    REP(i,N) SMAX(b,H[i][j]);
    assert(b==B[j]);
  }
  REP(i,N) {
    REP(j,M) printf("%d ",H[i][j]);
    println("");
  }
}

void solve_org() {
  REP(j,M) {
    int h=B[j];
    if(h==0)continue;
    bool ok=false;
    for(int i=N-1; i>=0; --i) {
      if(H[i][j]==0) continue;
      if(A[i]>=h) {
        ok=true;
        H[i][j]=h;
        break;
      }
    }
    assert(ok);
  }
  REP(i,N) {
    int h=A[i];
    bool ok=false;
    REP(j,M) if(H[i][j]==h) {
      ok=true;
      break;
    }
    if(ok) continue;
    ok=false;
    REP(j,M) if(H[i][j]>0) {
      if(B[j]>=h) {
        ok=true,H[i][j]=h;
        break;
      }
    }
    assert(ok);
  }
  REP(i,N) {
    REP(j,M) {
      assert(H[i][j]<=A[i]&&H[i][j]<=B[j]);
      printf("%d ",H[i][j]);
    }
    println("");
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>maxH;
  REP(i,M) cin>>B[i];
  REP(i,N) cin>>A[i];
  REP(i,N)REP(j,M) cin>>H[i][j];
  solve();
  
  return 0;
}
