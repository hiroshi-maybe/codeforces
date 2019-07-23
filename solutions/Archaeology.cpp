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

// $ cp-batch Archaeology | diff Archaeology.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Archaeology.cpp && ./a.out

/*
 
 7/20/2019
 
 10:20-10:54 submit
 11:03 resubmit and AC
 
 Find common subsequence for A=S[0..<N/2] and B=rev(S[N/2..N]).
 From the constraint, there should be at least one common character between A and B.
 
 https://codeforces.com/blog/entry/68534
 => Checking from outside is smarter. No need to decide where to split.
 
 */

//const int MAX_N=1e6+1;
string S;
int N;

void f(string A, string B, char c) {
  reverse(ALL(A));
  string res;
  for(int i=0,j=0; i<SZ(A)&&j<SZ(B); ) {
    if(A[i]==B[j]) res.push_back(A[i]),++i,++j;
    else if(j+1<SZ(B)&&A[i]==B[j+1]) res.push_back(A[i]),++i,j+=2;
    else if(i+1<SZ(A)&&A[i+1]==B[j]) res.push_back(B[j]),i+=2,++j;
    else if(i+1<SZ(A)&&j+1<SZ(B)&&A[i+1]==B[j+1]) res.push_back(A[i+1]),i+=2,j+=2;
    else {
      if(SZ(A)-i<SZ(B)-j) ++i;
      else ++j;
    }
  }
//  dump(c,A,B,res);
  string a=res; reverse(ALL(a));
  string ans=a;
  if(c!='?') ans+=c;
  ans+=res;
  if(SZ(ans)>=N/2) {
    cout<<ans<<endl;
    exit(0);
  }
}

void solve() {
  N=SZ(S);
  int ci=N/2;
  string A,B;
  A=S.substr(0,ci),B=S.substr(ci);
  f(A,B,'?');
  A=S.substr(0,ci),B=S.substr(ci+1);
  f(A,B,S[ci]);
  println("IMPOSSIBLE");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>S;
  solve();
  
  return 0;
}
