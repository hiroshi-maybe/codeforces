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
//#define __KUMATRACE__ true
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
vector<int> sieve(int N) {
  assert(N>=1);
  vector<int> fs(N+1, true);
  fs[0]=fs[1]=false;
  for(long long p=2; p*p<=N; ++p) if(fs[p]) {
    for(long long q=p*p; q<=N; q+=p) fs[q]=false;
  }
  vector<int> res;
  for(int n=2; n<=N; ++n) if(fs[n]) res.push_back(n);
  return res;
}
template<typename Integer>
vector<Integer> primeFactors(Integer n) {
  assert(n>=1);
  vector<Integer> res;
  for(Integer p=2; p*p<=n; ++p) while(n%p==0) {
    res.push_back(p);
    n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}
// $ cp-batch GCDOfAnArray | diff GCDOfAnArray.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GCDOfAnArray.cpp && ./a.out

/*

 3/6/2021

 7:29-8:20 give up

 18:10-18:50, 21:20-21:30 read tweets and got AC

 https://twitter.com/hanseilimak/status/1368620335583485953

 https://codeforces.com/blog/entry/88422
 https://twitter.com/kzyKT_M/status/1368235263831404544
 https://twitter.com/laycrs/status/1368239491035455490
 https://twitter.com/natsugir/status/1368245310003183617

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N,Q;

void solve() {
  VI ps=sieve(2e5);
  map<int,int> pmap; REP(i,SZ(ps)) pmap[ps[i]]=i;
  vector<set<II>> xs(SZ(ps));
  vector<map<int,int>> cnts(N);

  auto minpow=[&](int p) {
    int pid=pmap[p];
    if(SZ(xs[pid])<N) return 0;
    auto it=xs[pid].begin();
    return it->first;
  };

  /*auto curpow=[&](int p, int i) {
    return cnts[i][p];
  };*/
  auto addpow=[&](int p, int n, int i) {
    int cur=cnts[i][p];
    cnts[i][p]+=n;
    int pid=pmap[p];
    if(xs[pid].count({cur,i})) {
      xs[pid].erase({cur,i});
    }
    xs[pid].emplace(cnts[i][p],i);
  };

  REP(i,N) {
    VI ps=primeFactors(A[i]);
    map<int,int> cnt;
    FORR(p,ps) cnt[p]++;
    FORR(kvp,cnt) {
      int p=kvp.first,pid=pmap[p];
      xs[pid].emplace(kvp.second,i);
    }
    cnts[i]=cnt;
  }
  ModInt res=1;
  REP(i,SZ(ps)) if(SZ(xs[i])==N) {
    int p=ps[i];
    res*=ModInt(p).pow(minpow(p));
  }
  while(Q--) {
    int i,x; cin>>i>>x;
    --i;
    dump(i,x);
    VI xps=primeFactors(x);
    map<int,int> cnt;
    FORR(p,xps) cnt[p]++;
    FORR(kvp, cnt) {
      int p=kvp.first,n=kvp.second;

      //II cur={curpow(p,i),i};

      auto minp=minpow(p);
      addpow(p,n,i);
      if(SZ(xs[pmap[p]])==N) {
        auto minp2=minpow(p);
        int delta=minp2-minp;
        dump(minp, minp2, delta);
        if(delta>0) res*=ModInt(p).pow(delta);
      }
      //dump(p,n);
    }
    cout<<res<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>Q;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
