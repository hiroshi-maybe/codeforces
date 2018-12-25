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

// $ ../batch EhabAndAnotherAnotherXorProblem | diff EhabAndAnotherAnotherXorProblem.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EhabAndAnotherAnotherXorProblem.cpp && ./a.out

/*
 
 12/23/2018
 
 15:31-16:10 give up
 
 12/24/2018
 
 15:45-19:05 read editorial and got AC
 
 https://codeforces.com/blog/entry/63656
 
 I didn't dig deeper to apply query(c,d) where c != d.
 I analyzed only c==d case. Fuck.
 
 We need two info for each i-th bit to solve this problem
  1. which is larger in suffix?
  2. is i-th bit different?
 
 q(0,0), q(1,1) queries does not give #1 while q(0,1) and q(1,0) gives it.
 Thus 61 queries should solve this problem.
 
 Below approaches were correct.
  - determining from left to right
  - cancel prefix by XOR to test i-th bit one by one
  - figure out which is greater by applying (A+0,B+0) query
 
 The missing analysis was an idea to query with different bits.
 There is a reason of flexible query format in the problem statement.
 
 ```
  Did you use the whole condition? Did you use all the data?
  - How to solve it
 ```
 
 Codeforces judge system gives wrong log. I wasted 1 hour to figure out it. Fuck.
 
 Summary:
  - Exhaustive analysis was not performed
  - if bits are same, XORing with 0 and 1 respectively determines the bits
   - (0,0) ^ (0,1) = (0,1) (< determines 0,0 pair)
   - (1,1) ^ (0,1) = (1,0) (> determines 1,1 pair)

 */

int qcnt=0;

int ask(int c, int d) {
  assert(++qcnt<=62);
  println("? %d %d",c,d);
  fflush(stdout);
  int res=0; scanf("%d",&res);
  dump3(c,d,res);
  assert(res==-1||res==1||res==0);
  if(res==-2) exit(0);
  return res;
}
void answer(int a, int b) {
  dump2(a,b);
  println("! %d %d",a,b);
  fflush(stdout);
}

void solve() {
  
  int ineq=ask(0,0),a=0,b=0;
  for(int i=29; i>=0; --i) {
    int x=ask(a,b^(1<<i));
    if(ineq==0) {
      assert(x!=0);
      if(x>0) a|=(1<<i),b|=(1<<i);
    } else {
      int y=ask(a^(1<<i),b);
      if(x!=y) {
        if(x>0) a|=(1<<i),b|=(1<<i);
      } else {
        if(ineq<0) b|=(1<<i);
        else a|=(1<<i);
        ineq=x;
      }
    }
  }
  answer(a,b);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cout.flush();
  solve();
  
  return 0;
}
