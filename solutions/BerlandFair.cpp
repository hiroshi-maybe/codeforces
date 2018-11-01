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
 
 10/25/2018 ER53
 
 9:20-9:35 time is up
 
 10/31/2018
 
 20:10-21:22 analysis
 21:57 submit and got WA
 
 11/1/2018
 
 12:00-12:50, 13:30-14:55 read editorial and got AC
 
 https://codeforces.com/blog/entry/62742
 http://betrue12.hateblo.jp/entry/2018/10/26/200331
 
 data: T and A
 condition: keep buying candies from left to right in cyclic manner if T'>=A[i]
 unknown: # of bought candies
 
 Solving possible # of bought candies from left to right one by one was my aim.
 However it didn't work because my method was ignoring a condition to go through from left to right.
 It was better to look for optimization following simulation steps.
 Skipped candies are never revisited. Also remaining T should be less than skipped A[i].
 
 Key:
  - Once candy at `i` is skipped, it's never revisited
  - Once candy at `i` is skipped, remaining `T` is less than A[i]
 
 Summary:
  - My induction was wrong due to speciality of example
  - Induction from examples is important. However verify reduced property if it's general enough
  - Problem condition is forcing to look from left to right. Algorithm should follow the way not to violate the condition
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
LL A[MAX_N];
LL T;
int N;

LL solve() {
  LL res=0;
  LL mina=*min_element(A,A+N);
  while(T>=mina) {
    int cnt=0; LL sum=0;
    LL T2=T;
    REP(i,N) if(A[i]<=T2) {
      ++cnt;
      T2-=A[i];
      sum+=A[i];
    }
    res+=T/sum*cnt;
//    dump4(T,sum,cnt,T/sum);
//    dump3(T,T/sum*cnt,res);
    T%=sum;
  }
  return res;
}

/*
 10 25
 2 2 5 1 5 4 5 5 5 1
 fails
*/
LL solve_wrong() {
  vector<LL> AA(N); REP(i,N) AA[i]=A[i];
  sort(ALL(AA));
  LL sum=0; int cnt=0;
  unordered_map<LL,int> cntM;
  unordered_map<LL,LL> ubM;
  vector<LL> cum(1,0);
  REP(i,N) {
    sum+=AA[i];
    ++cnt;
    if(i==N-1||AA[i]!=AA[i+1]) {
      cum.push_back(sum);
      cntM[sum]=cnt;
      ubM[sum]=AA[i];
    }
  }
  LL res=T/sum*N,ub=1e10;
  T%=sum;
  dump3(sum,res,T);
  REP(i,N) if(A[i]<=ub) {
    auto j=upper_bound(ALL(cum),T)-cum.begin();
    --j;
    assert(j>=0);
    LL sum=cum[j];
    if(ubM[sum]>=A[i]) {
      SMIN(ub,ubM[sum]);
      LL a=T/sum,b=cntM[sum];
      res+=a*b;
      T%=sum;
      dump4(i,A[i],sum,ubM[sum]);
      dump4(a,b,T,res);
    }
    if(T>=A[i]) T-=A[i],++res;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>T;
  REP(i,N) cin>>A[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
