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

// $ cp-batch DreamoonLikesColoring | diff DreamoonLikesColoring.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DreamoonLikesColoring.cpp && ./a.out

/*
 
 4/3/2020
 
 8:13-9:12 AC
 
 https://codeforces.com/blog/entry/75559
 The editorial solution is simpler by firstly checking sum { L[i] } >= N
 
 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N,M;

void nope() {
  println("-1");
}
void solve() {
  /*
  LL sum=accumulate(A,A+M,0LL);
  if(sum<N) nope();
  vector<LL> cum(M+1,0);
  REP(i,M) cum[i+1]=cum[i]+L[i];*/
  vector<pair<LL,LL>> R(M+1),L(M+1);
  R[M]={N,(LL)1e8};
  for(int i=M-1; i>=0; --i) {
    LL lb=R[i+1].first-A[i];
    LL hb=min(R[i+1].second-1,(LL)N-A[i]);
    R[i]={lb,hb};
    dump(i,lb,hb);
  }
  REP(i,M) {
    LL hb=(i==0?0:R[i-1].second+A[i-1]);
    LL lb=i;
    L[i]={lb,hb};
    dump(i,lb,hb);
  }
  
  VI res(M);
  REP(i,M) {
    LL l=max(L[i].first,R[i].first),r=min(L[i].second,R[i].second);
    if(r<l) {
      nope();
      return;
    }
    assert(0<=l&&l<N);
    res[i]=(int)l;
  }
  REP(i,M) printf("%d ", res[i]+1);
  println("");
  
  VI C(N,-1);
  REP(i,M) {
    FOR(j,res[i],res[i]+A[i]) C[j]=i;
  }
  assert(count(ALL(C),-1)==0);
  set<int> S(ALL(C));
  REP(i,M) assert(S.count(i)>0);
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
void test() {
  N=genRandNum(1,1000);
  M=genRandNum(1,N+1);
  VI L=genRandSeq(M,1,N+1);
  REP(i,M) A[i]=L[i];
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  while(true) test();
  
  cin>>N>>M;
  REP(i,M) cin>>A[i];
  solve();
  
  return 0;
}
