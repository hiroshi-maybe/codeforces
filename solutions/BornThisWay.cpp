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
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ' '; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch BornThisWay | diff BornThisWay.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BornThisWay.cpp && ./a.out

/*
 
 6/1/2019
 
 7:41-8:24 WA
 8:31 WA
 8:47 WA
 8:52 WA. Give up
 
 6/2/2019
 
 10:53-11:43 figured out bug of my design
 11:43-12:04, 12:54-13:15 read editorial and got AC
 
 https://codeforces.com/blog/entry/67366
 
 The most important property that I missed:
 If we cancel `x` flights from A, canceling first `x` flights is optimal (monotonic)
 
 Suppose we cancel flight A[0] and A[2].
 Because A[1]<A[2], available flight for A[1] is superset of A[2].
 Canceling A[0] and A[1] cannot be worse than A[0] and A[2].
 
 I didn't come up with an idea to fix # of canceled flights in A... 😞
 I could not even figure out that selection of A or B must be consecutive 😞😞
 
 */

const int MAX_N=1e6+1;
LL T1,T2,A[MAX_N],B[MAX_N];
int N,M,K;

LL solve() {
  if(K>=min(N,M)) return -1;
  int j=0;
  REPE(x,K) {
    int p=lower_bound(B,B+M,A[x]+T1)-B;
    p+=K-x;
    SMAX(j,p);
  }
  return j>=M?-1:B[j]+T2;
}

int X[MAX_N];
LL solve_wrong() {
  REP(i,N) {
    int p=lower_bound(B,B+M,A[i]+T1)-B;
    X[i]=p;
  }
  dumpC(X,X+N);
  int k=K,j=X[0];
  REP(i,N) if(j<M&&k>0) {
    j=max(j,X[i]);
    if(X[i]<j) continue;
    if(i==N-1) {
      //++j,--k;
      j=M;
//      dump(i,j);
      continue;
    }
    int a=X[i],b=X[i+1];
    if(a<b) --k,j=X[i+1];
    else ++j,--k;
//    dump(a,b,j,k);
  }
//  dump(k,j,M);
  LL res=k<=0&&j<M?B[j]+T2:-1;
  return res;
}

LL correct() {
  if(K>=N||K>=M) return -1;
  LL mx = 0;
  FOR(i,0,K+1){
    LL tt = A[i]+T1;
    LL k1 = K-i;
    LL p = lower_bound(B,B+M,tt)-B+k1;
    if(p>=M){
      return -1;
    }
    mx = max(mx,B[p]+T2);
  }
  return mx;
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
  N=genRandNum(1,10),M=genRandNum(1,10);
  VI as=genRandSeq(N,1,10),bs=genRandSeq(M,1,10);
  sort(ALL(as)),sort(ALL(bs));
  as.erase(unique(ALL(as)),as.end());
  bs.erase(unique(ALL(bs)),bs.end());
  N=SZ(as),M=SZ(bs);
  REP(i,N) A[i]=as[i];
  REP(i,M) B[i]=bs[i];
  T1=genRandNum(1,5),T2=genRandNum(1,5),K=genRandNum(1,N+M);
  LL a=correct(),b=solve();
  if(a!=b) {
    dump(a,b);
    cerr<<N<<" "<<M<<" "<<T1<<" "<<T2<<" "<<K<<endl;
    dumpc(as);
    dumpc(bs);
  }
  assert(a==b);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N>>M>>T1>>T2>>K;
  REP(i,N) cin>>A[i];
  REP(i,M) cin>>B[i];
  cout<<solve()<<endl;
  
  return 0;
}
