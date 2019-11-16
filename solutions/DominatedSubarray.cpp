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

// $ cp-batch DominatedSubarray | diff DominatedSubarray.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DominatedSubarray.cpp && ./a.out

/*
 
 11/13/2019
 
 7:09-7:37 AC
 
 https://codeforces.com/blog/entry/71434
 https://twitter.com/hanseilimak/status/1195842648759656448
 
 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

const int Inf=1e7;
void solve() {
  VV<int> X(N+1);
  REP(i,N) X[A[i]].push_back(i);
  int res=Inf;
  REP(a,N+1) if(SZ(X[a])>1) {
    REP(i,SZ(X[a])-1) SMIN(res,X[a][i+1]-X[a][i]+1);
  }
  if(res>=Inf) res=-1;
  cout<<res<<endl;
}
void solve_org() {
  map<int,int> cnt;
  int doma=-1,l=0,res=Inf; cnt[A[0]]++;
  FOR(r,1,N) {
    int a=A[r];
    cnt[a]++;
    if(cnt[a]>1) doma=a;
    while(cnt[doma]>1) {
      assert(l<r);
      SMIN(res,r-l+1);
      int b=A[l];
      cnt[b]--,++l;
      if(cnt[b]==0) cnt.erase(b);
    }
    doma=-1;
  }
  if(res>=Inf) res=-1;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(_,T) {
    cin>>N;
    REP(i,N)cin>>A[i];
    solve();
  }
  
  return 0;
}
