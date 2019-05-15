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

// $ cp-batch TheBeatles | diff TheBeatles.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheBeatles.cpp && ./a.out

/*
 
 5/13/2019
 
 20:36-21:28 WA on test case #11
 22:15 WA on test case #13. Give up
 
 # Wrong point of my first solution
 
 s≡A (mod K) or s≡-A (mod K)
 AND
 s+l≡B (mod K) or s+l≡-B (mod K)
 
 => B-A≡0 (mod K)
 
 This doesn't mean B-A≡0 (mod K) => original conditions 👎
 Also `K-A (mod N*K)` makes NO sense 👎👎
 Analyze `-A (mod K)` following problem statement
 
 # Wrong point of my second solution
 
 Same points as first solution. Additionally below is stupic.
 
 x*l=x*(p*k+B-A)≡0 (mod N*K)
 
 Due to this transformation, we cannot use x=N*K/gcd(l,N*K) which comes from a condition where `x` is minimum number of cycle to fill lcm(l,N*K).
 
 5/14/2019
 
 12:30-12:55, 21:50-23:40 read editorials and got AC
 
 https://cinnamo-coder.hatenablog.com/entry/2019/03/30/000000
 https://codeforces.com/blog/entry/66301
 
 Summary:
  - Keep in mind that formula transformation is <=> or => 😡
 
 */
LL N,K,A,B;
LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
void solve() {
  vector<LL> as={A,K-A},bs={B,K-B};
  vector<LL> X;
  FORR(a,as)FORR(b,bs) {
    REPE(i,N) {
      LL bb=b+i*K;
      if(bb<a) continue;
      LL l=bb-a;
      LL g=gcd(N*K,l),x=N*K/g;
      X.push_back(x);
    }
  }
  LL x=*min_element(ALL(X)),y=*max_element(ALL(X));
  println("%lld %lld",x,y);
}

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
void solve_wrong2() {
  vector<LL> as={A,(N*K+K-A)%(N*K)},bs={B,(N*K+K-B)%(N*K)};
  VI X;
  vector<LL> xs=divisors(N*K);
  FORR(a,as)FORR(b,bs) {
    LL ba=(N*K+b-a)%(N*K);
    FORR(x,xs) {
      LL l=N*K/x;
      LL g=gcd(l,K);
      if(x==6) dump(ba,l,g,ba%g);
      if(ba%g==0) X.push_back(x);
    }
  }
  LL x=*min_element(ALL(X)),y=*max_element(ALL(X));
  println("%lld %lld", x, y);
}

void solve_wrong1() {
  vector<LL> as={A,(N*K+K-A)%(N*K)},bs={B,(N*K+K-B)%(N*K)};
  VI X,Y;
  
  vector<LL> xs=divisors(N*K);
  
  FORR(a,as)FORR(b,bs) {
    LL ba=(N*K+b-a)%(N*K);
    FORR(x,xs) {
      LL NK=N*K/x;
      LL g=gcd(K,NK);
//      if(x==6) dump(x,NK,ba,g)
      if(ba%g==0) X.push_back(x);
    }
    LL y;
    if(ba==0) y=1; else {
      LL g=gcd((N*K+ba)%(N*K),N*K);
      y=N*K/g;
    }
    Y.push_back(y);
  }
  LL x=*min_element(ALL(X)),y=*max_element(ALL(Y));
  println("%lld %lld", x, y);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K>>A>>B;
  solve();
  
  return 0;
}
