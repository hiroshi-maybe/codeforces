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
 
 11/4/2018
 
 21:00-22:00 give up
 
 We need to manage data in some interval
  -> segment tree with coordinate compression?
  -> online update blocks how to figure out intervals
  -> even if I got intervals before hand, I don't know how to get values at specific index...
 
 Coordinate compression
  -> imos?
 
 11/6/2018
 
 13:20-16:50 read editorial and got AC
 
 http://codeforces.com/blog/entry/62985
  - Proof is interesting. Parity is used to show inviolation of invariant.
 
 Border relation is an analogy of special distance between vertices.
 This association is based on property of Abelian group of XOR operation
 
 https://en.wikipedia.org/wiki/Exclusive_or#Relation_to_modern_algebra
 https://en.wikipedia.org/wiki/Shortest_path_problem#General_algebraic_framework_on_semirings:_the_algebraic_path_problem
 
 Also XOR weight in the tree is typical as well because we can keep only XOR with root of the tree to query distance between arbitrary nodes.
 d(a,b) = d(a,root) XOR d(b,root)
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=2e5+1;
int Q;
map<int,int> comp;

int getid(int a) {
  if(comp.count(a)) return comp[a];
  comp[a]=SZ(comp);
  return comp[a];
}

struct UF {
public:
  int groupNum;
  vector<int> X;
  UF(int N) {
    uf=vector<int>(N);
    rank=vector<int>(N);
    X=vector<int>(N);
    for(int i=0; i<N; ++i) uf[i]=i,rank[i]=0;
    groupNum=N;
  }

  int find(int i) {
    return uf[i]==i?i:find(uf[i]);
  }
  
  int dist(int u) {
    int cur = 0;
    while(uf[u] != u) {
      cur ^= X[u];
      u = uf[u];
    }
    return cur;
  }
  
  bool same(int x, int y) {
    return find(x)==find(y);
  }
  
  void unite(int x, int y, int z) {
    int px=find(x);
    int py=find(y);
    if(px==py) return;
    groupNum--;
    
    z=dist(x)^dist(y)^z;

    if (rank[px]==rank[py]) {
      uf[px]=py; X[px]=z;
      rank[py]++;
      return;
    }
    if (rank[px]<rank[py]) {
      uf[px]=py; X[px]=z;
    } else {
      uf[py] =px; X[py]=z;
      if(rank[px]==rank[py]) ++rank[px];
    }
  }
private:
  vector<int> rank;
  vector<int> uf;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin>>Q;
  UF uf(2*Q+10);
  int last=0;
  while(Q--) {
    int t,l,r; cin>>t>>l>>r;
    l^=last,r^=last;
    if(l>r) swap(l,r);
    ++r;
//    println("Q %d %d %d",t,l,r);
    dump4(l,r,getid(l),getid(r));
    l=getid(l),r=getid(r);
    if(t==1) {
      int x; cin>>x;
      x^=last;
      uf.unite(l,r,x);
    } else {
      int p1=uf.find(l),p2=uf.find(r);
      if(p1!=p2) {
        last=1;
        println("%d",-1);
      } else {
        last=uf.dist(l)^uf.dist(r);
        println("%d",last);
      }
    }
  }
  
  return 0;
}
