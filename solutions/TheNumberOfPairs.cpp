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
struct PrimeFact {
public:
  PrimeFact(int N): N(N) {
    // make prime table by sieve
    divp.resize(N+1,0);
    for(int p=2; p<=this->N; ++p) if(divp[p]==0) {
      P.push_back(p);
      divp[p]=p;
      for(long long q=1LL*p*p; q<=N; q+=p) if(divp[q]==0) divp[q]=p;
    }
  }
  vector<int> fact(int n) {
    vector<int> res;
    while(n>1) res.push_back(divp[n]), n/=divp[n];
    return res;
  }
  int factn(int n) {
    unordered_set<int> res;
    while(n>1) res.emplace(divp[n]), n/=divp[n];
    return res.size();
  }
  vector<int> divs(int n) {
    vector<int> res={1};
    while(n>1) {
      int p=divp[n],cnt=1,pp=p;
      while(n%p==0) n/=p,++cnt;
      int sz=res.size();
      for(int k=1; k<cnt; ++k) {
        for(int j=0; j<sz; ++j) res.push_back(res[j]*pp);
        pp*=p;
      }
    }
    return res;
  }
  vector<int> P; // list of prime numbers
private:
  int N;
  vector<int> divp;
};
template<typename Integer>
vector<Integer> divisors(Integer N) {
  assert(N>=1);
  vector<Integer> res;
  for(Integer p=1; p*p<=N; ++p) if(N%p==0) {
    res.push_back(p);
    if(p!=N/p) res.push_back(N/p);
  }
  sort(res.begin(),res.end());
  return res;
}
// $ cp-batch TheNumberOfPairs | diff TheNumberOfPairs.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheNumberOfPairs.cpp && ./a.out

/*

 3/18/2021

 8:54-9:40 TLE
 10:00 give up

 23:00-23:23 Referred to ACed code and figured out that O(log N) prime factorization is hitting TLE. Fixed and got AC

 https://codeforces.com/blog/entry/88812
 https://twitter.com/laycrs/status/1372591337598455810

 */

int C,D,X;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  const int MAX_N=2e7+100;
  VI pfact(MAX_N,0);
  for(int p=2; p<MAX_N; ++p) if(pfact[p]==0) {
    for(long long q=p; q<MAX_N; q+=p) pfact[q]++;
  }

  int t; cin>>t;
  while(t--) {
    cin>>C>>D>>X;

    LL res=0;
    VI divs=divisors(X);
    FORR(g, divs) {
      int d=X/g;
      int dd=d+D;
      if(dd%C!=0) continue;
      int ab=dd/C;
      //auto ps=pf.fact(ab);
      //unordered_set<int> S;
      //FORR(p,ps) S.emplace(p);
      res+=1LL<<(pfact[ab]);
    }
    cout<<res<<endl;
  }

  return 0;
}
