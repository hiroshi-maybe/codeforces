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
  vector<long long> fact(long long n) {
    vector<long long> res;
    while(n>1) res.push_back(divp[n]), n/=divp[n];
    sort(res.begin(),res.end());
    return res;
  }
  vector<int> P; // list of prime numbers
private:
  int N;
  vector<int> divp;
};
#define UNIQUE(A) (A).erase(std::unique((A).begin(), (A).end()), (A).end());
// $ cp-batch TwoDivisors | diff TwoDivisors.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TwoDivisors.cpp && ./a.out

/*

 6/11/2020

 8:26-8:42 WA
 9:35 give up

 6/13/2020

 17:00-17:40 read editorial and got AC

 https://codeforces.com/blog/entry/78735
 https://twitter.com/hanseilimak/status/1271964300471496704
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.vhbrufsspjhq

 https://twitter.com/laycrs/status/1271118788939796480
 https://twitter.com/ei1333/status/1271119558280011776
 https://twitter.com/kzyKT_M/status/1271119704531193856

 */

vector<LL> divisors(LL N) {
  assert(N>=1);
  vector<LL> res;
  for(LL p=1; p*p<=N; ++p) if(N%p==0) {
    res.push_back(p);
    if(p!=N/p) res.push_back(N/p);
  }
  sort(res.begin(),res.end());
  return res;
}

const int MAX_N=1e6+1;
int A[MAX_N];
int N;
LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
const int maxa=1e7;
void solve() {
  PrimeFact pf(maxa);
  vector<pair<LL,LL>> res(N);
  REP(i,N) {
    vector<LL> ps=pf.fact(A[i]);
    UNIQUE(ps);
    if(SZ(ps)<2) {
      res[i]={-1,-1};
    } else {
      //dumpc(ps);
      res[i]={ps[0],1};
      FOR(j,1,SZ(ps)) res[i].second*=ps[j];
      /*
      int a=A[i];
      REP(k,SZ(ps))REP(j,k) {
        dump(a,ps[j],ps[k]);
        dump(gcd(a,ps[j]+ps[k]));
        if(gcd(a,ps[j]+ps[k])==1) {
          res[i]={ps[j],ps[k]};
          assert(a%ps[k]==0);
          assert(a%ps[j]==0);
        }
      }*/
    }
  }

/*
  if(res[0].first==-1&&res[0].second==-1) {
    vector<LL> ds=divisors(A[0]);
    REP(j,SZ(ds))REP(i,j)if(ds[i]!=1&&ds[j]!=1) {
      if(gcd(ds[i]+ds[j],A[0])==1) {
        dump(ds[i],ds[j],A[0]);
      }
      //assert(gcd(ds[i]+ds[j],A[0])!=1);
    }
  }*/

  REP(i,N) cout<<res[i].first<<" ";
  cout<<endl;
  REP(i,N) cout<<res[i].second<<" ";
  cout<<endl;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
void test() {
  N=1;
  A[0]=genRandNum(2,maxa+1);
  dump(A[0]);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  cin>>N;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
