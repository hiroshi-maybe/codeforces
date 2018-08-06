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
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 8/3/2018 ER48 div2
 
 8:03-8:27 TLE with rolling hash
 8:28-9:15 AC
 
 Editorial:
  - http://codeforces.com/blog/entry/61015
  - http://betrue12.hateblo.jp/entry/2018/08/04/135456
  - https://twitter.com/tempura_pp/status/1025423228276113408
 
 Firstly I came up with KMP or rolling hash because substring matching may be cyclic.
 However it's NOT obviously necessary because check of all the substrings is possible in O(N*M)<<1e8 😡
 I'm very foolish. I got TLE with rolling hash 😡😡.
 
 I'm stupid enough to go through complex imos approach.
 Let me say again. N is SMALL. NO NEED to do coordinate compression by imos 😡😡😡😡.
 I got AC though, it's such a waste of time 😡😡😡😡😡😡😡😡.
 
 Just use cumulative sum 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡.
 One tricky point is that substring is interval.
 However it's fixed length |T|. It's easy to accomodate it.
 
 Summary:
  - Very stupid. N^2 is affordable. Just use cumulative sum 😞
  - if length of interval is fixed, problem is reduced to cumulative sum.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 8:27 TLE on #5
// 9:15 AC

template<class T> struct RollingHash {
public:
  int M;
  string P;
  T d; // radix
  T MOD; // MOD
  T h; // d^(M-1) % MOD, helper to adjust rolling hash
  T p; // hash code of P
  RollingHash(string P, T d=131, T MOD=1e9+7): M(P.size()), P(P), d(d), MOD(MOD) {
    this->h=powmod(d,M-1,MOD);
    this->p=calcRollingHash(P);
  }
  
  // Rolling hash x for X[i..<M]
  // x=d^(M-1)*X[i]+d^(M-2)*X[i+1]+..+d^0*X[i+M-1]
  T calcRollingHash(string X) {
    T res=0;
    for(int i=0; i<min((int)X.size(), M); ++i) {
      res=(d*res)%MOD+X[i],res%=MOD;
    }
    return res;
  }
  // incremental update of hash code
  T updateRollingHash(T base, string S, int i) {
    T res=d*(base+MOD-((T)S[i]*h)%MOD)%MOD+S[i+M];
    res%=MOD;
    return res;
  }
  
  int doRabbinKarpMatch(string S) {
    int N=S.size();
    
    // preprocessing
    T s=calcRollingHash(S);
    
    int res=0;
    for(int i=0; i<N-M; ++i) {
      if(s==p) ++res;
      // incremental update of hash code
      // s=d(t-S[i]h)+S[i+M]
      s=updateRollingHash(s,S,i);
    }
    if(s==p) ++res;
    return res;
  }
private:
  T powmod(T a, T b, T MOD) {
    T res=1;
    for(T mask=1; mask<=b; mask<<=1) {
      if(b&mask) res*=a, res%=MOD;
      a*=a; a%=MOD;
    }
    return res;
  }
};

const int MAX_Q=1e5+1;
int L[MAX_Q],R[MAX_Q];
int Q,N,M;
string S,T;

void solve_TLE() {
  RollingHash<long long> rh(T);
  
  REP(i,Q) {
    int l=L[i]-1,r=R[i]-1;
    string s=S.substr(l,r-l+1);
//    dump4(i,l,r,s);
    cout<<rh.doRabbinKarpMatch(s)<<(i==Q-1?'\n':' ');
  }
}

const int MAX_N=1e3+2;
int mx[MAX_N][MAX_N];
void solve_org() {
  ZERO(mx);
  map<int,int> imos;
  REPE(i,N-M) {
    bool ok=true;
    REP(j,M) ok&=S[i+j]==T[j];
    if(ok) { imos[i]=i+M-1; dump2(i,i+M-1); }
  }
  REP(i,N) {
    int sum=0;
    for(auto it=imos.lower_bound(i); it!=imos.end(); ++it) {
      int r=it->second;
      sum+=1;
      mx[i][r]=sum;
//      dump3(i,r,sum);
      auto it2=it; it2++;
      int end=it2!=imos.end()?it2->second:N;
      FOR(j,r+1,end) {
//        dump3(i,j,sum);
        mx[i][j]=sum;
      }
    }
  }
  /*
  REPE(i,N) {
    REPE(j,N) cout<<mx[i][j];
    cout<<endl;
  }*/
  
  REP(i,Q) {
    int l=L[i]-1,r=R[i]-1;
    cout<<mx[l][r]<<(i==Q-1?'\n':' ');
  }
}

int cum[MAX_N];
void solve() {
  ZERO(cum);
  REP(i,N) {
    cum[i+1]+=cum[i];
    bool ok=i+M<=N;
    if(ok) REP(j,M) ok&=(S[i+j]==T[j]);
    cum[i+1]+=ok;
  }
  REP(i,Q) {
    int l=L[i]-1,r=R[i]-M+1;
    LL res=r<=l?0:cum[r]-cum[l];
    cout<<res<<(i==Q-1?'\n':' ');
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>Q>>S>>T;
  REP(i,Q) cin>>L[i]>>R[i];
  
  solve();
  
  return 0;
}
