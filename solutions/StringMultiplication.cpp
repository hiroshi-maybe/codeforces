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

// $ cp-batch StringMultiplication | diff StringMultiplication.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address StringMultiplication.cpp && ./a.out

/*
 
 3/1/2019
 
 22:24-22:52 pause
 
 3/2/2019
 
 10:00-10:32 WA on test case #10
 10:41 AC
 
 https://codeforces.com/blog/entry/65487
 
 */

const int MAX_N=1e5+1;
string P[MAX_N];
int N;

bool cum[MAX_N][26];
LL f(int i, int c) {
  string p=P[i];
  LL res=0;
  LL cnt=0;
  int M=SZ(p);
  REP(j,M) {
    if(p[j]=='a'+c) ++cnt;
    else cnt=0;
    SMAX(res,cnt);
  }
  LL pcnt=0,scnt=0;
  for(int j=0; j<M&&p[j]=='a'+c; ++j) ++pcnt;
  for(int j=M-1; j>=0&&p[j]=='a'+c; --j) ++scnt;
  if(cum[i][c]) SMAX(res,pcnt+scnt+1);
  if(i>0&&pcnt==M&&scnt==M) {
    LL x=f(i-1,c);
    SMAX(res,x+(x+1)*M);
  }
  return res;
}
void solve() {
  REP(i,N)REP(c,26) {
    cum[i+1][c]=cum[i][c];
    REP(j,SZ(P[i])) cum[i+1][c]|=(P[i][j]==('a'+c));
  }
  
  LL res=0;
  REP(c,26) SMAX(res,f(N-1,c));
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>P[i];
  solve();
  
  return 0;
}
