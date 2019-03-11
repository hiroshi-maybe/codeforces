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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch SystemTesting | diff SystemTesting.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SystemTesting.cpp && ./a.out

/*
 
 3/3/2019
 
 8:30-10:53 ugly contest, ugly problem statement. Each `i` solution should not be counted duplicated. fuck.
 
 https://codeforces.com/blog/entry/65679
 
 */

const int MAX_N=1e3+1;
int A[MAX_N];
int N,K;

void solve() {
  int m=0,t=0;
  SETI res;
  set<II> Q;
  auto proc=[&]() {
    if(SZ(Q)==0) return;
    auto it=Q.begin();
    int dur,ii; tie(dur,ii)=*it;
    int d=floor(100.0*m/N+0.5);
    t+=dur;
    dump(t,ii,dur,d,m,SZ(res));
    set<II> Q2;
    FORR(tu,Q) {
      int rem,j; tie(rem,j)=tu;
      int a=A[j]-rem+1,b=a+dur-1;
      dump(d,j,rem,a,b);
      if(a<=d&&d<=b) res.emplace(j);
      if(rem!=dur) {
        Q2.emplace(rem-dur,j);
      } else {
        ++m;
      }
    }
    swap(Q,Q2);
  };
  REP(i,N) {
    Q.emplace(A[i],i);
    if(SZ(Q)>=K) proc();
    assert(SZ(Q)<=K);
  }
  while(SZ(Q)) proc();
  cout<<SZ(res)<<endl;
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
