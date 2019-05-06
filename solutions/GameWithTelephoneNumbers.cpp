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

// $ cp-batch GameWithTelephoneNumbers | diff GameWithTelephoneNumbers.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GameWithTelephoneNumbers.cpp && ./a.out

/*
 
 4/22/2019
 
 7:39-8:01 WA
 8:15 AC
 
 https://codeforces.com/blog/entry/66687
 https://cinnamo-coder.hatenablog.com/entry/2019/04/23/165615
 
 "8xxxxxxxxxx" is win state.
 
 P1 wants to make it. He will remove non-8 in left side of right 11 digits
 - Remove 8 in left: loses chance to leave more 8s
 - Remove some digit in right:
  8xxxxxxxxxx => loses chance to leave 8
  yxxxxxxxxxx => same as deleting non-8 y
 
 => Other strategies are declined by counter examples
 
 P2 prevents by removing 8
 - Remove non-8 in left: helps to keep more 8s
 - Remove some digit in right:
  8xxxxxxxxxx => same as removing 8
  yxxxxxxxxxx => loses chance to remove 8
 
 => Other strategies are declined by counter examples
 
 Summary:
  - Win state is clear. Find simple strategy and prove it (Guess and prove)
  - In proof, find counter example where operation against the strategy makes it worse
 
 */

const int MAX_N=1e6+1;
int N;
string S;

int viz[MAX_N];
void nope() {
  cout<<"NO"<<endl;
  exit(0);
}
void solve() {
  int l1=(N-11+1)/2,l2=(N-11)-l1;
  assert(l1-l2<=1);
  int cnt=0;
  REP(i,N-10) cnt+=(S[i]=='8');
  if(cnt<=l2) nope();
  else cout<<"YES"<<endl;
  /*
  REP(i,N-10) if(S[i]=='8') {
    viz[i]=true,l2--;
    if(l2==0) break;
  }
  assert(l2==0);
  REP(i,N) if(!viz[i]) {
    --l1;
    if(l1==0) {
      string res=(S[i+1]=='8')?"YES":"NO";
      cout<<res<<endl;
      return;
    }
  }
  nope();*/
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>S;
  solve();
  
  return 0;
}
