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
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline bool SMIN(T &l,const T &r){return l<r?l=r,1:0;}
template<class T> inline bool SMAX(T &l,const T &r){return l>r?l=r,1:0;}
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
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

#define println(args...) fprintf(stdout, ##args),putchar('\n');

/*
 
 10/24/2018
 
 9:49-11:00 give up
 
 Observations:
  - Transitivity does not hold
  - We can build a graph based on color pairs
  - Rooks can put in the same row if graph has a clique
  - N*(N-1)/2 <= 100(100-1)/2 < 5000 (N<=100)
  - graph connectivity can be represented in 2d board?
   - matrix or adjacent list
 
 10/29/2018
 
 20:30-21:40 read editorial
 21:40-21:54 add solution
 
 http://codeforces.com/blog/entry/62688
 
 Putting rooks with every color diagonally was correct.
 However I didn't have an idea to make pairs in bottom or right side
 
 P={(1,3),(2,3),(2,4)}
 
 1
  2
   3
    4
 1 3
  23
  2 4
 
 Looking for clique is definitely complex.
 If we could solve this problem, it's preferred that connectivity is represented independently.

 /---\
 1-2-3 (1,2),(2,3),(3,1)
 
 Representing this complete graph as below is not generic enough.
 123
 
 If we could have represented independently, each pair should occupy single row or column.
 Then following structure is coming up.
 
 12
  23
 1 3
 
 # How to solve it?
 
 data: N, M pairs
 condition: Rooks with N colors show up, Rooks with different colors show up in same column or row iff pairs of them exists
 unknown: positions of rooks (constructive problem)
 
 - Look at the unknown! And try to think of a familiar problem having the same or a similar unknown
  - constructive steps should be simple and general enough to solve any input
 - Could you change the unknown or the data so that the new unknown and the new data are nearer to each other?
  - If we could solve this problem, pair should be represented independently.
 
 Summary:
  - I should have imagined that this problem can be solved in a simple construction. Then putting each pair in different row or column should have come up
  - This is kind of analysis, or solution backwards, or regressive reasoning in "How to solve it".
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_M=1e3+1;
int A[MAX_M],B[MAX_M];
int N,M;

void solve() {
  VV<int> res(N);
  REP(i,N) res[i].push_back(i);
  REP(i,M) {
    int a=A[i],b=B[i];
    res[a].push_back(i+N);
    res[b].push_back(i+N);
  }
  REP(i,N) {
    println("%d",SZ(res[i]));
    REP(j,SZ(res[i])) println("%d %d",res[i][j]+1,i+1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,M) {
    cin>>A[i]>>B[i];
    --A[i],--B[i];
  }
  solve();
  
  return 0;
}
