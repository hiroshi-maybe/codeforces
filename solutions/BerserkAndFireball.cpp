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

// $ cp-batch BerserkAndFireball | diff BerserkAndFireball.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BerserkAndFireball.cpp && ./a.out

/*

 7/12/2020

 9:40-10:22 WA on the test case 4
 10:37 bug fix and still WA
 10:50 give up

 23:16-23:22 all the A[i] in the interval should be if no fireball is applied
 23:25 fix overlow bug

 https://codeforces.com/blog/entry/80054
 https://twitter.com/laycrs/status/1282363059718090753

 */

const int MAX_N=1e6+1;
int A[MAX_N],B[MAX_N];
int N,M,K;
LL X,Y;

LL solve() {
  int j=0;
  VI alive(N,0);
  REP(i,N) if(j<M&&A[i]==B[j]) {
    alive[i]=1;
    ++j;
  }
  if(j<M) return -1;
  vector<II> rs;
  REP(i,N) {
    if(alive[i]==0&&(i==0||alive[i-1]==1)) rs.emplace_back(i,-1);
    if(alive[i]==0) rs.back().second=i;
  }
  const LL Inf=1e16;
  LL res=0;
  FORR(p,rs) {
    int L,R; tie(L,R)=p;
    //dump(L,R);
    int len=R-L+1;
    LL minc=Inf;
    REPE(x,len/K) {
      int rem=len-K*x;
      if(rem<0) continue;

      LL cost=X*x+Y*rem;
      if(x==0) {
        int maxa=0;
        FORE(i,L,R) SMAX(maxa,A[i]);
        int left=L==0?0:A[L-1];
        int right=L==N-1?0:A[R+1];
        if(maxa>left&&maxa>right) cost=Inf;
      }
      //dump(x,rem,cost);
      SMIN(minc,cost);
    }
    if(minc>=Inf) return -1;
    res+=minc;
  }
  if(res>=Inf) return -1;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>X>>K>>Y;
  REP(i,N) cin>>A[i];
  REP(i,M) cin>>B[i];
  cout<<solve()<<endl;

  return 0;
}
