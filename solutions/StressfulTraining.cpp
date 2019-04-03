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

// $ cp-batch StressfulTraining | diff StressfulTraining.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address StressfulTraining.cpp && ./a.out

/*
 
 4/1/2019
 
 17:26-17:50 pause
 
 4/2/2019
 
 10:55-11:25, 14:40-15:05 WA on test #19.
 15:08 TLE on test case #22. Improved performance by replacing set<III> with priority queue
 15:31 TLE on test case #27
 15:44 got AC by replacing LL with int
 
 https://codeforces.com/blog/entry/65752
 http://kmjp.hatenablog.jp/entry/2019/03/28/0930
 https://betrue12.hateblo.jp/entry/2019/03/07/015040
 
 Condition: `x` laptops must be charged at most `x` times at time `x` for x=1..K
 If this condition was found, no simulation is needed and we don't need take care of order to process.
 If we naively simulate all, it takes O(N*K). However # of charge times is at most K. O(max(N,K)) is feasible.
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int B[MAX_N];
int N,K;

int T[MAX_N];
LL C[MAX_N];
bool ok_org(LL x) {
//  vector<LL> T(N,0),C(N);
  REP(i,N)T[i]=0;
  priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>> Q;
//  set<tuple<LL,LL,int>> Q;
  REP(i,N) {
    C[i]=A[i];
    int tt=(int)min((LL)MAX_N, A[i]/B[i]);
    Q.emplace(tt,-B[i],i);
  }
  REP(t,K) {
//    auto it=Q.begin();
    auto tup=Q.top();
    int exp; int i; tie(exp,ignore,i)=tup;
//    dump(t,exp,i);
    if(t>exp) return false;
    LL cur=C[i]-(t-T[i])*B[i]+x;
    C[i]=cur,T[i]=t;
//    Q.erase(it);
    Q.pop();
    int tt=(int)min((LL)MAX_N,t+cur/B[i]);
    Q.emplace(tt,-B[i],i);
  }
  return true;
}

LL cum[MAX_N];
bool ok(LL x) {
  ZERO(T),ZERO(cum);
  int cnt=0;
  REP(i,N) {
    int y=0;
    while(((LL)A[i]+x*y)/B[i]<K-1) {
      LL t=((LL)A[i]+x*y)/B[i];
      T[t]++;
      ++y,++cnt;
//      dump(x,i,y,cnt,t);
      if(cnt>=K) return false;
    }
  }
  REP(i,K) cum[i+1]=cum[i]+T[i];
//  dumpC(cum,cum+K+1);
  REP(i,K) if(cum[i]>i) return false;
  return true;
}

LL solve() {
  LL good=1e13,bad=-1;
  
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2;
    bool a=ok(m);
//    dump(m,a);
    (a?good:bad)=m;
  }
  if(!ok(good)) return -1;
  return good;
}



mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
LL genRandNum(LL lb, LL ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  LL x = rnd() % (LL)(ub - lb);
  return x + lb;
}
vector<LL> genRandSeq(int size, LL lb, LL ub) {
  if (size==0) return {};
  vector<LL> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
void test() {
  N=K=2e5;
  vector<LL> X=genRandSeq(N,1,1e12+1),Y=genRandSeq(N,1,1e7+1);
  REP(i,N)A[i]=X[i],B[i]=Y[i];
  LL res=solve();
  cout<<res<<endl;
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
//  dump(ok(50000000000000));
//  exit(0);
  
  scanf("%d %d",&N,&K);
  REP(i,N) scanf("%lld",&A[i]);
  REP(i,N) scanf("%d",&B[i]);
  cout<<solve()<<endl;
  
  return 0;
}
