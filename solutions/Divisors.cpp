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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 10/7/2018 Lyft Level 5 Challenge 2018 - Elimination Round
 
 10:48-11:57 WA
 13:40-13:48 bug fix and got AC
 
 https://codeforces.com/blog/entry/62287
 
 It took a lot of time to figure out how to find common prime.
 It turned out that it is just a special case to compute GCD.
 
 */
// 11:57 WA
// 13:40-13:48 looked at failed test case, fixed bug and got AC
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=500+1;
LL A[MAX_N];
int N;
const LL MOD=998244353;

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
LL sqrt2(LL n) {
  double a=sqrt(n);
  for(LL d=-2; d<=2; d+=1) {
    LL p=a+d;
    if(p*p==n) return p;
  }
  return -1;
}
LL sqrt3(LL n) {
  //for(LL p=2; p*p*p<=n; ++p) if(p*p*p==n) return p;
  double a=pow(n,1.0/3.0);
  for(LL d=-2; d<=2; d+=1) {
    LL p=a+d;
    if(p*p*p==n) return p;
  }
  return -1;
}

LL solve() {
  unordered_map<LL,LL> M;
  unordered_map<LL,LL> X;
  REP(i,N) {
    LL a=sqrt2(A[i]);
    if(a!=-1) {
      LL aa=sqrt2(a);
      if(aa!=-1) M[aa]+=4;
      else M[a]+=2;
    }
    LL b=sqrt3(A[i]);
    if(a==-1&&b!=-1) {
      M[b]+=3;
    }
    if(a==-1&&b==-1) {
      X[A[i]]++;
    }
  }
  
  dump2(SZ(M),SZ(X));
  
  vector<LL> MM; FORR(kvp2,M) MM.push_back(kvp2.first);
  
  vector<pair<LL,LL>> Y;
  FORR(kvp,X) {
    LL n=kvp.first,cnt=kvp.second;
    
    bool ok=false;
    FORR(m,MM) {
      if(n%m==0) {
        LL p=n/m;
        M[m]+=cnt,M[p]+=cnt;
        ok=true;
        break;
      }
    }
    if(!ok) Y.emplace_back(n,cnt);
  }
  
  int L=SZ(Y);
  dump(L);
  
  VI viz(L,0);
  REP(i,L) FOR(j,i+1,L) if(!viz[i]||!viz[j]) {
    LL g=gcd(Y[i].first,Y[j].first);
    LL cnt1=Y[i].second,cnt2=Y[j].second;
    if(g!=1) {
      dump3(Y[i].first,Y[j].first,g);
      if(!viz[i]) M[g]+=cnt1,M[Y[i].first/g]+=cnt1;
      if(!viz[j]) M[g]+=cnt2,M[Y[j].first/g]+=cnt2;
      viz[i]=1,viz[j]=1;
    }
  }
  LL res=1;
  FORR(kvp,M) {
    res=res*(kvp.second+1LL)%MOD;
  }
  //int x=count(viz.begin(),viz.end(),0);
  //dump(x);
  //REP(_,x) res=res*4LL%MOD;
  REP(i,L) if(!viz[i]) {
    LL cnt=Y[i].second;
    res=res*(1LL+cnt)%MOD*(1LL+cnt)%MOD;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
