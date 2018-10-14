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
 
 10/13/2018
 
 15:35-16:35 give up
 16:36-17:00, 19:45-20:00 read editorials
 
 10/14/2018
 
 13:00-16:10 read editorial and implemented as shown. However I cannot beat query limit. I gave up.
 
 https://codeforces.com/blog/entry/62287
 
 1. Want to find necessary partition to form bipartite graph
  => Build spanning tree (only N-1 edges are needed)
  => Suppose we have tree `T` and `V\T`. If an edge between `T` and `V\T` is found, we can make tree `T'` with new edge. When `T`=`V`, we got spanning tree.
  => Binary search works to find edges
 2. Check if partitions are really bipartite
  => e(P1)=0 and e(P2)=0
 3. If graph is not bipartite, find an edge in the same partition
  => Binary search works here too
  => If (u,v) has an edge, find path from `u` to `v` in the tree
 
 Key:
  - Spanning tree gives necessary partition of bipartite graph
   - Vertices in the same level should belong to the same partition if it's bipartite graph
   - It's possible to find edges by O(lg N) queries
  - Sufficiency can be checked by condition e(P1)=0 and e(P2)=0
  - If graph is not bipartite,
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=600+1;
int V;
VI G[MAX_N];

int CL=1000;
map<VI,int> memo;
int ask(VI S) {
  int N=SZ(S);
  assert(N>0);
  if(N==1) return 0;
  //if(N==2&&S[0]>S[1]) swap(S[0],S[1]);
  
  if(N<=CL) {
    sort(S.begin(),S.end());
    if(memo.count(S)) return memo[S];
  }
  
//  dumpAR(S);
  
  cout<<"? "<<N<<endl;
  REP(i,N) cout<<S[i]<<(i==N-1?'\n':' ');
  cout<<flush;
  int res; cin>>res;
  if(res==-1) exit(0);
  
//  dump2(SZ(S),res);
  
  if(N<=CL) memo[S]=res;
  return res;
}

int e(VI A, VI B) {
  int a=ask(A),b=ask(B);
  VI AB;
  REP(i,SZ(A)) AB.push_back(A[i]);
  REP(i,SZ(B)) AB.push_back(B[i]);
  int ab=ask(AB);
  int res=ab-a-b;
  if(res<0) {
    dumpAR(A);
    dumpAR(B);
    dump3(ab,a,b);
  }
  assert(res>=0);
  return res;
}

II findEdge(VI A, VI B, bool swapped) {
  if(SZ(A)==1&&SZ(B)==1) {
    II res={A[0],B[0]};
    if(swapped) res={B[0],A[0]};
    return res;
  }
  if(SZ(A)==1&&swapped==0) swap(A,B),swapped=1;
  VI AA[2];
  int N=SZ(A);
  REP(i,N) AA[i&1].push_back(A[i]);
  int e1=e(AA[0],B),e2=e(AA[1],B);
  if(e1>0) return findEdge(AA[0],B,swapped);
  assert(e2>0);
  return findEdge(AA[1],B,swapped);
}

int C[MAX_N];
void color(int u, int pre, int c) {
  C[u]=c;
  FORR(v,G[u]) if(v!=pre) color(v,u,c^1);
}

VI res;
void dfs(int u, int t, int pre, VI &cur) {
  if(u==t) {
    res=cur;
    return;
  }
  FORR(v,G[u]) if(v!=pre) {
    cur.push_back(v);
    dfs(v,t,u,cur);
    cur.pop_back();
  }
}

void solve() {
  VI A={1};
  VI B(V-1); REP(i,V-1) B[i]=i+2;
  while(SZ(B)) {
    int u,v; tie(u,v)=findEdge(A,B,0);
//    dump2(u,v);
    VI C; REP(i,SZ(B)) if(B[i]!=v) C.push_back(B[i]);
    B=C;
    A.push_back(v);
//    dumpAR(A);
//    dumpAR(B);
    G[u].push_back(v),G[v].push_back(u);
  }
  ZERO(C);
  color(1,-1,0);
//  dumpAR(A);
  VI P[2];
  REP(i,V) P[C[i+1]&1].push_back(i+1);
  int p1=ask(P[0]),p2=ask(P[1]);
  dump2(p1,p2);
  if(p1==0&&p2==0) {
    cout<<"Y "<<SZ(P[0])<<endl;
    int M=SZ(P[0]);
    REP(i,M) cout<<P[0][i]<<(i==M-1?'\n':' ');
    cout<<flush;
    return;
  }
  VI PP=p1>0?P[0]:P[1];
  assert(SZ(PP)>1);
//  dumpAR(PP);
  VI Q1,Q2;
  Q1.push_back(PP[0]); REP(i,SZ(PP)-1) Q2.push_back(PP[i+1]);
  while(SZ(Q2)) {
    if(!e(Q1,Q2)) {
      Q1.push_back(Q2.back()); Q2.pop_back();
      continue;
    }
//    dumpAR(Q1);
//    dumpAR(Q2);
    int s,t; tie(s,t)=findEdge(Q1,Q2,0);
    VI cur={s};
    dfs(s,t,-1,cur);
    int M=SZ(res);
    assert(M);
    cout<<"N "<<M<<endl;
    REP(i,M) cout<<res[i]<<(i==M-1?'\n':' ');
    return;
  }
  assert(0);
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>V;
  if(V==1) {
    cout<<"Y 1"<<endl;
    cout<<1<<endl;
    return 0;
  }
  solve();
  
  return 0;
}
