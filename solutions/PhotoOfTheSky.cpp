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
 
 7/30/2018 R500 div2
 
 25:35-25:54 1WA on test case #3
 25:55-26:25 give up
 
 7/31/2018
 
 19:00-20:00 read editorials and add solution
 
 Editorials:
  - http://codeforces.com/blog/entry/60920
  - http://achax0511.hatenablog.com/entry/2018/07/31/222144
 
 Tweets:
  - https://togetter.com/li/1251978
  - https://twitter.com/noimi__/status/1023882923479457792
  - https://twitter.com/satanic0258/status/1023883406822653952
 
 Suppose we sort numbers and get below sequence:
 
  a,..,b | c,..,d (a<b<c<d)
 
 (b-a)*(d-c) seems to be optimal. I showed that (c-a)*(d-b)>=(b-a)*(d-c)
 However that's not sufficient at all. There exists counter example of it.
 I couldn't figure out it during the contest 😞.
 
 Suppose dx=b-a, dy=d-c, dx*dy=P. dx and dy are moderate in this case.
 dx*dy=P could happen for other dx and dy with extremely small and extremely large numbers.
 6 = 2 * 3. At the same time 6 = 1 * 6.
 Thus we cannot say that (b-a)*(d-c) is the only optimal value.
 We should try (d-a)*(t-s) where a<=s<=t<=d as well to find 1*6 case.
 If we want to minimize `t-s`, it should be consecutive `N` elements in sorted `A`.
 Thus we can compute all the possible `t-s` in O(N).
 
 Key:
  - `a` and `d` always affects the result. Two cases can happen based on it
   - `a` and `d` are in the same group
   - `a` and `d` are in different group
 
 Summary:
  - I found only (b-a)*(d-c) and got WA
  - 6=2*3=1*6. I should figure out a case of pair of extremely small and large number 👎
  - Very poor math taste 👎👎
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 25:54 1WA
// 26:25 pause
//const int MAX_N=1e5+1;
vector<LL> A;
int N;

LL solve_wrong1() {
  sort(A.begin(),A.end());
  vector<LL> X,Y;
  REP(i,N) {
    LL x=A[i],y=A[2*N-i-1];
    X.push_back(x),Y.push_back(y);
  }
  sort(X.begin(),X.end()),sort(Y.begin(),Y.end());
//  dumpAR(X);
//  dumpAR(Y);
  LL dx=X.back()-X.front();
  LL dy=Y.back()-Y.front();
//  dump2(dx,dy);
  return dx*dy;
}

LL solve_wrong2() {
  sort(A.begin(),A.end());
  LL dx=abs(A[N-1]-A[0]);
  LL dy=abs(A[2*N-1]-A[N]);
  LL res=dx*dy;
  //  dump2(dx,dy);
  return res;
}

LL solve() {
  sort(A.begin(),A.end());
  LL dx=abs(A[N-1]-A[0]);
  LL dy=abs(A[2*N-1]-A[N]);
  LL res=dx*dy;
  FOR(i,1,N) {
    LL dx=A[2*N-1]-A[0],dy=A[i+N-1]-A[i];
    SMIN(res,dx*dy);
  }
  //  dump2(dx,dy);
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  A.resize(2*N);
  REP(i,2*N) cin>>A[i];
  cout<<solve()<<endl;
  
  return 0;
}
