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

// $ cp-batch Messy | diff Messy.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Messy.cpp && ./a.out

/*
 
 11/24/2019
 
 0:35-0:59 AC
 
 https://twitter.com/hanseilimak/status/1198755546221821952
 
 */

string S;
int N,K;

void solve() {
  string T(N,'?');
  for(int i=0; i<N; i+=2) {
    if(K>1) T[i]='(',T[i+1]=')',--K;
    else {
      int x=(N-i)/2;
      FOR(j,i,i+x) T[j]='(';
      FOR(j,i+x,i+2*x) T[j]=')';
      break;
    }
  }
//  dump(T);
  assert(count(ALL(T),'(')==N/2);
  assert(count(ALL(T),')')==N/2);
  vector<II> res;
  REP(i,N) if(S[i]!=T[i]) {
    bool found=false;
    FOR(j,i+1,N) if(T[i]==S[j]) {
      found=true;
      res.emplace_back(i,j);
      reverse(S.begin()+i,S.begin()+j+1);
      assert(S[i]==T[i]);
      break;
    }
    assert(found);
  }
  assert(S==T);
  println("%d",SZ(res));
  REP(i,SZ(res)) {
    println("%d %d", res[i].first+1,res[i].second+1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(_,T) {
    cin>>N>>K>>S;
    solve();
  }
  
  return 0;
}
