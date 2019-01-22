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
typedef tuple< int, int, int, int > IIII;
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

// $ cp-batch KilaniAndTheGame | diff KilaniAndTheGame.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address KilaniAndTheGame.cpp && ./a.out

/*
 
 1/21/2019
 
 10:50-12:13 AC by replacing queue with priority queue
 
 write code after confirming SATISFYING ALL THE CONDITIONS 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡
 
 Conditions:
  1. '#' cell blocks any player
  2. first player of a cell blocks other players (players have dependency)
   => This is the condition I missed EVEN twice 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡
 
 In order to satisfy condition #2, priority queue or turn-aware BFS is necessary
 
 Summary:
  - Ensure all the conditions are satisfied
  - BFS is not applicable by distance. BFS is applicable by "turn". DO understand necessary properties to apply algorithm 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡
 
 */

const int MAX_N=1e3+1;
string G[MAX_N];
int N,M,P;
int S[20];
III D[MAX_N][MAX_N];

vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };

const int Inf=1e8;
int viz[MAX_N][MAX_N];
void solve() {
  queue<II> Q[20];
  MINUS(viz);
  
  REP(i,N)REP(j,M) {
    if(!isdigit(G[i][j])) continue;
    int p=G[i][j]-'1';
    Q[p].emplace(0,i*M+j),viz[i][j]=p;
  }
  int step=0;
  while(true) {
    bool ok=true;
    ++step;
    REP(p,P) {
      int s=S[p];
      while(SZ(Q[p])) {
        int d,pos; tie(d,pos)=Q[p].front();
        if(d==step*s) break;
        //        dump4(step,p,t,d);
        Q[p].pop();
        int i=pos/M,j=pos%M;
        
        for(auto m : moves) {
          int ii=i+m.first,jj=j+m.second;
          if(ii<0||ii>=N||jj<0||jj>=M) continue;
          if(G[ii][jj]=='#') continue;
          if(viz[ii][jj]!=-1) continue;
          viz[ii][jj]=p;
          Q[p].emplace(d+1,ii*M+jj);
          //          dump4(d,p,ii,jj);
          ok=false;
        }
      }
    }
    //    dump(step);
    if(ok) break;
  }
  
  /*
   println("st");
   REP(i,N) {
   REP(j,M) printf("%d ",viz[i][j]);
   println("");
   }
   println("ed");*/
  
  VI res(P,0);
  REP(i,N)REP(j,M) {
    int p=viz[i][j];
    //    assert(p<P);
    //    assert(p!=Inf);
    //    dump3(i,j,p);
    if(p!=-1) res[p]++;
  }
  REP(i,P) printf("%d ",res[i]);
  println("");
}

void solve_pq() {
  REP(i,N)REP(j,M)D[i][j]={Inf,Inf,Inf};
  
  priority_queue<IIII,vector<IIII>,greater<IIII>> Q;
  REP(p,P)REP(i,N)REP(j,M) {
    if(!isdigit(G[i][j])) continue;
    if(p==G[i][j]-'1') Q.emplace(0,p,S[p],i*M+j);
  }
  while(SZ(Q)) {
    int t,d,p,pos; tie(t,p,d,pos)=Q.top(); Q.pop();
    int i=pos/M,j=pos%M;
    if(D[i][j]<=make_tuple(t,p,d)) continue;
    D[i][j]={t,p,d};
    assert(G[i][j]!='#');
    assert(p<P);
    //    dump4(i,j,t,p);
    //    assert(p<P);
    if(d>=S[p]) ++t,d=0;
    for(auto m : moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(G[ii][jj]=='#') continue;
      int dd=d+1;
      if(D[ii][jj]<=make_tuple(t,p,dd)) continue;
      Q.emplace(t,p,dd,ii*M+jj);
    }
  }
  
  VI res(P,0);
  REP(i,N)REP(j,M) if(G[i][j]!='#') {
    int p=get<1>(D[i][j]);
    //    assert(p<P);
    //    assert(p!=Inf);
    //    dump3(i,j,p);
    if(p<P) res[p]++;
  }
  REP(i,P) printf("%d ",res[i]);
  println("");
}

