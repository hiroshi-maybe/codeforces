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
/*
 
 10/20/2018 R517 div2
 
 26:00-27:10 give up
 
 My guess was it's always possible to achieve `n` s.t. N(N+1)/2<=A+B
 However I couldn't construct it by filling from 1 to N.
 Actually I should have filled from N to 1 because A-sum is getting smaller when sum gets larger.
 
 10/27/2018
 
 22:55-23:30 read submit code and got AC
 
 http://codeforces.com/blog/entry/62612
 
 Key:
  - filling with larger number is optimal
 
 Summary:
  - I never had an idea to fill in descendent order.
  - If we want to reduce chance that I cannot fill expected number, filling largest possible number is optimal. Remember it.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
LL A,B;
// 26:39 RE
void solve_wrong() {
  LL tot=A+B;
  LL n=0;
  while((n+1)*(n+2)/2LL<=tot) ++n;
  dump(n);
  bool swapped=false;
  if(A>B) swap(A,B),swapped=true;
  LL x=0;
  while(true) {
    if((x)*(x+1)/2LL>A) break;
    ++x;
  }
  --x;
  dump3(x,(x)*(x+1)/2LL,A);
  while(A-x*(x+1)/2<=x) --x;
  LL y1=-1,y2=-1;
  if(A-x*(x+1)/2<=n) {
    y1=n;
  } else {
    while(x>1) {
      LL ysum=A-x*(x+1)/2LL;
      y1=ysum/2,y2=ysum-y1;
      if(y1==y2) --y1,++y2;
      if(x<y1&&y2<=n) break;
      --x;
    }
  }
  dump4(x,y1,y2,A);
  vector<LL> P,Q;
  FORE(p,1,n) {
    if(p<=x||p==y1||p==y2)P.push_back(p);
    else Q.push_back(p);
  }
//  dump2(accumulate(P.begin(),P.end(),0LL),A);
  assert(accumulate(P.begin(),P.end(),0LL)<=A);
//  dump2(accumulate(Q.begin(),Q.end(),0LL),B);
  assert(accumulate(Q.begin(),Q.end(),0LL)<=B);

  if(swapped) swap(P,Q);
  int PN=SZ(P),QN=SZ(Q);
  cout<<PN<<endl;
  REP(i,PN) cout<<P[i]<<(i==PN-1?'\n':' ');
  cout<<QN<<endl;
  REP(i,QN) cout<<Q[i]<<(i==QN-1?'\n':' ');
}

VI viz;
void f(LL a, LL n, vector<LL> &P) {
  if(a==0||n==0) return;
  int x=a>=n?n:a;
//  dump3(a,n,x);
  viz[x]=1;
  P.push_back(x);
  f(a-x,n-1,P);
}
void solve() {
  LL tot=A+B;
  LL n=0,sum=0;
  while(sum+n<=tot) ++n,sum+=n;
  if(sum>tot) --n;
  dump(n);
  viz=VI(n+1,0);
  vector<LL> P,Q;
  f(A,n,P);
  FORE(x,1,n) if(!viz[x]) Q.push_back(x);
  assert(accumulate(P.begin(),P.end(),0LL)<=A);
  assert(accumulate(Q.begin(),Q.end(),0LL)<=B);
  int PN=SZ(P),QN=SZ(Q);
  cout<<PN<<endl;
  REP(i,PN) cout<<P[i]<<(i==PN-1?'\n':' ');
  cout<<QN<<endl;
  REP(i,QN) cout<<Q[i]<<(i==QN-1?'\n':' ');
}

#include <chrono>
#include <random>
// mt19937_64 for 64 bit unsigned integer
//mt19937 rnd(time(nullptr));
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
void test() {
  while(true) {
    A=genRandNum(0,1e9+1),B=genRandNum(0,1e9+1);
    dump2(A,B);
    solve();
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
//  test();
  
  cin>>A>>B;
  solve();
  
  return 0;
}
