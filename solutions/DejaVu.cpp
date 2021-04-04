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

// $ cp-batch DéjàVu | diff DéjàVu.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DéjàVu.cpp && ./a.out

/*

 4/3/2021

 7:35-8:08 AC

 https://codeforces.com/blog/entry/89319
 https://twitter.com/hanseilimak/status/1378589043118628868

 */

string S;
int N;

bool ispalin(string S) {
  int l=0,r=SZ(S)-1;
  while(l<r) {
    if(S[l]!=S[r]) return false;
    ++l,--r;
  }
  return true;
}

void solve() {
  N=SZ(S);
  int cnta=count(ALL(S),'a');
  if(cnta==N) {
    cout<<"NO"<<endl;
    return;
  }

  cout<<"YES"<<endl;

  if(ispalin(S)||cnta==0) {
    cout<<S+string(1,'a')<<endl;
    return;
  }

  vector<II> xs;
  REP(i,N) if(S[i]=='a') {
    if(i==0||S[i-1]!='a') xs.emplace_back(0,i);
    xs.back().first+=1;
  }
  auto maxl=*max_element(ALL(xs));
  string res=S;
  res.insert(maxl.second,1,'a');
  //dump(res);
  assert(!ispalin(res));
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
