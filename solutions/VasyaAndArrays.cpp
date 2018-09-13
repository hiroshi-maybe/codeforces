#include <iostream>
#include <iomanip>
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
 
 9/7/2018
 
 9:12-9:26 submit and got TLE
 
 I have no idea why TLE happens :(
 
 9/12/2018
 
 23:45-24:10 fix code not to use cumulative sum and unordered set. Got AC.
 
 */

// 9:26 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3e5+1;
int N,M;
LL A[MAX_N],B[MAX_N];
LL cumA[MAX_N]={},cumB[MAX_N]={};
unordered_set<LL> S;
void end() {
  cout<<-1<<endl;
  exit(0);
}

void solve_ok() {
  int res=0;
  
  cumA[0]=0,cumB[0]=0;
  REP(i,N) cumA[i+1]=cumA[i]+A[i];
  REP(i,M) cumB[i+1]=cumB[i]+B[i];
  
  FORE(i,1,M) S.emplace(cumB[i]);
  
  LL suma=0,sumb=0;
  int i=0,j=0;
  while(i<N||j<M) {
    if(suma<sumb) {
      if(i<N)suma+=A[i++];
      else break;
    } else if(suma>sumb) {
      if(j<M)sumb+=B[j++];
      else break;
    } else if(suma==sumb) {
      ++res;
      if(i<N&&j<M) {
        if(A[i+1]<B[j+1]) suma+=A[i++];
        else if(A[i+1]>B[j+1]) sumb+=B[j++];
        else suma+=A[i++],sumb+=B[j++];
      } else break;
    }
  }
//  dump4(i,N,j,M);
//  dump4(suma,sumb,accumulate(A,A+N,0LL),accumulate(B,B+M,0LL));
  if(i!=N||j!=M||suma!=sumb) end();
  cout<<res<<endl;
}

void solve() {
  cumA[0]=0,cumB[0]=0;
  REP(i,N) cumA[i+1]=cumA[i]+A[i];
  REP(i,M) cumB[i+1]=cumB[i]+B[i];

  int res=0;
  if(cumA[N]!=cumB[M]) end();
  
  // Inserting values into unordered set 3e5 times is extremely slow. It's spending 600(ms).
  /*
   i = 1, S.bucket_count() = 2
   i = 3, S.bucket_count() = 5
   i = 6, S.bucket_count() = 11
   i = 12, S.bucket_count() = 23
   i = 24, S.bucket_count() = 47
   i = 48, S.bucket_count() = 97
   i = 98, S.bucket_count() = 197
   i = 198, S.bucket_count() = 397
   i = 398, S.bucket_count() = 797
   i = 798, S.bucket_count() = 1597
   i = 1598, S.bucket_count() = 3203
   i = 3204, S.bucket_count() = 6421
   i = 6422, S.bucket_count() = 12853
   i = 12854, S.bucket_count() = 25717
   i = 25718, S.bucket_count() = 51437
   i = 51438, S.bucket_count() = 102877
   i = 102878, S.bucket_count() = 205759
   i = 205760, S.bucket_count() = 411527
 */
  // set<LL> does not have the problem because rehash does not happen.
  /*
  int x=S.bucket_count();
  FORE(i,1,M) {
    S.emplace(cumB[i]);
    if(S.bucket_count()!=x) {
      dump2(i,S.bucket_count());
      x=S.bucket_count();
    }
  }*/
  // initializing with iterator does not have the problem (got AC)
  S=unordered_set<LL>(cumB+1,cumB+M+1);
  
  FORE(i,1,N) if(S.count(cumA[i])) {
//    dump2(i,cumA[i]);
    ++res;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin>>N;
  REP(i,N) cin>>A[i];
  cin>>M;
  REP(i,M) cin>>B[i];

  solve();
  return 0;
}
