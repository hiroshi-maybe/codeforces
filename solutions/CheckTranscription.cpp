#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
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
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

/*
 
 12/10/2018
 
 17:12-18:03 give up
 18:03-18:30, 20:30-21:30 read editorial and figure out string hash library is necessary
 
 https://codeforces.com/blog/entry/63461

 12/12/2018
 
 Created more comprehensive rolling hash library.
 
 String hashing:
  - https://cp-algorithms.com/string/string-hashing.html
  - https://github.com/hiroshi-maybe/topcoder/blob/master/lib/string-matching.cpp

 12/13/2018
 
 14:00-16:35 add analysis, implement and got AC
 
 Properties of this problem:
 
 1 counting
  => brute force |T|/2|S| candidates
 2 string matching
  => core solution of this problem (rolling hash) ✅
 3 cycle of strings
  => not relevant to this problem
 4 only lower case letters (automaton?)
  => not relevant to this problem
 5 {0,1} only two patterns
  => we can make only rolling hashes of two patterns from this property ✅
  => Symmetry property helps evaluate tight time complexity ✅
 6 string partitioning. precompute something?
  => not directly relevant.
 7 dp?
  => not really
 
 If we know r0 and r1, we can check the correctness in O(|S|) time by rolling hash.
 Suppose there are {`a`,`b`} characters for 0s and 1s (a+b=|S|, a>=b) because of symmetry property of 0s and 1s.
 
 Then following conditions should be satisfied:
  a+b = |S|, a>=b
  |T| = a*|rx|+b*|ry| (rx,ry ∈ {r0, r1})
 
 Note that we can figure out {rx,ry} in O(|S|+|T|) time if |rx| and |ry| are determined,
 
 From first formula, we know that |S|=a+b<2*a => a>|S|/2
 From second formula, there are |T|/a candidates of length of |r1|.
 |T|/a<|T|/(|S|/2)=2|T|/|S|
 
 It takes O(|S|) time to process each (rx,ry).
 Thus total runtime is 2|T|/|S|*|S|=2|T|. Runtime is O(|T|}.
 
 Summary:
  - I knew Rabin Karp algorithm. However I didn't know that O(1) comparison is possible for any substrings by cumulative sum
  - I came up with formulas. I tried to find something based on Bézout's identity. However no luck
   - I didn't know rolling hash algorithm to compare substrings in O(1)
   - I didn't have an idea to upper-bound complexity by evaluating symmetry formula
  - Do not call substring, which will spend huge overhead if |S| is small. Proceed only by hash values!!! (I experienced TLE due to this mistake)
 
 */

// $ ../batch CheckTranscription | diff CheckTranscription.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CheckTranscription.cpp && ./a.out

namespace RollingHash {
  template<int MOD> struct ModInt {
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
  };
  const int MOD0=1e9+7,MOD1=1e9+9;
  using M0=ModInt<MOD0>;
  using M1=ModInt<MOD1>;
  M0 p0=rand()%MOD0,pinv0=p0.inv();
  M1 p1=rand()%MOD1,pinv1=p1.inv();
  vector<M0> P0{1}, PINV0{1};
  vector<M1> P1{1}, PINV1{1};
  struct H {
    vector<pair<M0,M1>> hcum;
    string str;
    H(string s) : str(s) {
      int N=(int)s.size();
      while ((int)P0.size()<=N) {
        P0.push_back(P0.back()*p0);
        PINV0.push_back(PINV0.back()*pinv0);
        P1.push_back(P1.back()*p1);
        PINV1.push_back(PINV1.back()*pinv1);
      }
      hcum.resize(N+1);
      hcum[0]={M0(0),M1(0)};
      for(int i=0; i<N; ++i) {
        hcum[i+1]={hcum[i].first+M0(s[i])*P0[i],hcum[i].second+M1(s[i])*P1[i]};
      }
    }
    // half-open range [l,r)
    pair<M0,M1> hash(int r) { assert(0<=r&&r<=SZ(str)); return { hcum[r].first, hcum[r].second }; }
    pair<M0,M1> hash(int l, int r) {
      assert(0<=l&&l<=SZ(str));
      assert(0<=r&&r<=SZ(str));
      return {
        (hcum[r].first-hcum[l].first)*PINV0[l],
        (hcum[r].second-hcum[l].second)*PINV1[l]
      };
    }
  };
  // Rabin-Karp algorithm
  vector<int> match(H &s, H &p) {
    int N=s.str.size(),M=p.str.size();
    auto pp=p.hash(0,M);
    vector<int> res;
    for(int i=0; i<=N-M; ++i) if(s.hash(i,i+M)==pp) res.push_back(i);
    return res;
  }
};

string S,T;

void solve() {
  char ca='0',cb='1';
  int a=0,b=0;
  int N=SZ(S),M=SZ(T);
  REP(i,N) (S[i]==ca?a:b)++;
  if(a<b) swap(a,b),swap(ca,cb);
  RollingHash::H th(T);
  
  int res=0;
  for(int la=1; a*la<=M; ++la) if((M-a*la)%b==0) {
    int lb=(M-a*la)/b;
    if(lb<1) continue;
    assert(a*la+b*lb==M);
    
    bool ok=true;
    int a=0,b=0;
    pair<RollingHash::M0,RollingHash::M1> ah,bh;
    REP(i,N) {
      int p=a*la+b*lb;
      if(S[i]==ca) {
        if(a==0) {
          ah=th.hash(p,p+la);
        } else if(ah!=th.hash(p,p+la)) {
          ok=false;
          break;
        }
        ++a;
      }
      if(S[i]==cb) {
        if(b==0) {
          bh=th.hash(p,p+lb);
        } else if(bh!=th.hash(p,p+lb)) {
          ok=false;
          break;
        }
        ++b;
      }
    }
    if(ah!=bh)res+=ok;
    /*
     
    string ra,rb; int j=0;
    REP(i,N) {
      if(S[i]==ca) {
        // ⚠️ TLE happens if `la` or `lb` are large
        if(ra.empty()) ra=T.substr(j,la);
        j+=la;
      }
      if(S[i]==cb) {
        // ⚠️ TLE happens if `la` or `lb` are large
        if(rb.empty()) rb=T.substr(j,lb);
        j+=lb;
      }
    }
    if(ra==rb) continue;
    RollingHash::H ah(ra),bh(rb);
    
    dump4(la,lb,ra,rb);
    bool ok=true;
    int a=0,b=0;
    REP(i,N) {
      int p=a*la+b*lb;
      dump4(i,a,b,p);
      if(S[i]==ca) {
        if(ah.hash(0,la)!=th.hash(p,p+la)) {
          ok=false;
          break;
        }
        ++a;
      }
      if(S[i]==cb) {
        if(bh.hash(0,lb)!=th.hash(p,p+lb)) {
          ok=false;
          break;
        }
        ++b;
      }
    }
    if(ok) dump2(ra,rb);
    res+=ok;*/
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>S>>T;
  solve();
  
  return 0;
}
