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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

// $ ../batch NewYearAndTheAcquaintanceEstimation | diff NewYearAndTheAcquaintanceEstimation.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NewYearAndTheAcquaintanceEstimation.cpp && ./a.out

/*
 
 12/30/2018
 
 08:53-9:15 give up
 
 1/5/2018
 
 15:45-17:07 read editorials and theorems
 
 1/6/2018
 
 9:50-13:20 read editorials and theorems. got AC.
 
 https://codeforces.com/blog/entry/64196
 http://kmjp.hatenablog.jp/entry/2019/01/02/0900
 
 https://en.wikipedia.org/wiki/Graph_realization_problem
 https://en.wikipedia.org/wiki/Havel%E2%80%93Hakimi_algorithm
 https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93Gallai_theorem
 
 It took tons of time to understand how to compute ∑ min(k,d[i]) part.
 `k` changes at most one. We can observe number which moves from <k bucket to >=k bucket by counting each number.
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

int f(int v) {
  if(v<0) return -1;
  if(v>N) return 1;
  int M=N+1;
  VI cnt(M+1,0);
  VI D(A,A+N);
  D.push_back(v);
  sort(D.rbegin(),D.rend());
  vector<LL> cum(M+1,0);
  REP(i,M) cum[i+1]=cum[i]+D[i];
  
  LL len=0,sum=0;
  for(int k=M; k>=1; --k) {
    len+=cnt[k];
    sum-=1LL*k*cnt[k];
    LL r=(LL)k*(k-1)+sum+k*len;
    LL l=cum[k]-cum[0];
    if(l>r) {
      int res=D[k-1]<=v?1:-1;
      dump3(v,k,res);
      return res;
    }
    
    if(D[k-1]>=k) ++len;
    else sum+=D[k-1];
    cnt[D[k-1]]++;
  }
  dump2(v,0);
  return 0;
}

void solve() {
  sort(A,A+N);
  reverse(A,A+N);
  
  int p=0;
  REP(i,N) p^=(A[i]%2);
  
  int good=-1,bad=(N+2)/2;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    (f(2*m+p)<0?good:bad)=m;
  }
  int l=good+1;
  
  good=(N+2)/2,bad=-1;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    (f(2*m+p)>0?good:bad)=m;
  }
  int r=good-1;
  
  dump2(l,r);
  if(r-l<0) {
    println("%d",-1);
  } else {
    FORE(i,l,r) printf("%d ",2*i+p);
    println("");
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
