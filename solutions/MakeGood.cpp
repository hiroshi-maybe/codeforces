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

// $ cp-batch MakeGood | diff MakeGood.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MakeGood.cpp && ./a.out

/*
 
 12/29/2019
 
 6:18-7:07 WA
 7:16 AC
 
 https://codeforces.com/blog/entry/72611
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

string n2bin(long long n) {
  assert(n>=0);
  string res="";
  while(n>0) res+=(n%2LL?'1':'0'),n/=2LL;
  return string(res.rbegin(), res.rend());
}

void solve() {
  LL sum=0,ex=0;
  REP(i,N) sum+=A[i],ex^=A[i];
//  dump(sum,ex,ex*2);
  vector<LL> B;
  if(sum!=ex*2) {
    if((sum&1)||sum>ex*2) {
      B.push_back(0LL);
      if(sum&1) B[0]+=1,sum+=1,ex^=1;
      if(sum>ex*2) B[0]|=(1LL<<50),sum+=(1LL<<50),ex^=(1LL<<50);
      
//      dump(B[0],sum,ex,ex*2);
    }
  }
  if(sum!=ex*2) {
    assert(sum<ex*2);
    assert((sum&1)==0);
    LL dif=ex*2-sum;
    string s=n2bin(dif);
    reverse(ALL(s));
//    dump(s);
    LL a=0,b=0;
    REP(i,SZ(s)) if(s[i]=='1') {
      LL x=1LL<<(i-1);
      a|=x,b|=x;
    }
    sum+=a+b;
    assert(sum==ex*2);
    B.push_back(a),B.push_back(b);
  }
  println("%d",SZ(B));
  REP(i,SZ(B)) printf("%lld ", B[i]);
  println("");
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
  N=genRandNum(1,5);
  VI X=genRandSeq(N,0,8);
  REP(i,N) A[i]=X[i];
  dump(N);
  dumpC(A,A+N);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  int T; cin>>T;
  REP(_,T) {
    cin>>N;
    REP(i,N)cin>>A[i];
    solve();
  }
  
  return 0;
}
