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

// $ cp-batch ChocolateBunny | diff ChocolateBunny.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ChocolateBunny.cpp && ./a.out

/*

 9/8/2020

 8:26-9:35 give up
 10:10-10:29 read tweets and got AC

 https://twitter.com/hanseilimak/status/1304291614160871425
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.olxp8myvoagb

 https://codeforces.com/blog/entry/82417

 https://twitter.com/ei1333/status/1303371416926957568
 https://twitter.com/kzyKT_M/status/1303371861917458433
 https://twitter.com/akakimidori/status/1303372616711847937

 */

int N;

VI ex;

int cnt=0;
int ask(int i, int j) {
  ++cnt;
  assert(cnt<=2*N);
  cout<<"? "<<i+1<<" "<<j+1<<endl;

  int res;

  #ifdef __KUMATRACE__
  res=ex[i]%ex[j];
  #else
  cin>>res;
  #endif

  if(res==-1) exit(0);
  return res;
}

void answer(VI P) {
  cout<<"!";
  REP(i,N) cout<<" "<<P[i];
  cout<<endl;

  #ifdef __KUMATRACE__
  assert(P==ex);
  #endif

  exit(0);
}

void solve() {
  //if(N==1) answer({1});
  VI P(N,-1);
  VI S(N); iota(ALL(S),0);
  VI viz(N+1,0);
  while(SZ(S)>1) {
    int i=S[SZ(S)-1],j=S[SZ(S)-2];
    int a=ask(i,j),b=ask(j,i);
    int rem=j,done=i;
    assert(a!=b);
    if(a<b) swap(rem,done);
    P[done]=max(a,b);
    REP(_,2) S.pop_back();
    S.push_back(rem);
    viz[max(a,b)]=1;
  }
  dumpc(S);
  assert(SZ(S)==1);
  FORE(i,1,N) if(viz[i]==0) {
    REP(j,N) if(P[j]==-1) P[j]=i;
    break;
  }

  answer(P);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;

  #ifdef __KUMATRACE__
  ex=VI(N);
  REP(i,N) cin>>ex[i];
  #endif

  solve();

  return 0;
}
