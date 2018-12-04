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
//#include <cmath>
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

/*
 
 12/3/2018
 
 10:35-11:36 1WA
 12:28 AC
 
 https://codeforces.com/blog/entry/63436
 
 Summary:
  - It took tons of time to fix two implementation bugs 😞
  - "black = ALL - white" should have been used to reduce complexity
 
 */

// $ ../batch MashaAndTwoFriends | diff MashaAndTwoFriends.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MashaAndTwoFriends.cpp && ./a.out
int T;

LL N,M;
LL p1x,p1y,p2x,p2y;

LL f(LL x, LL y, int c) {
  LL cnto=(y+1)/2,cnte=y/2;
  // bug 2
  LL ce=(x+1)/2, fl=x/2;
  if(c==0) {
    return cnto*ce+cnte*fl;
  } else {
    return cnte*ce+cnto*fl;
  }
}
LL cnt(LL x1, LL y1, LL x2, LL y2, int co) {
  if(x1>x2||y1>y2) return 0;
  LL a=f(x2,y2,co),b=f(x1-1,y2,co),c=f(x2,y1-1,co),d=f(x1-1,y1-1,co);
  if(co==0){
    dump4(x1,y1,x2,y2);
    dump4(a,b,c,d);
  }
  return a-b-c+d;
}
LL g(LL x1, LL y1, LL x2, LL y2, LL x3, LL y3, LL x4, LL y4, int c) {
  if(c==0) {
    LL x=p2x-p1x>=0&&p2y-p1y>=0?(p2x-p1x+1)*(p2y-p1y+1):0;
    dump(x);
    return (x2-x1+1)*(y2-y1+1)-x;
  } else {
    return (x4-x3+1)*(y4-y3+1);
  }
}
LL res[2]={};
pair<LL,LL> solve(LL x1, LL y1, LL x2, LL y2, LL x3, LL y3, LL x4, LL y4) {
  p1x=max(x1,x3),p1y=max(y1,y3),p2x=min(x2/* bug 1 */,x4),p2y=min(y2,y4);
  dump4(p1x,p1y,p2x,p2y);
  REP(co,2) {
    LL a=cnt(1,1,N,M,co),b=cnt(x1,y1,x2,y2,co),c=cnt(x3,y3,x4,y4,co),d=cnt(p1x,p1y,p2x,p2y,co),e=g(x1,y1,x2,y2,x3,y3,x4,y4,co);
    dump4(co,a,b,c);
    dump3(co,d,e);
    res[co]=a-b-c+d+e;
  }
  dump2(res[0]+res[1],N*M);
  assert(res[0]+res[1]==N*M);
  return {res[0],res[1]};
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

const int mx=11,nx=11;
int X[mx][nx];
void test() {
  while(true) {
  //  int n=genRandNum(1,mx),m=genRandNum(1,nx);
    int x1=genRandNum(1,nx),y1=genRandNum(1,mx);
    int x2=genRandNum(x1,nx),y2=genRandNum(y1,mx);
    int x3=genRandNum(1,nx),y3=genRandNum(1,mx);
    int x4=genRandNum(x3,nx),y4=genRandNum(y3,mx);
    FOR(i,1,mx)FOR(j,1,nx)X[i][j]=(i+j)%2;
    FORE(i,x1,x2)FORE(j,y1,y2)X[i][j]=0;
    FORE(i,x3,x4)FORE(j,y3,y4)X[i][j]=1;
    LL res[2]={};
    FOR(i,1,mx)FOR(j,1,nx) res[X[i][j]]++;

    FOR(i,1,mx){
      FOR(j,1,nx) cout<<X[i][j];
      cout<<endl;
    }
    
    N=mx-1,M=nx-1;
    println("%d %d %d %d",x1,y1,x2,y2);
    println("%d %d %d %d",x3,y3,x4,y4);
    auto p=solve(x1,y1,x2,y2,x3,y3,x4,y4);
    dump4(p.first,p.second,res[0],res[1]);
    assert(p.first==res[0]);
    assert(p.second==res[1]);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
//  test();
  
  cin>>T;
  REP(i,T) {
    cin>>N>>M;
    LL x1,y1,x2,y2,x3,y3,x4,y4;
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    auto p=solve(x1,y1,x2,y2,x3,y3,x4,y4);
    println("%lld %lld",p.first,p.second);
  }
  
  return 0;
}
