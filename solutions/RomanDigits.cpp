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
 
 7/1/2018 R493 Div2 C
 
 24:18-24:50 time is up
 
 7/28/2018
 
 22:50-23:27 Read editorials and add solution
 
 Editorials:
  - http://codeforces.com/blog/entry/60357
 
 Tweets:
  - https://togetter.com/li/1242766
  - https://twitter.com/kuuso1/status/1013455399687557120
  - https://twitter.com/hamko_intel/status/1013454054729478144
  - https://twitter.com/n_vip/status/1013454420812500993
 
 From some of related tweets, I did experiment and found out that f(N)-f(N-1)=49 for N>=12
 It worked after one WA due to overflow.
 
 Problem is reduced to a problem where picking up at most N integers from {4,9,49} from twitter.
 Why? The official editorial is explaining about it.
 
 That we want to do in counting problem is count specific case uniquely.
 Let's sort sequence of digits firstly like { 1,1,1,5,10,10,50,50,50,50,50 } (N=11).
 
  S = { 1,1,1,5,10,10,50,50,50,50,50 }
 
 Now N is fixed. We can convert this sequence to difference to 1.
 
  S  = { 1,1,1,5,10,10,50,50,50,50,50 }
  S' = { 0,0,0,4, 9, 9,49,49,49,49,49 }
 
 0 does not contribute to sum.
 Now problem is transformed into a problem to pick unique sum from {4,9,49} with at most N elements.
 9 is co-prime with 4. nine 4s can be converted to one 9 to count uniquely.
 
 4 x11 => 0 x8, 4 x2, 9 x1
 
 We can brute-force number of 4s and number of 9s.
 
 Brute-force solutions:
  - http://codeforces.com/contest/998/submission/40077703
 
 However most of people are solving based on growing linear result when n>=12.
 
 Key:
  - Sort to count uniquely
  - Take difference to smallest element 1 in order to convert to easier problem
   - At most N elements
   - {4,9,49} are mutually co-prime
 
 Summary:
  - I didn't even experiment... 😞
  - How should I figure out that difference is constant for N>=12? 🤔
   - According to editorial, which comes from analysis of
  - Editorial makes more sense. {1,5,10,50} with N elements is converted to {4,9,49} with at most N elements
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
LL N;

SETI S;
int X[4]={1,5,10,50};
void dfs(int i, int rem, int cur) {
  if(i==4) {
    if(rem==0) S.emplace(cur);
    return;
  }
  REPE(x,rem) dfs(i+1,rem-x,cur+x*X[i]);
}

int test(int N) {
  S.clear();
  dfs(0,N,0);
//  cout<<N<<": "<<SZ(S)<<endl;
//  dumpAR(S);
  return SZ(S);
}

LL solve() {
  LL res=test(min(11LL,N));
  if(N<=11) return res;
  res+=(N-11LL)*49LL;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  
  FORE(i,1,20) test(i);
  
  cout<<solve()<<endl;
  
  return 0;
}
