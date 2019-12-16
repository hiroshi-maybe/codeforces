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

// $ cp-batch Blocks | diff Blocks.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Blocks.cpp && ./a.out

/*
 
 12/15/2019
 
 1:21-1:55 AC
 
 https://twitter.com/hanseilimak/status/1206384244055928832
 https://codeforces.com/contest/1271/submission/66941821
 
 */

//const int MAX_N=200+1;
string S;
int N;

VI res;
bool f(string &s) {
  VI ps;
  REP(i,N)if(s[i]=='B') ps.push_back(i);
  if(SZ(ps)%2==1) return false;
  for(int i=0; i<SZ(ps); i+=2) {
    int a=ps[i],b=ps[i+1];
    FOR(j,a,b) res.push_back(j);
  }
  return true;
}
char inv(char c) {
  return c=='W'?'B':'W';
}
void yes(string s) {
  REP(i,SZ(res)) {
    s[res[i]]=inv(s[res[i]]);
    s[res[i]+1]=inv(s[res[i]+1]);
//    dump(i,s);
  }
  int cnt=count(ALL(s),'W');
//  dumpc(res);
//  dump(cnt,s);
  assert(cnt==0||cnt==N);

  println("%d",SZ(res));
  REP(i,SZ(res)) printf("%d ",res[i]+1);
  println("");
  exit(0);
}
void solve() {
  string s=S;
  if(f(s)) yes(s);
  REP(i,N)s[i]=inv(s[i]);
  if(f(s)) yes(s);
  cout<<-1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>S;
  solve();
  
  return 0;
}
