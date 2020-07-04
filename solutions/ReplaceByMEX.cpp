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
// $ cp-batch ReplaceByMEX | diff ReplaceByMEX.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ReplaceByMEX.cpp && ./a.out

/*

 7/4/2020

 9:26-9:51 WA
 10:07 AC

 https://twitter.com/hanseilimak/status/1279548829822406656
 https://codeforces.com/blog/entry/79731

 https://twitter.com/kzyKT_M/status/1279464020223770624
 https://twitter.com/natsugir/status/1279471571392856065


 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

int mex(VI &A) {
  set<int> S;
  REP(i,N) S.emplace(A[i]);
  REP(i,N+1) if(!S.count(i)) return i;
  assert(false);
}
void solve() {
  VI exp(N); REP(i,N) exp[i]=i;
  VI as(A,A+N);
  VI res;
  while(as!=exp) {
    int m=mex(as);
    int i=m;
    if(m==N) {
      bool ok=false;
      REP(j,N)if(as.at(j)!=j) {
        i=j;
        ok=true;
        break;
      }
      assert(ok);
    }
    dump(i,m);
    res.push_back(i);
    as[i]=m;
    dumpc(as);
    assert(SZ(res)<=2*N);
  }
  cout<<SZ(res)<<endl;
  REP(i,SZ(res)) cout<<res[i]+1<<" ";
  cout<<endl;
}

void test() {
  N=genRandNum(3,1000);
  VI as=genRandSeq(N,0,N+1);
  REP(i,N) A[i]=as[i];
  dump(N);
  dumpc(as);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N) cin>>A[i];
    solve();
  }

  return 0;
}
