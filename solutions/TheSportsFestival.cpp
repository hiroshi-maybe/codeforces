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

// $ cp-batch TheSportsFestival | diff TheSportsFestival.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheSportsFestival.cpp && ./a.out

/*

 4/16/2021

 7:58-8:44 TLE
 8:45 AC

 https://codeforces.com/blog/entry/89644

 */

const int MAX_N=2010;
LL S[MAX_N];
int N;

LL memo[MAX_N][MAX_N];
LL f(int l, int r) {
  if(memo[l][r]>=0) return memo[l][r];
  LL &res=memo[l][r];
  if(l==0&&r==N+1) return res=0;
  if(l==0) return res=S[r]-S[l+1]+f(l,r+1);
  if(r==N+1) return res=S[N]-S[l]+f(l-1,r);

  LL lcost=S[r-1]-S[l],rcost=S[r]-S[l+1];
  return res=min(lcost+f(l-1,r),rcost+f(l,r+1));
}

void solve() {
  LL res=1e17;
  sort(S,S+N+1);
  //dumpC(S,S+N+1);
  REPE(i,N+1)REPE(j,N+1) memo[i][j]=-1;
  FORE(i,1,N) SMIN(res,f(i-1,i+1));

  /*
  REP(st,N) {
    LL cur=0;
    int l=st-1,r=st+1;
    while(l>=0||r<N) {
      if(l<0) cur+=S[r]-S[0],++r;
      else if(r>=N) cur+=S[N-1]-S[l],--l;
      else {
        if((S[r]-S[l+1])*(N-r)<(S[r-1]-S[l])*()) cur+=S[r]-S[l+1],++r;
        else cur+=S[r-1]-S[l],--l;
      }
    }
    dump(st,cur);
    SMIN(res,cur);
  }*/

  /*
  do {
    dumpC(S,S+N);
    LL cur=0;
    LL maxs=S[0],mins=S[0];
    REP(i,N) {
      SMAX(maxs,S[i]),SMIN(mins,S[i]);
      cur+=maxs-mins;
    }
    dump(cur);
    SMIN(res,cur);
  } while(next_permutation(S,S+N));*/

  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>S[i+1];
  solve();

  return 0;
}
