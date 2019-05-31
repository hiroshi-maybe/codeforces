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

// $ cp-batch GoodTriple | diff GoodTriple.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GoodTriple.cpp && ./a.out

/*
 
 5/26/2019
 
 9:26-9:44 WA
 9:53 WA #11
 10:08 WA #13
 11:02 Looked at other's solutions and got AC
 
 https://codeforces.com/blog/entry/67241
 https://cinnamo-coder.hatenablog.com/entry/2019/05/27/152011
  
 */

//const int MAX_N=1e6+1;
string S;
int N;

LL solve() {
  N=SZ(S);
  LL res=0;
  vector<II> X;
  REP(i,N) {
    int k=1,r=N;
    while(true) {
      if(i+2*k>=N) break;
      if(S[i]==S[i+k]&&S[i]==S[i+2*k]) {
        r=i+2*k;
        break;
      }
      ++k;
    }
    if(r<N)X.emplace_back(r,i);
  }
  sort(ALL(X));
  /*
  dumpc(X);
  int minr=N;
  REP(i,SZ(X)) {
    int l,r; tie(l,r)=X[i];
    LL pre=i==0?-1:X[i-1].first;
    LL delta=l-pre;
    if(r>=minr) {
      res+=delta*(N-r);
    } else {
//      dump(i,(l-pre),(N-r),(l-pre)*(N-r),pre,(minr-r),pre*(minr-r));
      res+=(LL)(pre+1)*(minr-r)+delta*(N-r);
    }
//    dump(pre,l,ll,r,minr,res);
    SMIN(minr,r);
  }*/
  int lmax=-1;
  REP(i,SZ(X)) {
    int l,r; tie(r,l)=X[i];
    res+=(LL)(N-r)*max(0,l-lmax);
    SMAX(lmax,l);
  }
  return res;
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
LL bf() {
  set<II> res;
  
  REP(i,N) {
    int k=1,r=N;
    while(true) {
      if(i+2*k>=N) break;
      if(S[i]==S[i+k]&&S[i]==S[i+2*k]) {
        r=i+2*k;
        break;
      }
      ++k;
    }
    REPE(j,i)FOR(k,r,N) res.emplace(j,k);
  }
  return SZ(res);
}
void test() {
  N=8;
  VI A=genRandSeq(N,0,2);
  S=string(N,'0'); REP(i,N) S[i]='0'+A[i];
  LL a=solve(),b=bf();
  if(a!=b) {
    dump(S,a,b);
  }
  assert(a==b);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//    while(true) test();
  
  cin>>S;
  cout<<solve()<<endl;;
  
  return 0;
}
