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

// $ cp-batch PlusesAndMinuses | diff PlusesAndMinuses.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PlusesAndMinuses.cpp && ./a.out

/*

 6/25/2020

 8:06-8:34 AC

 https://codeforces.com/blog/entry/79376

 6/26/2020

 Add simpler solution in the editorial.

 */

string S;
int N;

void solve() {
  N=SZ(S);
  LL res=0;
  int cur=0,mn=0;
  REP(i,N) {
    cur+=S[i]=='+'?1:-1;
    if(cur<mn) {
      res+=i+1;
      mn=cur;
    }
  }
  res+=N;
  cout<<res<<endl;
}

void solve_org() {
  N=SZ(S);
  VI cum(N+1,0);
  REP(i,N) cum[i+1]=cum[i]+(S[i]=='+'?1:-1);
  REP(i,N) SMIN(cum[i+1],cum[i]);
  REPE(i,N) cum[i]=-cum[i];
  cum.push_back(1e7);
  //dumpc(cum);

  LL res=0;
  REPE(i,N) {
    int del=upper_bound(ALL(cum),i)-cum.begin();
    res+=del;
    //dump(i,del,N,res);
    if(del>N) {
      res-=1;
      break;
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>S;
    solve();
  }

  return 0;
}
