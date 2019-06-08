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

// $ cp-batch NauuoAndCards | diff NauuoAndCards.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NauuoAndCards.cpp && ./a.out

/*
 
 6/7/2019
 
 11:09-13:08 AC
 
 It took tons of time to complete case work
 
 a) B={....,1,2,..,K}
  res = N-K if K+1,..,N are in appropriate positions
 b) Otherwise
 res = N+{# of operations to have `1`} + max { # of operations to put `i` after putting `1` }
 
 https://codeforces.com/blog/entry/67511
 
 Editorial is showing clearer model for case #b.
 Sequence of #s to play is in form of {0,..,0,1,2,..,N}.
 We want to know mimimul # of `0`s.
 That can be computed by pos[i]+1-(i-1)=pos[i]-i+2, which is independent to `i`(>=1).
 res = max{pos[i]-i+2}+N, not that pos[i] is 0-indexed.
 
 Noticing optimal sequence to be played is {0,..,0,1,..,N} is the key.
 Then problem is reducing to auxiliary problem.
 
 Constructing optimal step is probably one typical point of this problem.
 Then we can figure out that it's possible to compute # of necessary steps to put `0` independently in O(1) step for each element.
 Tricky point is that each number is processed one by one. Number itself affects necessary # of steps, too.
 Case work of a case of no `0` is kind of tricky, too.
 Therefore it took tons of time to solve this problem...😞
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N],B[MAX_N];
int N;

void solve() {
  VI pos(N+1,-1);
  REP(i,N) if(B[i]!=0) pos[B[i]]=i;
  int k=0;
  if(pos[1]>=0) {
    bool ok=true;
    for(int d=1; pos[1]+d<N; ++d) if(B[pos[1]+d]!=d+1) {
      ok=false;
      break;
    }
    if(ok) {
      k=N-pos[1];
      for(int i=1; k+i<=N; ++i) if(pos[k+i]>=i-1) ok=false;
      if(!ok) k=0;
    }
  }
  int res;
  if(k>0) {
    res=N-k;
  } else {
    int e=0;
    FORE(i,2,N) if(pos[i]>pos[1]) {
      int x=max(0,pos[i]-pos[1]-(i-1));
      SMAX(e,x);
    }
    res=pos[1]+1+N+e;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N) cin>>B[i];
  solve();
  
  return 0;
}
