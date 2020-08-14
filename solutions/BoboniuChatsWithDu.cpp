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

// $ cp-batch BoboniuChatsWithDu | diff BoboniuChatsWithDu.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BoboniuChatsWithDu.cpp && ./a.out

/*

 8/12/2020

 8:39-9:05 WA
 9:58 figured out {11,11,11,100,12}, M=11,D=2 case and got RE

 22:05-22:23 AC after fixing negative index bug

 https://twitter.com/hanseilimak/status/1293941393400840192
 https://codeforces.com/blog/entry/81355

 */

const int MAX_N=1e6+1;
LL A[MAX_N],M;
int N,D;

LL solve() {
  VV<LL> S(2);
  REP(i,N) (A[i]>M?S[0]:S[1]).push_back(A[i]);
  REP(i,2) sort(ALL(S[i])),reverse(ALL(S[i]));
  VV<LL> cum(2);
  REP(i,2) {
    cum[i]=vector<LL>(SZ(S[i])+1);
    REP(j,SZ(S[i])) cum[i][j+1]=cum[i][j]+S[i][j];
  }

  LL res=0;
  REPE(y,SZ(S[1])) {
    int x=(N-y+D)/(D+1);
    if(x>SZ(S[0])) continue;
    SMAX(res,cum[0][x]+cum[1][y]);
  }
  return res;
}

LL solve_org() {
  LL res=0;
  VV<LL> S(2);
  REP(i,N) (A[i]>M?S[0]:S[1]).push_back(A[i]);
  REP(i,2) sort(ALL(S[i])),reverse(ALL(S[i]));
  //dumpc(S[0]);
  //dumpc(S[1]);
  VV<LL> cum(2);
  REP(i,2) {
    cum[i]=vector<LL>(SZ(S[i])+1);
    REP(j,SZ(S[i])) cum[i][j+1]=cum[i][j]+S[i][j];
  }

  if(SZ(S[1])==N) res=cum[1][N];
  FORE(x,1,SZ(S[0])) {
    LL hb=(LL)N-((LL)x*(D+1)-D),lb=hb-D;
    //dump(x,lb,hb);
    if(hb<0) continue;
    if(SZ(S[1])<lb) continue;
    int cnt1=(int)min(hb,(LL)SZ(S[1]));
    //dump(x,cnt1);
    //assert(SZ(S[0])-x+SZ(S[1])==rem);
    //if(rem>SZ(S[1])||rem2>SZ(S[1])||rem+rem2>SZ(S[1])) continue;
    LL a=cum[0][x],b=cum[1][cnt1];
    //dump(x,a,b,a+b);
    SMAX(res,a+b);
  }
  return res;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
template <typename Integer>
vector<Integer> genRandSeq(int size, Integer lb, Integer ub) {
  if (size==0) return {};
  vector<Integer> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  N=genRandNum(1,10);
  D=genRandNum(1,N+1);
  M=genRandNum(0,10);
  VI as=genRandSeq(N,0,10);
  REP(i,N) A[i]=as[i];
  println("%d %d %lld", N,D,M);
  REP(i,N) printf("%d ",as[i]);
  println("");
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  cin>>N>>D>>M;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;

  return 0;
}
