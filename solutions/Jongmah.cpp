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

// $ cp-batch Jongmah | diff Jongmah.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Jongmah.cpp && ./a.out

/*
 
 2/7/2019
 
 7:03-7:33, 10:15-10:40 give up
 
 possible options:
  - dp
  - greedy
 
 2/9/2019
 
 16:10-17:10 read editorials and got AC
 
 https://codeforces.com/blog/entry/65079
 https://twishort.com/O7vnc
 https://naoyat.hatenablog.jp/entry/CodeforcesGlobalRound1
 
 Normal dp needs O(N^3) time. It's necessary to take some greedy approach.
 Analyzing extreme case is typical to find greedy strategy.
 If we have below:
 
 a:   100
 a+1: 100
 a+2: 100
 
 {a,a,a}x33,{a+1,a+1,a+1}x33,{a+2,a+2,a+2}x33,{a,a+1,a+2}x1
 = {a,a+1,a+2}x100
 
 Thus we can assume that {a,a+1,a+2} at most 2. The works case is below:
 {a,a+1,a+2}x2
   {a+1,a+2,a+3}x2
       {a+2,a+3,a+4}x2

 In this case {a+2} is used for consecutive tuple 6 times.
 Thus dp[N][7][7] is sufficient state to do dp.
 
 */

const int MAX_N=1e6+10,MAX_V=1e6;
int A[MAX_N];
int N,M;

int B[MAX_N];
int dp[2][7][7];
void solve() {
  REP(i,N)B[A[i]]++;
  ZERO(dp);
  FORE(i,1,(int)MAX_V)REP(a,7)REP(b,7)REP(k,3) if(b+k<7) {
    int p=i%2,pp=1-p;
//    dump(a,b+k,k);
    if(B[i]>=a+k&&B[i+1]>=b+k&&B[i+2]>=k) SMAX(dp[pp][b+k][k],dp[p][a][b]+k+(B[i]-a-k)/3);
  }
  cout<<dp[(MAX_V+1)%2][0][0]<<endl;
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
