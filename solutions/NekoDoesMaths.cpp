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

// $ cp-batch NekoDoesMaths | diff NekoDoesMaths.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NekoDoesMaths.cpp && ./a.out

/*
 
 4/24/2019
 
 8:07-8:35 WA
 8:42 pause
 9:00-9:35 give up
 9:35-10:35 read solutions and ACed
 
 Condition: S∈LCM(A+k,B+k), k=0..
 Unknown: min k s.t. LCM(A+k,B+k)=min{S}
 
 If gcd(A+k,B+k)==1 for any `k`, A*B is minimum (k=0).
 Otherwise gcd(A+k,B+k)>1 holds.
 
 Suppose gcd(A+k,B+k)=g
      A+k=g*a, B+k=g*b
   => k=g*a-A=g*b-B
   => g(a-b)=A-B
 
 We can search such `g` by iterating divisors of A-B (A>B)
 
 https://codeforces.com/blog/entry/66696
 https://cinnamo-coder.hatenablog.com/entry/2019/04/25/031403
 
 gcd(a+k,b+k) = gcd(a-b,a+k) makes a lot of sense.
 
     A+k=d*a, B+k=d*b
 <=> A ≡ B ≡ -k (mod d)
 <=> k=(d-A%d)%d
 
 */

LL A,B;
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
vector<LL> distinctPrimeFactors(LL n) {
  /*
   vector<LL> res=primeFactors(n);
   res.erase(unique(res.begin(),res.end()),res.end());
   return res;
   */
  //assert(n>=1);
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) if(n%p==0) {
    res.push_back(p);
    while(n%p==0) n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}
LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
LL lcm(LL a, LL b) { return (a*b)/gcd(a,b); }

LL solve() {
  if(A==B) return 0;
  vector<LL> ds=divisors(abs(A-B));
  LL minl=lcm(A,B),res=0;
  FORR(d,ds) {
    LL k=d-A%d;
    LL l=lcm(A+k,B+k);
    if(minl>l) minl=l,res=k;
  }
  return res;
}

LL solve_org() {
//  if(A>B) swap(A,B);
  LL x=abs(A-B);
  if(x==0) return 0;
  vector<LL> ds=divisors(x);
  LL minl=lcm(A,B),res=0;
//  dumpc(ds);
  FORR(d,ds) {
    LL AA=(A+d-1)/d*d;
    LL k=AA-A;
    LL BB=B+k;
    LL l=lcm(AA,BB);
    assert(BB%d==0);
//    dump(d,k,AA,BB,l);
    if(minl>l) minl=l,res=k;
  }
//  dump(minl,res);
  return res;
}

LL solve_wrong() {
  LL g=gcd(A,B);
  LL a=A/g,b=B/g;
  LL x=abs(a-b);
  dump(A,B,x,g);
  if(x==0) return 0;
  vector<LL> ps=divisors(x);
  LL minl=lcm(A,B),res=0;
  dumpc(ps);
  FORR(p,ps) {
    LL gg=g*p;
    dump(gg);
    dump((A+gg-1)/gg);
    LL AA=(A+gg-1)/gg*gg;
    LL k=AA-A;
    LL BB=B+k;
    dump(a,b,g,gg,AA,BB,k);
    //assert(BB%gg==0);
    LL l=lcm(AA,BB);
    if(minl>l) minl=l,res=k;
  }
  dump(minl,res);
  return res;
}

LL f() {
  LL minl=lcm(A,B),res=0;
  REP(k,1000) {
    LL l=lcm(A+k,B+k);
    if(minl>l) {
      dump(k,minl,l);
      res=k,minl=l;
    }
  }
  return res;
}

void test() {
  for(int x=1; x<=100; ++x) for(int y=x; y<=100; ++y) {
    A=x,B=y;
    dump(A,B);
    LL k1=solve(),k2=f();
    if(k1!=k2) dump(A,B,k1,k2);
    assert(k1==k2);
//    LL k2=f(),l=lcm(A+k2,B+k2);
//    if(k2!=-1)dump(k2,A+k2,B+k2,l);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
// test();
  
  cin>>A>>B;
  cout<<solve()<<endl;
  
  return 0;
}
