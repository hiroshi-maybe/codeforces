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

// $ cp-batch PalindromeGame | diff PalindromeGame.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PalindromeGame.cpp && ./a.out

/*

 5/20/2021

 7:42-9:00 AC

 https://codeforces.com/blog/entry/90939

 */

string S;
int N;

bool ispalin(string &s) {
  int l=0,r=N-1;
  while(l<r) {
    if(s[l]!=s[r]) return false;
    ++l,--r;
  }
  return true;
}

string solve() {
  int cnt0=count(ALL(S),'0');
  if(cnt0==0) return "DRAW";
  if(N%2==0) {
    if(ispalin(S)) return "BOB";
    return "ALICE";
  } else {
    if(ispalin(S)) {
      if(cnt0==1) return "BOB";
      else if(S[N/2]=='1') return "BOB";
      else return "ALICE";
    } else {
      if(S[N/2]=='0'&&cnt0==2) return "DRAW";
      else return "ALICE";
    }
  }
}

string tos(int n, int l) {
  string S(l,'0');
  REP(i,l) if((n>>i)&1) S[i]='1';
  return S;
}

const int Inf=1e8;
map<tuple<string,int,int>, int> memo;
int f(string s, int t, int rev) {
  int cnt0=count(ALL(s),'0');
  if(cnt0==0) return 0;
  if(memo.count({s,t,rev})) return memo[{s,t,rev}];
  int& res=memo[{s,t,rev}];
  res=(t==0?Inf:-Inf);
  if(!ispalin(s)&&!rev) {
    reverse(ALL(s));
    res=f(s,1-t,1);
    reverse(ALL(s));
  }
  REP(i,SZ(s)) if(s[i]=='0') {
    s[i]='1';
    int d=t==0?1:-1;
    int x=f(s,1-t,0)+d;
    if(t==0) SMIN(res,x);
    else SMAX(res,x);
    s[i]='0';
  }
  //if(S=="1000") dump(s,t,rev,res);
  return res;
}

string solvetest() {
  memo.clear();
  int res=f(S,0,0);
  if(res==0) return "DRAW";
  if(res<0) return "ALICE";
  return "BOB";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

/*
  N=7;
  REP(n,1<<N) {
    S=tos(n,N);
    N=SZ(S);
    string res=solve();
    dump(S,res);
  }
  return 0;*/

  int t; cin>>t;
  while(t--) {
    cin>>N>>S;
    cout<<solve()<<endl;
  }

  return 0;
}
