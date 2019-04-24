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

// $ cp-batch TreeDiameter | diff TreeDiameter.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TreeDiameter.cpp && ./a.out

/*
 
 4/20/2019
 
 11:24-12:31 AC
 
 https://cinnamo-coder.hatenablog.com/entry/2019/04/22/014951
 https://codeforces.com/blog/entry/66639
 
 I solved by a technique to compute tree diameter.
 
 Solving by testing all the pairs is a great idea that I could not come up with.
 Brute-force is testing all the pairs. However naiive algorithm needs N^2 queries.
 Look at a vertex `1` (=0000001(2)). If we want to test with all the other vertices, querying with 1******, *1*****, ..,*****1*, ******0 vertices is sufficient.
 That's true for other vertices too.
 
 */

int N;

int ask(VI A, VI B) {
  cout<<SZ(A)<<" "<<SZ(B)<<" ";
  REP(i,SZ(A)) cout<<A[i]<<" ";
  REP(i,SZ(B)) {
    cout<<B[i];
    if(i==SZ(B)-1) cout<<endl;
    else cout<<" ";
  }
  int verd; cin>>verd;
  if(verd==-1) exit(0);
  return verd;
}
void answer(int res) {
  cout<<"-1 "<<res<<endl;
}
void solve() {
  int res=0;
  REP(i,7) {
    VI A[2];
    FORE(j,1,N) A[(j>>i)&1].push_back(j);
    if(A[0].empty()||A[1].empty()) continue;
    SMAX(res,ask(A[0],A[1]));
  }
  answer(res);
}

void solve_org() {
  VI S; FORE(i,2,N) S.push_back(i);
  int cur=ask({1},S);
  while(SZ(S)>1) {
    VI A[2];
    REP(i,SZ(S)) A[i%2].push_back(S[i]);
    
    int x=ask({1},A[0]);
    if(x<cur) S=A[1];
    else S=A[0];
  }
  assert(SZ(S)==1);
  int u=S.front();
  VI T; FORE(i,1,N) if(i!=u) T.push_back(i);
  int res=ask({u},T);
  answer(res);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(i,T) {
    cin>>N;
//    dump(i,N);
    solve();
  }
  
  return 0;
}
