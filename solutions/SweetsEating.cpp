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

// $ cp-batch SweetsEating | diff SweetsEating.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SweetsEating.cpp && ./a.out

/*
 
 11/16/2019
 
 7:18-7:50 AC
 
 https://codeforces.com/blog/entry/71489
 https://twitter.com/hanseilimak/status/1196140364521865216
 https://codeforces.com/contest/1253/submission/65177633
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,M;

vector<LL> B[MAX_N],cum[MAX_N];

void solve() {
  sort(A,A+N);
  vector<LL> B(M,0);
  LL res=0;
  REP(k,N) {
    B[k%M]+=A[k];
    res+=B[k%M];
    printf("%lld ", res);
  }
  println("");
}

void solve_org() {
  sort(A,A+N);
  REP(i,N) B[i%M].push_back(A[i]);
  REP(i,M) {
    cum[i]=vector<LL>(SZ(B[i])+1);
    REP(j,SZ(B[i])) cum[i][j+1]=cum[i][j]+B[i][j];
  }
  vector<LL> res(N);
  REP(k,N) {
    res[k]=k==0?0:res[k-1];
    assert(k/M+1<SZ(cum[k%M]));
    res[k]+=cum[k%M][k/M+1];
  }
  REP(i,N) printf("%lld ", res[i]);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
