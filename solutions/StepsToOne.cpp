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
#define UNIQUE(A) sort((A).begin(),(A).end()),(A).erase(std::unique((A).begin(), (A).end()), (A).end());
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

const int MOD=1000000007;
//const int MOD=998244353;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};

// $ cp-batch StepsToOne | diff StepsToOne.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address StepsToOne.cpp && ./a.out

/*
 
 4/12/2019
 
 9:03-9:25 give up
 
 Equation needs to be solved.
 However all the combinations of (gcd(A),x) seems to be too large.
 I'm in stuck...
 
 12:40-15:00, 15:30-16:10 read editorials
 
 4/13/2019
 
 13:25-14:00, 14:50-16:30 read editorials and got AC by IEP solution
 16:30-17:30 read other solutions
 
 4/14/2019
 
 9:30-10:30 add solution with Mobius function.
 
 1. Prime factorization and divisor enumeration
 
 E[k]=1+∑{E[k]/M : i=1..L}+F where L=floor(M/k),F=∑{E[gcd(k,l)]/M : l!=p*k}
 <=> E[k]=(1-L/M)^-1*(1+F)
 
   F
 = ∑{E[gcd(k,l)]/M : l!=p*k}
 = ∑{E[d]/M*cnt(d) : d|K }
 
 cnt(d) = |{x:gcd(k,x)=d}|
 
 cnt(d) can be computed by IEP by prime factors of K
 k = d*a, x = d*b, gcd(a,b)=1
 
 cnt(d) = ∑ { 𝜇(|A|)*M/d*∏{p∈A} : A⊆P } where P is prime factors of a=k/d
 
 Note that divisors and prime factors should be pre-computed
 
 res = ∑ { E[i]/M : i=1..M }, 1/M factor is showing that probability of first turn is uniformly random.
 
 - Fast primer factorization by sieve is necessary - O(M*lg M) time
 - Enumeration of divisors is necessary - O(M*lg M) time
 - Apply IEP to compute cnt(x) = |{gcd(k,x)=d}|
 
 Still estimated runtime is M*HCN(M)*2^6*6 = 5*10^9. Too large. Fuck.
 
 https://codeforces.com/blog/entry/66101
 
 2. Math by infinite series
 
 E'[g] = expected value where gcd = multiple of `g`.
 It's easy to count by multiples because just divide by `x` works.
 However unknown is E[g] = expected value where gcd is exactly `g`.
 We need to subtract E'[k*g] k=2,..M/g.
 
 E'[g] = M/(M-cnt(g))
 
 https://ferin-tech.hatenablog.com/entry/2019/03/22/Codeforces_Round_%23548_%28Div__2%29_D__Steps_to_One
 
 3. Mobius function
 
 E = 1 + ∑ { k*Pr[k] : k=1.. } where Pr[k] = probability s.t. trial ends exactly `k` times
 
 Pr[k] = Pr'[k]-Pr'[k+1] where Pr'[k] = probabillity s.t. trial does not end `k` times.
 
 Pr'[k] = ∑ { mob(i)*Pr[# is multiple of i]^k : i=2..M }
 Pr[# is multiple of i] = floor(M/i)/M
 
   E
 = 1+ ∑ { k*Pr[k] : k=1.. }
 = 1+ ∑ { k*(Pr'[k]-Pr'[k+1]) : k=1.. }
 = 1+ (Pr'[1]-Pr'[2])+2*(Pr'[2]-Pr'[3])+3*(Pr'[3]-Pr'[4])+..
 = 1+ Pr'[1] + Pr'[2] + Pr'[3] + ...
 = 1+ ∑ { Pr'[k] : k=1..∞ }
 = 1+ ∑ { ∑ { mob(i)*Pr[# is multiple of i]^k : i=2..M } : k=1..∞ }
 = 1+ ∑ { mob(i)*∑ { Pr[# is multiple of i]^k: k=1..∞ } : i=2..M } (nested ∑ is exchanged. maybe we need proof of it for strict analysis? 🤔)
 = 1+ ∑ { mob(i)*s/(M-s) : i=1..M } where s=floor(M/i)
 
 https://twitter.com/tempura_cpp/status/1108785361080053760
 https://twitter.com/tempura_cpp/status/1108801110737743872
  - Mobius function
 https://codeforces.com/contest/1139/submission/51652104
 
 Summary:
  - First step was not clear. GCD starts from first turn. After that common dp formula starts
  - Expected value of # of turn <=> find state cycle and solve equation
  - Too many tate transitions in number theory <=> group by multiples or divisors
 
 */

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

const int MAX_N=1e6+1;
ModInt E[MAX_N];
int M;
vector<LL> P[MAX_N];
vector<LL> divs[MAX_N];

vector<int> mobiusfunc(int N) {
  vector<int> res(N+1,-1),isprime(N+1,1);
  res[0]=0,res[1]=1;
  isprime[0]=isprime[1]=false;
  for(int p=2; p<=N; ++p) if(isprime[p]) {
    for(int n=2*p; n<=N; n+=p) isprime[n]=false;
    for(int k=1; k*p<=N; ++k) {
      res[k*p]*=-1;
      if(k%p==0) res[k*p]=0;//multiple of p*p
    }
  }
  return res;
}

void solve() {
  mobiusfunc(30);
  VI mob=mobiusfunc(M);
  ModInt res(1);
  FORE(k,2,M) {
    int s=M/k;
    res+=ModInt(mob[k])*ModInt(s)/ModInt(M-s);
  }
  cout<<res<<endl;
}

void solve_primefact() {
  PrimeFact pf(M);
  FORE(n,1,M) {
    vector<LL> ps=pf.fact(n);
    UNIQUE(ps);
    P[n]=ps;
  }
  FORE(n,1,M)for(int m=2*n; m<=M; m+=n) divs[m].push_back(n);
  REPE(i,M) sort(ALL(divs[i]));
  E[1]=ModInt(0);
  for(int k=2; k<=M; ++k) {
    ModInt F;
    FORR(d,divs[k]) {
      LL a=k/d;
      vector<LL> ps=P[a];
      LL cnt=0;
      REP(mask,1<<SZ(ps)) {
        int sign=__builtin_popcount(mask)%2?-1:1;
        LL pp=1;
        REP(i,SZ(ps)) if((mask>>i)&1) pp*=ps[i];
        cnt+=sign*(M/d/pp);
      }
      F+=E[d]/M*cnt;
      int L=M/k;
      ModInt inv=ModInt(1)-ModInt(L)/ModInt(M);
      E[k]=(F+1)/inv;
    }
  }
  ModInt res(1);
  FORE(i,1,M) res+=E[i]/M;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>M;
  solve();
  
  return 0;
}
