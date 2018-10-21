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
 
 10/18/2018 Mail.Ru Cup 2018 R1
 
 9:02-10:32 WA
 10:34 AC after bug fix (sample #2 didn't pass in no case)
 
 http://codeforces.com/blog/entry/62563
 
 Solution in the editorial is cleaner.
 In order to give number of candies, we should be able to figure out sorted order of them.
 N-L[i]+R[i] shows how many children has less than or equal to the number of candy of child[i].
 Thus we can order them. This is relaxing the condition (necessary condition against the problem statement).
 Thus check of sufficiency is needed.
 
 Summary:
  - How to solve it?
   - What is unknown?
   - What should data satisfy if we got the result?
 
 */

// 10:32 WA
// 10:34 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
LL L[MAX_N],R[MAX_N];
int N;
int viz[MAX_N];

const string yes="YES",no="NO";
void end() {
  cout<<no<<endl;
  exit(0);
}
void solve() {
  VI res(N,0);
  ZERO(viz);
  int cur=N;
  while(true) {
    int visited=0; SETI X;
    REP(i,N) if(!viz[i]) {
      if(L[i]==0&&R[i]==0) {
        X.emplace(i);
        ++visited;
        viz[i]=true;
      }
    }
//    dump2(cur,visited);
    if(visited==0) break;
    int x=0;
    REP(i,N) {
      if(X.count(i)) res[i]=cur,L[i]=-1,++x;
      else if(!viz[i]) {
        L[i]-=x;
      }
//      dump4(i,x,viz[i],L[i]);
    }
    x=0;
    for(int i=N-1; i>=0; --i) {
      if(X.count(i)) ++x,R[i]=-1;
      else if(!viz[i]) {
        R[i]-=x;
      }
//      dump2(i,R[i]);
    }
    --cur;
  }
//  dumpAR(res);
  if(count(res.begin(),res.end(),0)!=0) {
    end();
  }
  cout<<yes<<endl;
  REP(i,N) cout<<res[i]<<(i==N-1?'\n':' ');
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>L[i];
  REP(i,N) cin>>R[i];

  solve();
  
  return 0;
}
