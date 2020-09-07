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

// $ cp-batch MultiplesOfLength | diff MultiplesOfLength.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MultiplesOfLength.cpp && ./a.out

/*

 8/30/2020

 8:29-9:19 AC

 https://twitter.com/hanseilimak/status/1303045027770236929
 https://codeforces.com/blog/entry/82142

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void solve() {
  if(N==1) {
    cout<<"1 1"<<endl;
    cout<<-A[0]<<endl;
    REP(_,2) {
      cout<<"1 1"<<endl;
      cout<<"0"<<endl;
    }
    return;
  }

  vector<LL> B(A,A+N);
  REP(i,N) B[i]=(A[i]%N+N)%N;
  dumpc(B);
  vector<LL> X(N+1,-1);
  X[N]=0;
  REP(i,N) {
    int a=(int)(((LL)(N-1)*i)%N);
    X[a]=(LL)(N-1)*i;
  }
  assert(count(ALL(X),-1)==0);
  cout<<1<<" "<<N-1<<endl;
  REP(i,N-1) {
    LL a=X[(N-B[i])%N];
    cout<<a<<" ";
    A[i]+=a;
  }
  cout<<endl;

  cout<<N<<" "<<N<<endl;
  LL a=(N-B[N-1])%N;
  cout<<a<<endl;
  A[N-1]+=a;

  cout<<1<<" "<<N<<endl;
  REP(i,N) {
    assert(A[i]%N==0);
    cout<<-A[i]<<" ";
  }
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