// dfs doesn't work because optimality within a turn is not satisfied.
void solve_dfswrong() {
  queue<int> Q[20];
  MINUS(viz);
  REP(i,N)REP(j,M) if(isdigit(G[i][j])) {
    int p=G[i][j]-'1';
    Q[p].emplace(i*M+j),viz[i][j]=p;
  }
  int step=0;
  while(true) {
    ++step;
    bool upd=false;
    REP(p,P) {
      int s=S[p];
      queue<int> Q2;
      /*
      function<void(int,int,int)> dfs;
      dfs=[&](int i, int j, int d) {
        for(auto m : moves) {
          int ii=i+m.first,jj=j+m.second;
          if(ii<0||ii>=N||jj<0||jj>=M) continue;
          if(G[ii][jj]=='#') continue;
          if(viz[ii][jj]!=-1) continue;
          if(d+1>s) continue;
          viz[ii][jj]=p;
          Q2.emplace(ii*M+jj);
          dfs(ii,jj,d+1);
          //          dump4(d,p,ii,jj);
          upd=true;
        }
      };
      while(SZ(Q[p])) {
        int pos=Q[p].front(); Q[p].pop();
        dfs(pos/M,pos%M,0);
      }
      Q[p]=Q2;*/
    }
    if(!upd) break;
  }
  
  println("st");
  REP(i,N) {
    REP(j,M) printf("%d ",viz[i][j]);
    println("");
  }
  println("ed");
  
  VI res(P,0);
  REP(i,N)REP(j,M) {
    int p=viz[i][j];
    if(p!=-1) res[p]++;
  }
  REP(i,P) printf("%d ",res[i]);
  println("");
}

/*
 
 BFS should keep items in the queue where max difference of distance (turn in this problem) in it is at most 1 (thus visited check should suffice).
 
 */
void solve_bfswrong() {
  REP(i,N)REP(j,M)D[i][j]={Inf,Inf,Inf};
  
  queue<IIII> Q;
  REP(p,P)REP(i,N)REP(j,M) {
    if(!isdigit(G[i][j])) continue;
    if(p==G[i][j]-'1') Q.emplace(0,p,S[p],i*M+j);
  }
  while(SZ(Q)) {
    int t,d,p,pos; tie(t,p,d,pos)=Q.front(); Q.pop();
    int i=pos/M,j=pos%M;
    //if(D[i][j]<=make_tuple(t,p,d)) continue;
    if(get<0>(D[i][j])!=Inf) continue;
    D[i][j]={t,p,d};
    int s=S[p];
    for(auto m : moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(G[ii][jj]=='#') continue;
      int dd=d+1;
      int tt=(dd+s-1)/s;
      Q.emplace(tt,p,dd,ii*M+jj);
    }
  }
  
  
  println("st");
  REP(i,N) {
    REP(j,M) printf("%d ",get<1>(D[i][j]));
    println("");
  }
  println("ed");
  
  VI res(P,0);
  REP(i,N)REP(j,M) if(G[i][j]!='#') {
    int p=get<1>(D[i][j]);
    //    assert(p<P);
    //    assert(p!=Inf);
    //    dump3(i,j,p);
    if(p<P) res[p]++;
  }
  REP(i,P) printf("%d ",res[i]);
  println("");
}

/*
void solve__() {
  REP(i,N)REP(j,M)X[i][j]={Inf,Inf};

  FORE(p,1,P) {
    int s=S[p-1];

    queue<III> Q;
    REP(i,N)REP(j,M) {
      D[i][j]={Inf,Inf};
      if(G[i][j]=='0'+p) Q.emplace(0,s,i*M+j);
    }
    while(SZ(Q)) {
      int t,d,pos; tie(t,d,pos)=Q.front(); Q.pop();
      int i=pos/M,j=pos%M;
      D[i][j]={t,d};
      SMIN(X[i][j],{t,p});
      if(d==s) ++t,d=0;
      for(auto m : moves) {
        int ii=i+m.first,jj=j+m.second;
        if(ii<0||ii>=N||jj<0||jj>=M) continue;
        if(G[ii][jj]=='#') continue;
        int dd=d+1;
        if(D[ii][jj]<=make_pair(t,dd)) continue;
        if(X[ii][jj]<=make_pair(t,p)) continue;
        Q.emplace(t,dd,ii*M+jj);
      }
    }
    if(p==1) {
      println("st");
      REP(i,N) {
        REP(j,M) printf("%d ",D[i][j].first);
        println("");
      }
        println("ed");
    }
  }
  VI res(P,0);
  REP(i,N)REP(j,M) {
    int p=X[i][j].second;
    if(p<=P) res[p-1]++;
  }
  REP(i,P) printf("%d ",res[i]);
  println("");
}*/

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>P;
  REP(i,P) cin>>S[i];
  REP(i,N) cin>>G[i];
  
  solve();
  
  return 0;
}
