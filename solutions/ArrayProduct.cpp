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
 
 10/24/2018
 
 16:55-17:46 AC (1WA)
 
 http://codeforces.com/blog/entry/61891
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
LL A[MAX_N];
int N;

int cnt=0;
void op1(int i, int j) {
  printf("1 %d %d\n",i+1,j+1);
  ++cnt;
}
void op2(int i) {
  printf("2 %d\n",i+1);
  ++cnt;
}
void solve() {
  cnt=0;
  priority_queue<II> NQ;
  queue<int> ZQ,PQ;
  REP(i,N) {
    int a=A[i];
    if(a==0) ZQ.emplace(i);
    else if(a>0) PQ.emplace(i);
    else NQ.emplace(a,i);
  }
  
  dump3(SZ(NQ),SZ(PQ),SZ(ZQ));
  
  if(SZ(NQ)%2==1) {
    II p=NQ.top(); NQ.pop();
    int i=p.second;
    if(SZ(ZQ)==0) {
      op2(i);
    } else {
      int j=ZQ.front();
      op1(i,j);
    }
  }
  
  while(SZ(ZQ)>1) {
    int i=ZQ.front(); ZQ.pop();
    int j=ZQ.front(); ZQ.pop();
    op1(i,j); ZQ.emplace(j);
  }
  if(SZ(ZQ)) {
    assert(SZ(ZQ)==1);
    int i=ZQ.front(); ZQ.pop();
    if(SZ(PQ)||SZ(NQ)) op2(i);
  }
  
  assert(SZ(NQ)%2==0);
  while(SZ(NQ)>1) {
    II p1=NQ.top(); NQ.pop();
    II p2=NQ.top(); NQ.pop();
    int i=p1.second,j=p2.second;
    op1(i,j); NQ.emplace(p2.first,j);
  }
  if(SZ(NQ)) {
    assert(SZ(NQ)==1);
    II p=NQ.top(); NQ.pop();
    int i=p.second;
    PQ.emplace(i);
  }
  
  while(SZ(PQ)>1) {
    int i=PQ.front(); PQ.pop();
    int j=PQ.front(); PQ.pop();
    op1(i,j); PQ.emplace(j);
  }
  dump2(cnt,N-1);
  dump3(SZ(PQ),SZ(NQ),SZ(ZQ));
  assert(cnt==N-1);
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
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  while(true) {
    VI X=genRandSeq(10,-10,10);
    dumpAR(X);
    N=SZ(X);
    REP(i,N) A[i]=X[i];
    solve();
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

//  test();
  
  cin>>N;
  REP(i,N) cin>>A[i];
  
  solve();
  
  return 0;
}
