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
template<class T> using VVV=vector<vector<vector<T>>>;
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

// $ cp-batch RestrictedRPS | diff RestrictedRPS.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RestrictedRPS.cpp && ./a.out

/*
 
 11/1/2019
 
 7:49-8:20 WA
 8:32 AC
 
 https://codeforces.com/blog/entry/71080
 
 */

int N,Y[3];
string S;

string rps="RPS";
void solve() {
  vector<queue<int>> X(3);
  REP(i,N) {
    if(S[i]=='R') X[0].emplace(i);
    if(S[i]=='P') X[1].emplace(i);
    if(S[i]=='S') X[2].emplace(i);
  }
  string T(N,'?');
  int win=0;
  REP(i,3) {
    int YY=Y[i];
    int j=-1;
    if(i==0) j=2;
    if(i==1) j=0;
    if(i==2) j=1;

//    dump(i,YY,SZ(X[j]),min(YY,SZ(X[j])));
    int a=min(YY,SZ(X[j]));
    REP(_,a) {
      assert(SZ(X[j]));
      int k=X[j].front(); X[j].pop();
      T[k]=rps[i];
      Y[i]--;
      ++win;
//      dump(i,k,win);
    }
  }
//  dump(win);
  queue<char> Q;
  REP(i,3)while(Y[i]>0) Q.emplace(rps[i]),--Y[i];
  REP(i,N)if(T[i]=='?') T[i]=Q.front(),Q.pop();
  assert(count(ALL(T),'?')==0);
  if(win>=(N+1)/2) {
    cout<<"YES"<<endl;
    cout<<T<<endl;
  } else {
    cout<<"NO"<<endl;
  }
  /*
  VVV<int> dp(3,VV<int>(N,VI(N,0)));
  VVV<int> pre(3,VV<int>(N,VI(N,0)));
  REP(i,3) REPE(r,Y[0]) REPE(p,Y[1]) {
    
  }*/
  
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(i,T) {
    cin>>N>>Y[0]>>Y[1]>>Y[2]>>S;
    solve();
  }
  
  return 0;
}
