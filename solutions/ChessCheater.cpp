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

// $ cp-batch ChessCheater | diff ChessCheater.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ChessCheater.cpp && ./a.out

/*

 10/10/2020

 8:02-8:54 AC

 https://twitter.com/hanseilimak/status/1317152012866183168
 https://codeforces.com/blog/entry/83553

 */

//const int MAX_N=1e6+1;
int N,K;
string S;

int solve() {
  VI A(N,0);
  auto f=[&](int i) {
    if(i>0&&S[i-1]=='W') return 2;
    return 1;
  };

  VI rl={0};
  REP(i,N) if(S[i]=='L') {
    if(i>0&&S[i-1]=='W') rl.push_back(0);
    rl.back()++;
  }
  if(S[N-1]=='W') rl.push_back(0);

  int M=SZ(rl);
  dumpc(rl);
  if(M==1) {
    assert(S[0]=='L'&&S[N-1]=='L');
    int a=min(K,N);
    dump(a,K,N);
    return max(0,2*a-1);
  }

  vector<II> xs;
  REP(i,M) {
    if(i==0) xs.emplace_back(2,rl[i]);
    else if(i==M-1) xs.emplace_back(1,rl[i]);
    else xs.emplace_back(0,rl[i]);
  }

  sort(ALL(xs));
  int res=0;
  REP(i,N) if(S[i]=='W') res+=f(i);
  dump(res);
  dumpc(xs);

  int k=K,i=0;
  while(i<M&&k>0) {
    int t=xs[i].first,x=xs[i].second;
    dump(t,x);
    int y=min(x,k);
    if(t==0) {
      res+=2*y;
      if(y==x) ++res;
    } else if(t==1) {
      res+=2*y;
    } else if(t==2) {
      res+=2*y;
    }
    dump(t,x,y,k);
    k-=y;
    ++i;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>K>>S;
    cout<<solve()<<endl;
  }

  return 0;
}
