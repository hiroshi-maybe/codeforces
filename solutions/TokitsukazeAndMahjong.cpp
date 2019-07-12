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

// $ cp-batch TokitsukazeAndMahjong | diff TokitsukazeAndMahjong.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TokitsukazeAndMahjong.cpp && ./a.out

/*
 
 7/12/2019
 
 7:41-7:56 WA
 8:04 System test failed  
 
 https://codeforces.com/blog/entry/68314
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

map<char,int> T={
  {'s',0},{'m',1},{'p',2}
};
map<II,int> same;
vector<int> X[3];
void solve() {
  int res=2;
  FORR(kvp,same) SMIN(res,3-kvp.second);
  REP(i,3) {
    /*
    sort(ALL(X[i]));
    VI Y=X[i];
    int M=SZ(Y);
    if(M==3&&Y[2]==Y[1]+1&&Y[1]==Y[0]+1) res=0;
    if(M==3&&Y[2]==Y[1]+1) SMIN(res,1);
    if(M==2&&Y[1]==Y[0]+1) SMIN(res,1);
*/
    SETI S(ALL(X[i]));
    FORE(k,1,7) {
      int cnt=S.count(k)+S.count(k+1)+S.count(k+2);
      SMIN(res,3-cnt);
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  REP(i,3) {
    string s; cin>>s;
    int a=T[s[1]],b=s[0]-'0';
    same[{a,b}]++;
    X[a].push_back(b);
  }
  solve();
  
  return 0;
}
