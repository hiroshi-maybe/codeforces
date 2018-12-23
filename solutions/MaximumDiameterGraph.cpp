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

// $ ../batch MaximumDiameterGraph | diff MaximumDiameterGraph.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MaximumDiameterGraph.cpp && ./a.out

/*
 
 12/20/2018
 
 17:07-18:32 misunderstanding of the problem statement. Graph should be CONNECTED 🖕
 22:05-22:40 AC
 
 https://codeforces.com/blog/entry/63544
 
 Two states are sufficient to build in simple manner
  - is intermediate node
  - remaining degree
 Also array is better than queue to interate to attach leaves.
 
 See https://codeforces.com/contest/1082/submission/46316454
 
 */

int N;

/*
queue<int> Q1,Q2,Q3;

int D,E,cnt=0;
void showE(int u, int v) {
  println("%d %d",u+1,v+1);
  ++cnt;
}
void pairLeaves() {
  assert(SZ(Q1)%2==0);
  while(SZ(Q1)) {
    int u=Q1.front(); Q1.pop();
    int v=Q1.front(); Q1.pop();
    showE(u,v);
  }
}

void merge23() {
  while(SZ(Q3)) {
    Q2.emplace(Q3.front()); Q3.pop();
  }
}
void makeDm(int u) {
  while(SZ(Q2)) {
    int v=Q2.front(); Q2.pop();
    showE(u,v);
    u=v;
  }
  if(SZ(Q1)) {
    int v=Q1.front(); Q1.pop();
    showE(u,v);
  }
}

void solve_wrong() {
  cin>>N;
  REP(i,N) {
    int d; cin>>d;
    if(d>=3) Q3.emplace(i);
    else if(d>=2) Q2.emplace(i);
    else Q1.emplace(i);
  }
  
  int n=SZ(Q1),m=SZ(Q2),l=SZ(Q3);
  dump3(n,m,l);
  if(n%2==0) {
    // n=even
    if(m+l==0) {
      D=1,E=SZ(Q1)/2;
      println("YES %d",D);
      println("%d",E);
      pairLeaves();
    } else {
      D=m+l-1+min(n,2),E=D+(n-min(n,2))/2;
      println("YES %d",D);
      println("%d",E);
      
      merge23();
      int u;
      if(SZ(Q1)) u=Q1.front(),Q1.pop();
      else u=Q2.front(),Q2.pop();
      makeDm(u);
      
      pairLeaves();
    }
  } else {
    // n=odd
    int u=Q1.front(); Q1.pop();
    if(l>=1) {
      D=m+l-1+min(n,2),E=D+(n>=3)+(n-min(n,3))/2;
      println("YES %d",D);
      println("%d",E);
      
      int v=Q3.front(); Q3.pop();
      showE(u,v);
      u=v;
      if(SZ(Q1)) {
        int v=Q1.front(); Q1.pop();
        showE(u,v);
      }
      merge23();
      makeDm(u);
      pairLeaves();
    } else {
      // l=0
      if(m==0) {
        if(n%2==1) { println("NO"); exit(0);
        } else {
          D=1,E=N/2;
          println("YES %d",D);
          println("%d",E);
          pairLeaves();
        }
      } else if(m==1) {
        D=1,E=(n+m)/2;
        println("YES %d",D);
        println("%d",E);
        int u=Q2.front(); Q2.pop();
        int v=Q1.front(); Q1.pop();
        showE(u,v);
        pairLeaves();
      } else {
        if(n==1) {
          D=m,E=m;
          println("YES %d",D);
          println("%d",E);
          int u=Q1.front(); Q1.pop();
          makeDm(u);
        } else {
          // n>=3
          D=m-2+min(n,2),E=D+(n-3)/2+1;
          println("YES %d",D);
          println("%d",E);
          int u=Q1.front(); Q1.pop();
          makeDm(u);
          pairLeaves();
        }
      }
    }
  }
  if(E!=cnt) dump2(E,cnt);
  assert(E==cnt);
}*/

void yup(int d, int e) {
  println("YES %d",d);
  println("%d",e);
}
void nope() {
  println("NO");
  exit(0);
}

vector<II> es;
queue<int> Q1;
priority_queue<II> PQ;

int f(int u, int d) {
  if(SZ(PQ)==0) {
    bool added=false;
    while(SZ(Q1)&&d--) {
      int v=Q1.front(); Q1.pop();
      es.emplace_back(u,v);
      added=true;
    }
    if(SZ(Q1)) return -1e8;
    return added;
  } else {
    int u2,d2; tie(d2,u2)=PQ.top(); PQ.pop();
    es.emplace_back(u,u2);
    --d,--d2;
    while(SZ(Q1)>1&&d--) {
      int v=Q1.front(); Q1.pop();
      es.emplace_back(u,v);
    }
    return 1+f(u2,d2);
  }
}

void solve() {
  cin>>N;
  REP(i,N) {
    int d; cin>>d;
    if(d==1) Q1.emplace(i);
    else PQ.emplace(d,i);
  }
  
  if(SZ(PQ)==0) {
    if(SZ(Q1)==2) {
      int u=Q1.front(); Q1.pop();
      int v=Q1.front(); Q1.pop();
      es.emplace_back(u,v);
      yup(1,SZ(es));
    } else {
      nope();
    }
  } else {
    int u,d;
    if(SZ(Q1)==0) {
      tie(d,u)=PQ.top(); PQ.pop();
    } else {
      u=Q1.front(); Q1.pop();
      d=1;
    }
    int D=f(u,d);
    if(D<0) nope();
    yup(D,SZ(es));
  }
  FORR(e,es) println("%d %d",e.first+1,e.second+1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  solve();
  
  return 0;
}
