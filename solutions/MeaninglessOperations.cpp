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

// $ cp-batch MeaninglessOperations | diff MeaninglessOperations.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MeaninglessOperations.cpp && ./a.out

/*
 
 2/7/2019
 
 6:23-7:02 pass
 
 https://codeforces.com/blog/entry/65079
 https://twishort.com/O7vnc
 https://naoyat.hatenablog.jp/entry/CodeforcesGlobalRound1
 
 a) a!=2^k-1
 
 It's possible to find `b` s.t. a^b=2^k-1, a&b=0. Thus res=2^k-1
 
 b) a==2^k-1
 
 Generally a&b=b, a^b=a-b. Thus gcd(a^b,a&b)=gcd(b,a-b)=gcd(a,b)
 max { gcd(a,b) : 0<b<a } = max { divisor of a }
 
 O(sqrt(A)*Q) ≈ 9*10^6
 
 */

const int MAX_N=1e3+1;
LL A[MAX_N];
int Q;

int f(int a) {
  int n=0;
  REP(j,30) if((a>>j)&1) n=j;
  ++n;
  int mask=(1<<n)-1;
  if(a!=mask) return mask;
  for(int p=2; p*p<=a; ++p) if(a%p==0) {
    return a/p;
  }
  return 1;
}

VI as={1,1,5,1,21,1,85,73,341,89,1365,1,5461,4681,21845,1,87381,1,349525,299593,1398101,178481,5592405,1082401};
int f_org(int a) {
  int n=0;
  REP(j,30) if((a>>j)&1) n=j;
  ++n;
  if(a==((1<<n)-1)) {
//    dump(a,n,as[n-2]);
    return as[n-2];
  } else return (1<<n)-1;
}

void solve() {
  REP(i,Q) {
    int a=A[i];
    cout<<f(a)<<endl;
  }
}

int gcd(int a, int b) { return b==0?a:gcd(b,a%b); }
int g(int a) {
  int res=0;
  FOR(b,1,a) {
//    dump(a,b,a^b,a&b,gcd(a^b,a&b));
    SMAX(res,gcd(a^b,a&b));
  }
  dump(a,res);
  return res;
}
void test() {
  FORE(a,2,1000) {
    int x=f(a),y=g(a);
    if(x!=y) dump(a,x,y);
//    assert(x==y);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  /*
  VI xs;
  FOR(i,2,26) {
    int x=g((1<<i)-1);
    xs.push_back(x);
  }
  dumpc(xs);*/
//  test();
  
  cin>>Q;
  REP(i,Q) cin>>A[i];
  solve();
  
  return 0;
}
