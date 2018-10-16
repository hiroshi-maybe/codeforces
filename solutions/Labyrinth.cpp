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
 
 10/15/2018
 
 16:10-16:50 AC
 
 https://codeforces.com/blog/entry/62455
 https://twitter.com/ei1333/status/1051445065917202434
 
 I used Dijkstra's algorithm though, actually cost is always 0 or 1 in terms of horizontal move.
 
 It is interesting to use 0-1 bfs by applying 0-weight to vertical move.
 At each cell, number of R move can be calculated from # of L move.
 Thus if R is minimized to reach specific cell, L is minimized too.
 If L is minimized, R is minimized too.
 Therefore we can minimize both L and R moves. We don't care about vertical moves.
 Now problem is reduced to shortest distance problem with cost 1 to horizontal moves.
 
 22:59 add 0-1 BFS solution
 
 */

// 16:50 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e3+1;
vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
tuple<LL,LL,LL> D[MAX_N][MAX_N];
int N,M,sr,sc;
LL X,Y;
string G[MAX_N];

// Dijkstra's algorithm
LL const Inf=1e10;
LL solve_org() {
  REP(i,N)REP(j,M) D[i][j]={Inf,Inf,Inf};
  set<tuple<LL,LL,LL,int>> Q;
  Q.emplace(0,0,0,M*sr+sc); D[sr][sc]={0,0,0};
  while(SZ(Q)) {
    auto curt=*(Q.begin());
    LL l,r,d; int p; tie(l,r,d,p)=curt; Q.erase(curt);
    int i=p/M,j=p%M;
    FORR(m,moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(G[ii][jj]=='*') continue;
      LL ll=l+(m.second==-1),rr=r+(m.second==1);
      auto tup=D[ii][jj];
//      LL lcur,rcur,dcur; tie(lcur,rcur,dcur)=tup;
      tuple<LL,LL,LL> tup2={ll,rr,d+1};
      if(ll>X||rr>Y) continue;
      if(tup2<tup) {
        LL a,b,c; tie(a,b,c)=tup;
        auto it=Q.find({a,b,c,ii*M+jj});
        if(it!=Q.end()) Q.erase(it);
        Q.emplace(ll,rr,d+1,ii*M+jj); D[ii][jj]=tup2;
      }
    }
  }
  
  /*
  REP(i,N){
    REP(j,M) {
      auto t=D[i][j];
      char x=(get<0>(t)<Inf)?'+':'x';
      cout<<x;
    }
    cout<<endl;
  }*/
  
  int res=0;
  REP(i,N)REP(j,M) {
    auto t=D[i][j];
    if(get<0>(t)<Inf) ++res;
    
//    LL l,r,d; tie(l,r,d)=D[i][j];
//    printf("%d,%d,%lld,%lld,%lld\n",i,j,l,r,d);
  }
  return res;
}

// BFS
LL solve() {
  int const Inf=1e8;
  VV<int> dist(N,VI(M,Inf));
  deque<int> Q;
  Q.push_back(M*sr+sc); dist[sr][sc]=0;
  while(SZ(Q)) {
    auto p=Q.front(); Q.pop_front();
    int i=p/M,j=p%M;
    FORR(m,moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(G[ii][jj]=='*') continue;
      int d=dist[i][j]+(abs(m.second)==1);
      if(dist[ii][jj]<=d) continue;
      int x=jj-sc;
      int R=(x+d)/2,L=(d-x)/2;
      
      if(R>Y||L>X) continue;
      
      dist[ii][jj]=d;
      if(abs(m.second)==1) {
        Q.push_back(ii*M+jj);
      } else {
        Q.push_front(ii*M+jj);
      }
    }
  }
  
  /*
   REP(i,N){
   REP(j,M) {
   auto t=dist[i][j];
   char x=(t<Inf)?'+':'x';
     cout<<x;
   }
     cout<<endl;
   }*/
  
  int res=0;
  REP(i,N)REP(j,M) {
    auto t=dist[i][j];
    if(t<Inf) ++res;
    
    //    LL l,r,d; tie(l,r,d)=D[i][j];
    //    printf("%d,%d,%lld,%lld,%lld\n",i,j,l,r,d);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>sr>>sc>>X>>Y;
  --sr,--sc;
  REP(i,N) cin>>G[i];
  cout<<solve()<<endl;
  
  return 0;
}
