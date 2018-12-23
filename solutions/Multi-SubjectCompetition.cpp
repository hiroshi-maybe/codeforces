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

// $ ../batch Multi-SubjectCompetition | diff Multi-SubjectCompetition.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Multi-SubjectCompetition.cpp && ./a.out

/*
 
 12/20/2018
 
 16:09-17:06 AC after looking at failed test case
 
 DO NOT ignore all the negative values. Are you crazy? Remember Kadane's algorithm 🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕
 
 res[i]=max(A[i], res[i-1]+A[i])

 https://codeforces.com/blog/entry/63544
 
 */

map<int,vector<LL>> X;
int N,M;

void solve_org() {
  FORR(kvp,X) sort(ALL(kvp.second)),reverse(ALL(kvp.second));
  LL res=0;
  /*
  map<int,LL> cur;
  FORR(kvp,X) cur[kvp.first]=0;
  int L=0; FORR(kvp,X) {
//    dumpAR(kvp.second);
    SMAX(L,SZ(kvp.second));
  }
  REP(i,L) {
    LL sum=0;
    map<int,LL> cur2;
    FORR(kvp,cur) {
      int s=kvp.first;
      if(SZ(X[s])<=i) continue;
      cur2[s]=cur[s]+X[s][i];
      sum+=cur2[s];
    }
//    dump3(i,SZ(cur),sum);
    SMAX(res,sum);
    cur=cur2;
  }*/
  queue<tuple<int,int,LL>> Q;
  FORR(kvp,X) Q.emplace(kvp.first,0,0);
  while(SZ(Q)) {
    int N=SZ(Q);
    LL sum=0;
    REP(_,N) {
      int s,i; LL x; tie(s,i,x)=Q.front(); Q.pop();
      if(i<SZ(X[s])) {
        x+=X[s][i];
        if(x>=0) {
          sum+=x;
          Q.emplace(s,i+1,x);
        }
      }
    }
    SMAX(res,sum);
  }
  cout<<res<<endl;
}

void solve() {
  FORR(kvp,X) sort(ALL(kvp.second)),reverse(ALL(kvp.second));
  vector<LL> cums(N+1,0);
  FORR(kvp,X) {
    LL cur=0;
    REP(i,SZ(kvp.second)) {
      cur+=kvp.second[i];
      if(cur>0) cums[i+1]+=cur;
    }
  }
  LL res=*max_element(ALL(cums));
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) {
    int s; LL r; cin>>s>>r;
    X[s].push_back(r);
  }
  solve();
  
  return 0;
}
