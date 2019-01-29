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

// $ cp-batch PrefixesAndSuffixes | diff PrefixesAndSuffixes.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PrefixesAndSuffixes.cpp && ./a.out

/*
 
 1/25/2019
 
 14:11-14:48 tons of impl bugs. fuck.
 
 Bug1: comparator should return true only when lhs is "strictly" smaller
 
 https://codeforces.com/blog/entry/63961
 http://tsutaj.hatenablog.com/entry/2018/12/28/052918
 
 */

const int MAX_N=1e3+1;
string S[2*MAX_N];
int N;

void f(vector<pair<string,int>> X, bool pre) {
  vector<int> res(2*N-2);
  string p=X[pre].first,s=X[pre^1].first;
  res[pre]=1,res[pre^1]=0;
  for(int i=2; i<2*N-2; i+=2) {
    int len=i/2+1;
    string x=X[i].first,y=X[i+1].first;
//    dump4(p,s,x,y);
    if(x.substr(0,len-1)==p&&y.substr(1,len-1)==s) {
      res[i]=1;
      p=x,s=y;
    } else if(x.substr(1,len-1)==s&&y.substr(0,len-1)==p) {
      res[i+1]=1;
      p=y,s=x;
    } else {
      return;
    }
  }
  string ans(2*N-2,'?');
  REP(i,SZ(X)) {
    int j=X[i].second;
    if(res[i]) ans[j]='P';
    else ans[j]='S';
  }
  cout<<ans<<endl;
  exit(0);
}
void solve() {
//  vector<pair<string,int>> X(2*N-2,{"",-1});
  vector<pair<string,int>> X;
  REP(i,2*N-2) {
    /*
    int L=SZ(S[i]);
    int j=2*(L-1);
    if(X[j].second==-1) X[j]={S[i],i};
    else X[j+1]={S[i],i};*/
    X.emplace_back(S[i],i);
  }
  sort(ALL(X),[&](pair<string,int> a, pair<string,int> b) {
    return SZ(a.first)<SZ(b.first);
  });
  f(X,0),f(X,1);
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,2*N-2) cin>>S[i];
  solve();
  
  return 0;
}
