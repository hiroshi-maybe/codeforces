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

// $ cp-batch UglyPairs | diff UglyPairs.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address UglyPairs.cpp && ./a.out

/*
 
 6/27/2019
 
 14:07-15:09 give up
 17:30-18:00 read editorial
 20:10-21:15 read editorial and got AC
 
 https://codeforces.com/blog/entry/66827
 https://cinnamo-coder.hatenablog.com/entry/2019/05/02/021544
 
 In this problem, we want no consecutive elements to satisfy |A[i]-A[i+1]|==1
 Thus we can group characters by alphabet parity.
 If we concatenate them, position which potentially violates |A[i]-A[i+1]|==1 is only one position, which should be minimal.
 
 */

string S;

void solve() {
  int N=SZ(S);
  string X[2];
  REP(i,N) X[S[i]%2].push_back(S[i]);
  REP(i,2)sort(ALL(X[i]));
  string res;
  if(X[0].empty()) res=X[1];
  else if(X[1].empty()) res=X[0];
  else if(abs(X[0].back()-X[1].front())!=1) {
    res=X[0]+X[1];
  } else if(abs(X[1].back()-X[0].front())!=1) {
    res=X[1]+X[0];
  } else res="No answer";
  cout<<res<<endl;
}

void test() {
  int N=SZ(S);
  VI P(N); REP(i,N)P[i]=i;
  do {
    string x;
    REP(i,N) x.push_back(S[P[i]]);
    bool ok=true;
    REP(i,N-1) if(abs(x[i]-x[i+1])==1) ok=false;
    if(ok) dump(x);
  } while(next_permutation(ALL(P)));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(i,T) {
    cin>>S;
    solve();
  }
  
  return 0;
}
