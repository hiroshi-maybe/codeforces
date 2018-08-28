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
 
 8/27/2018 AIM Tech Round 5
 
 9:49-10:10 AC
 
 Editorials:
  - http://codeforces.com/blog/entry/61493
 
 Tweets:
  - https://togetter.com/li/1261045
  - https://twitter.com/satanic0258/status/1034153506381258755
 
 Key:
  - If M<=1 and N>=1129, the answer is always satisfies arbitrary input
 
 Summary:
  - Hmmm I haven't figured out that it's always possible to achieve S(a)>=N and S(b)>=N as well
 
 */


// 10:10 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int N,M;
void solve() {
  VI A(1,5),B(1,5);
  int sumA=5,sumB=5;
  int i=0;
  int D[2]={4,5};
  while(sumA<N||sumB<N) {
    A.push_back(D[i%2]);
    B.push_back(D[(i%2)^1]);
    ++i;
    sumA+=A.back(),sumB+=B.back();
  }
//  dumpAR(A);
  reverse(A.begin(),A.end()); reverse(B.begin(),B.end());
  string SA="",SB="";
  REP(i,SZ(A)) SA+='0'+A[i];
  REP(i,SZ(B)) SB+='0'+B[i];
  assert(SZ(SA)<=2230&&SZ(SB)<=2230);
  cout<<SA<<" "<<SB<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  solve();
  return 0;
}
