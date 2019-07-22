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

// $ cp-batch WOWFactor | diff WOWFactor.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WOWFactor.cpp && ./a.out

/*
 
 7/20/2019
 
 8:46-9:01 AC
 
 7/21/2019
 
 https://codeforces.com/blog/entry/68534
 
 Add simpler solution
 
 */

const int MAX_N=1e6+1;
string S;
int N;

void solve() {
  N=SZ(S);
  LL w=0,wo=0,wow=0;
  REP(i,N) {
    if(i>0&&S[i-1]=='v'&&S[i]=='v') ++w,wow+=wo;
    if(S[i]=='o') wo+=w;
  }
  cout<<wow<<endl;
}

LL dp[MAX_N][6];
void solve_org() {
  N=SZ(S);
  string s="vvovv";
  dp[0][0]=1;
  REP(i,N)REP(j,6) {
    if(j==0||j==2||j==5||j==3) dp[i+1][j]+=dp[i][j];
    if(j<5&&S[i]==s[j]) {
      if(j==1||j==4) {
        if(i>0&&S[i-1]==s[j-1]) dp[i+1][j+1]+=dp[i+1][j];
      } else dp[i+1][j+1]+=dp[i+1][j];
    }
  }
  LL res=dp[N][5];
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>S;
  solve();
  
  return 0;
}
