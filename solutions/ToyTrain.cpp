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

// $ cp-batch ToyTrain | diff ToyTrain.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ToyTrain.cpp && ./a.out

/*
 
 2/24/2019
 
 9:05-9:09 AC
 
 https://codeforces.com/blog/entry/65520
 
 */

const int MAX_N=20000+10;
int A[MAX_N],B[MAX_N];
multiset<int> cnt[MAX_N];
int N,M;

int dist(int i, int j) {
  if(j-i>=0) return j-i;
  return j+N-i;
}
void solve() {
  REP(i,M) cnt[A[i]].emplace(dist(A[i],B[i]));
  int maxcnt=0;
  REP(i,N) SMAX(maxcnt,SZ(cnt[i]));
  dump(maxcnt);
  vector<LL> res(N);
  REP(st,N) {
    LL ans=0;
    dump(st);
    REP(i,N) if(SZ(cnt[i])>=maxcnt-1) {
      LL n=SZ(cnt[i]);
      if(n<=0) continue;
      LL t=1LL*dist(st,i)+(n-1)*N+(LL)(*cnt[i].begin());
//      dump(i,n,dist(st,i),(n-1)*N,*cnt[i].begin(),t);
      SMAX(ans,t);
    }
    res[st]=ans;
  }
  REP(i,N) printf("%lld ",res[i]);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,M) {
    cin>>A[i]>>B[i];
    --A[i],--B[i];
  }
  solve();
  
  return 0;
}
