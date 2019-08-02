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

// $ cp-batch MP3 | diff MP3.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MP3.cpp && ./a.out

/*
 
 7/31/2019
 
 14:52-15:26 AC
 
 https://codeforces.com/blog/entry/68812
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
LL I;
int N;

LL cum[MAX_N];
void solve() {
  map<int,int> cnt;
  REP(i,N) cnt[A[i]]++;
  vector<LL> B(A,A+N);
  sort(ALL(B)),B.erase(unique(B.begin(),B.end()),B.end());
  int M=SZ(B);
  REP(i,M) cum[i+1]=cum[i]+cnt[B[i]];
//  dumpc(B);
//  dumpC(cum,cum+M+1);
  LL res=1e17;
  REP(l,M) {
    int good=l,bad=M+1;
    while(abs(good-bad)>1) {
      int m=(good+bad)/2;
      int cnt=m-l;
      int k=0;
      while((1LL<<k)<cnt) ++k;
      if((LL)N*k<=I*8) good=m;
      else bad=m;
    }
    LL x=cum[l]+cum[M]-cum[good];
//    dump(l,good,cum[l],cum[M],cum[good],x)
    SMIN(res,x);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>I;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
