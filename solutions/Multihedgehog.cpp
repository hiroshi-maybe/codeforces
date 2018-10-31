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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

/*
 
 10/30/2018
 
 15:40-16:55 give up (test case #3 does not pass)
 21:40-23:16 after tons of debug, it turns out that bug was below:
 
 NG: int children=pre==-1?SZ(G[u]):SZ(G[u])+1;
 OK: int children=pre==-1?SZ(G[u]):SZ(G[u])-1;

 https://en.wikipedia.org/wiki/Centered_tree
 
 My approach seems to be correct. However something in implementation is wrong...
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N,K;
VI G[MAX_N];

int viz[MAX_N];
void end() {
  cout<<"No"<<endl;
  exit(0);
}
void dfs(int u, int pre, int d) {
  assert(d<=K);
  if(d==K) {
//    dump2(u,SZ(G[u]));
    assert(SZ(G[u])==1&&G[u][0]==pre);
  } else {
    int children=pre==-1?SZ(G[u]):SZ(G[u])-1;
//    if(N==39325) printf("%d %d %d,",u,d,children);
  //  dump2(u,SZ(G[u]));
    if(children<3) {
      dump2(u,SZ(G[u]));
      end();
    }
  }
  FORR(v,G[u])if(v!=pre)dfs(v,u,d+1);
}
void solve_org() {
  queue<int> Q;
  REP(i,N) if(SZ(G[i])==1) Q.emplace(i),viz[i]=1;
  int step=0;
  while(step<K) {
    int L=SZ(Q);
    SETI vsnext,vscur;
    if(L==0) {
      dump(step);
      end();
    }
    REP(_,L) {
      int u=Q.front(); Q.pop();
      vscur.emplace(u);
      int par=-1,cnt=0;
      FORR(v,G[u]) {
        if(viz[v]==1) end();
        if(viz[v]==0) par=v,++cnt;
      }
      if(par==-1) end();
      //dump3(u,cnt,par);
      if(cnt!=1) end();
      assert(cnt==1);
      if(vsnext.count(par)==0) {
        vsnext.emplace(par),Q.emplace(par);
      }
    }
//    dumpAR(vscur);
    FORR(u,vscur) viz[u]=2;
    FORR(v,vsnext) viz[v]=1;
    ++step;
  }
  if(SZ(Q)!=1) end();
  int c=Q.front();
  viz[c]=2;
//  if(N==39325) println("%d",c);
  REP(i,N) assert(viz[i]==2);
  dfs(c,-1,0);
  cout<<"Yes"<<endl;
}

vector<int> findCenter() {
  vector<int> deg(N,0);
  queue<int> Q;
  for(int u=0; u<N; ++u) {
    int x=G[u].size();
    deg[u]=x;
    if(x<=1) Q.emplace(u);
  }
  int d=0;
  vector<int> res;
  while(Q.size()) {
    int L=Q.size();
    res=vector<int>();
    for(int _=0; _<L; ++_) {
      int u=Q.front(); Q.pop();
      res.emplace_back(u);
      --deg[u];
      for(auto v : G[u]) {
        --deg[v];
        if(deg[v]==1) Q.emplace(v);
      }
    }
    ++d;
  }
  sort(res.begin(),res.end());
  res.erase(unique(res.begin(),res.end()),res.end());
  assert(1<=res.size()&&res.size()<=2);
  return res;
}

int cntd[MAX_N];
void dfs2(int u, int pre, int d) {
  if(d>K) end();
  if(d==K) {
    if(SZ(G[u])!=1) end();
  } else {
    int children=pre==-1?SZ(G[u]):SZ(G[u])-1;
    //if(N==39325&&u==365) printf("%d->%d %d %d,",pre,u,d,children);
    //  dump2(u,SZ(G[u]));
    if(children<3) {
      dump2(u,SZ(G[u]));
      end();
    }
  }
  FORR(v,G[u])if(v!=pre)dfs2(v,u,d+1);
}

void solve() {
  VI cs=findCenter();
  if(SZ(cs)!=1) end();
  int c=cs.front();
  dfs2(c,-1,0);
  cout<<"Yes"<<endl;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
//  if(N==39325)REP(i,SZ(G[365])) printf("%d,",G[365][i]);
  
  solve();
  
  return 0;
}

/*
class range {private: struct I { int x; int operator*() { return x; }bool operator!=(I& lhs) { return x<lhs.x; }void operator++() { ++x; } }; I i, n;public:range(int n) :i({ 0 }), n({ n }) {}range(int i, int n) :i({ i }), n({ n }) {}I& begin() { return i; }I& end() { return n; }};
#define ng {cout<<"No"<<endl;return 0;}
#define ok {cout<<"Yes"<<endl;return 0;}
using VVI=vector<VI>;
int main(){
  int n,k;
  cin>>n>>k;
  VVI g(n);
  for(int i:range(n-1)){
    int a,b;
    cin>>a>>b;
    a--;b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  VI vx;
  VI used(n,0);
  
  for(int i:range(n)){
    if(g[i].size()==1){
      vx.push_back(i);
    }
    else if(g[i].size()<3) {
      if(n==39325) println("degree <3 %d (%d)",i,SZ(g[i]));
      ng;
    }
  }
  for(int i:range(k)){
    int sz = vx.size();
    if(sz==0){
      if(n==39325) println("no leaves at step %d",i);
      ng;
    }
    VI nxt;
    for(int _:range(sz)){
      used[vx[_]]=1;
    }
    for(int _:range(sz)){
      int v = vx[_];
      int par = -1;
      for(int u:g[v]){
        if(used[u]==0&&par!=-1) {
          if(n==39325) println("%d already visited",u);
          ng;
        }
        if(used[u]==0)par=u;
      }
      if(par==-1){
        if(n==39325) println("no parent %d",v);
        ng;
      }
      nxt.push_back(par);
    }
    sort(ALL(nxt));
    nxt.erase(unique(ALL(nxt)),nxt.end());
    swap(vx,nxt);
  }
  if(vx.size()!=1){
    if(n==39325) println("invalid # of centers %d",SZ(vx));
    ng;
  }
  int center=vx[0];
  for(int i:range(n)){
    if(i==center){
      if(g[i].size()<3) {
        if(n==39325) println("children <3 %d",SZ(g[i]));
        ng;
      }
    }
    else{
      if(g[i].size()==1);
      else if(g[i].size()<4) {
        if(n==39325) println("children %d <4 of %d",SZ(g[i]),i);
        ng;
      }
    }
  }
  ok;
  return 0;
}*/
