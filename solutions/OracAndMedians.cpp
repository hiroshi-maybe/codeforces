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

// $ cp-batch OracAndMedians | diff OracAndMedians.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address OracAndMedians.cpp && ./a.out

/*
 
 5/12/2020
 
 6:16-8:05 give up
 10:00-10:10 read twitter solutions and got AC
 
 https://twitter.com/hanseilimak/status/1260619655602860032
 
 https://codeforces.com/blog/entry/77284
 https://twitter.com/n_vip/status/1260224890495352833
 https://twitter.com/tsutaj/status/1260224808781926403
 https://twitter.com/kzyKT_M/status/1260224579630292993
 https://twitter.com/heno_code/status/1260225345073983488
 https://twitter.com/laycrs/status/1260225247426445312
 https://twitter.com/satanic0258/status/1260227373376475136
 https://twitter.com/satanic0258/status/1260230460581396481
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,K;

bool solve() {
  int kcnt=count(A,A+N,K);
  if(kcnt==0) return false;
  if(N==1) return true;
  REP(i,N-1) if(A[i]>=K&&A[i+1]>=K) return true;
  REP(i,N-2) if(A[i]>=K&&A[i+2]>=K) return true;
  return false;
}

bool solve_wrong() {
  int kcnt=count(A,A+N,K);
  if(kcnt==N) return true;
  REP(i,N-1) if(A[i]==K&&A[i+1]==K) return true;
  
  int p=-100;
  map<int,VI> cump;
  int cnt0=0,cnt1=0;
  cump[0].push_back(-1);
  REP(i,N) {
    if(A[i]==K) p=i;
    (A[i]<K?cnt0:cnt1)++;
    int cur=cnt1-cnt0;
    if(cump.count(cur)) {
      int lpos=cump[cur].front();
      if(lpos!=i-1) {
        dump(i,lpos,cur);
        if(lpos<p) return true;
      }
    }
    if(cump.count(cur-1)) {
      int lpos=cump[cur-1].front();
      if(lpos!=i-1) {
        dump(i,lpos,p,cur-1);
        if(lpos<p) return true;
      }
    }
    dump(i,cnt0,cnt1,cur,p);
    cump[cur].push_back(i);
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int t; cin>>t;
  while(t--) {
    cin>>N>>K;
    REP(i,N) cin>>A[i];
    cout<<(solve()?"yes":"no")<<endl;
  }
  
  return 0;
}
