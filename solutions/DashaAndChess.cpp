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

// $ ../batch DashaAndChess | diff DashaAndChess.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DashaAndChess.cpp && ./a.out

/*
 
 1/15/2019
 
 20:40-21:40 give up
 21:40-22:40 understand editorial.
 22:40-24:12 got AC after bug fixes. Judge code does returns "0 x y" instead of "0 0 0". Sucks 🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕
 
 Suppose rooks stay in the same row `r` (or column)
 If # of rooks at row `r` >= |row of king - r|, king wins.
 
 However suppose rooks stay diagonally....
 
 +---------+
 |r        |
 | r       |
 |  r      |
 |   .     |
 |    .    |
 |     r   |
 |         |
 |         |
 |        K|
 +---------+
 
 Rook keeps escaping from king. I have no idea to win.
 
 https://codeforces.com/blog/entry/64543
 https://codeforces.com/blog/entry/64545
 
 If we hit in either column or row of a rook, we win.
 Thus moving diagonally has more chance to hit row or column of a rook.
 
 We want to maximize the chance to hit them.
 If we start from centent of the board, steps to sweep one of four quandra is upper-bounded by 499.
 We want to choose a quadrant with the most chance to win.
 One rook can be caught in 3 out of 4 quadrants. We can count the best quadrant by checking positions of all the rooks.
 Pigeonhole principle proves that we always win if we choose the best quadrant.
 The worst case is that rooks are distributed to quadrants equally (666/4=161.5).
 We can sweep 666*(3/4)=499.5 rooks by 499 moves. Thus pigeonhole principle guarantees that at least one rook cannot escape from us.
 
 We don't need to directly hit rooks. Thus figuring out that sweeping diagonally gives more chance to win is the key of this problem.
 Then moving to center firstly comes up because which upper-bounds necessary moves later on.
 Keeping pigeonhole principle in mind to resolve this kind of "unknown" should also be useful.
 
 */

const int MAX_N=666+10;
int board[1000][1000];
II rooks[MAX_N];
II me;

void move(int dx, int dy) {
  int x=me.first,y=me.second;
  assert(1<=x+dx&&x+dx<=999&&1<=y+dy&&y+dy<=999);
  if(board[x+dx][y+dy]) {
    FORE(dxdx,-1,1)FORE(dydy,-1,1) if(!(dxdx==0&&dydy==0)) REP(i,666) {
      if(x+dxdx<=0||x+dxdx>999) continue;
      if(y+dydy<=0||y+dydy>999) continue;

      if(rooks[i+1].first==x+dxdx&&rooks[i+1].second!=y+dydy&&board[x+dxdx][y+dydy]==0) {
        dx=dxdx,dy=dydy;
        goto out;
      }
      if(rooks[i+1].second==y+dydy&&rooks[i+1].first!=x+dxdx&&board[x+dxdx][y+dydy]==0) {
        dy=dydy,dx=dxdx;
        goto out;
      }
    }
  }
out:
  assert(!(dx==0&&dy==0));
  x+=dx,y+=dy;
  assert(board[x][y]==0);
  assert(1<=x&&x<=999&&1<=y&&y<=999);

  me.first=x,me.second=y;
  cout<<x<<" "<<y<<endl<<flush;
//  dump2(x,y);
  REP(i,666) {
    if(rooks[i+1].first==me.first) exit(0);//dump2(i+1,rooks[i+1].first);
    if(rooks[i+1].second==me.second) exit(0);//dump2(i+1,rooks[i+1].second);
  }
  
  int k; cin>>k>>x>>y;
//  dump3(k,x,y);
  if(k==0&&x==0&&y==0) assert(false);
  if(k==-1) exit(0);
//  if(k<1||k>666) dump3(k,x,y);
  assert(1<=x&&x<=999&&1<=y&&y<=999);
  assert(1<=k&&k<=666);
  board[rooks[k].first][rooks[k].second]=0;
  rooks[k]={x,y};
  board[x][y]=1;
}

void solve() {
  while(me.first!=500||me.second!=500) {
    int dx=0,dy=0;
    if(me.first<500) dx+=1;
    else if(me.first>500) dx-=1;
    
    if(me.second<500) dy+=1;
    else if(me.second>500) dy-=1;
    
    move(dx,dy);
  }
  int cnt[4]={};
  REP(i,666) {
    auto p=rooks[i+1];
    int x=p.first,y=p.second;
    int a=0,b=0;
    if(x>500) a=1;
    if(y>500) b=1;
    cnt[(a<<1)+b]++;
    cnt[((a^1)<<1)+b]++;
    cnt[(a<<1)+(b^1)]++;
  }
  vector<II> as(4); REP(i,4)as[i]={cnt[i],i};
  sort(as.rbegin(),as.rend());
  int q=as[0].second;
  int dx=(q>>1)&1?+1:-1;
  int dy=q&1?+1:-1;
  while(true) move(dx,dy);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int x,y;
  
  cin>>x>>y;
  me={x,y};
  REP(i,666) {
    cin>>x>>y;
    rooks[i+1]={x,y};
    board[x][y]=1;
  }
  solve();
  
  return 0;
}
