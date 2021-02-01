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

// $ cp-batch Journey | diff Journey.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Journey.cpp && ./a.out

/*

 1/29/2021

 7:51-8:28 TLE
 8:35 WA

 1/31/2021

 22:00-22:25 AC

 https://codeforces.com/blog/entry/87356
 https://twitter.com/hanseilimak/status/1356127716865499137

 */

const int LF=0,RT=1;
const int MAX_N=1e6;
//const int Inf=1e7;
int N;
string S;

int memo[MAX_N][2][2];
int f(int i, int d, int p) {
  // `i>N` check was missing :(
  if(i<0||i>N) return 0;
  int &res=memo[i][d][p];
  if(res>=0) return res;
  if(d==LF) {
    // to left
    if(i>=N) return res=0;
    int rr=(S[i]=='R')^(1-p);
    if(rr==RT) return res=0;
    res=1;
    res+=f(i-1,d,1-p);
  } else {
    // to right
    if(i==0) return res=0;
    int lr=(S[i-1]=='R')^(1-p);
    //dump(i,d,p,lr);
    if(lr==LF) return res=0;
    res=1;
    res+=f(i+1,d,1-p);
  }

  //dump(i,d,p,res);
  return res;
}
void solve() {
  REPE(i,N+1)REP(j,2)REP(k,2) memo[i][j][k]=-1;
  //MINUS(memo);
  REPE(i,N) {
    int res=1;
    /*if(i>0&&S[i-1]=='L')*/ res+=f(i-1,LF,1);
    /*if(i<N&&S[i]=='R')*/ res+=f(i+1,RT,1);
    cout<<res<<" ";
  }
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>S;
    solve();
  }

  return 0;
}
