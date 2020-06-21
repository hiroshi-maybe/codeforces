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

// $ cp-batch OddEvenSubsequence | diff OddEvenSubsequence.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address OddEvenSubsequence.cpp && ./a.out

/*

 6/20/2020

 8:30-9:55 give up
 11:45-12:46 read @kmjp's code and got AC

 https://twitter.com/hanseilimak/status/1274425176415821825
 https://codeforces.com/blog/entry/79107

 https://twitter.com/kzyKT_M/status/1274384684349157376

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N,K;

vector<II> as;
bool ok(int p) {
  int x=as[p].first;
  REP(par,2) {
    int len=0;
    REP(i,N) {
      if(len%2==par) {
        if(A[i]<=x) len+=1;
      } else {
        len+=1;
      }
    }
    //dump(par,len,K);
    if(len>=K) return true;
  }
  return false;
}

void solve() {
  REP(i,N) as.emplace_back(A[i],i);
  sort(ALL(as));
  int good=N-1,bad=-1;
  while(abs(good-bad)>1) {
    int mid=(good+bad)/2;
    bool res=ok(mid);
    //dump(mid,as[mid].first,as[mid].second,res);
    (res?good:bad)=mid;
  }
  cout<<as[good].first<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>K;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
