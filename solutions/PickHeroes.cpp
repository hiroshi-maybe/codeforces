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

/*
 
 12/10/2018
 
 14:40-15:44 WA on test #7
 16:30-17:10 redesigned algorithm by myself and got AC
 
 https://codeforces.com/blog/entry/63461
 
 Forcing opponent's turn is the most powerful choice.
 It should be picked whenever possible.
 Otherwise pick up largest choice.
 
 */

// $ ../batch PickHeroes | diff PickHeroes.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PickHeroes.cpp && ./a.out
const int MAX_N=2e3+1;
int P[MAX_N];
int Q[MAX_N];
int viz[MAX_N];
int N,M,T;

void choose(int x) {
  viz[x]=1;
  cout<<x<<endl;
}
int xread() {
  int i; cin>>i;
  if(i==-1) exit(0);
  assert(!viz[i]);
  viz[i]=1;
  return i;
}

void solve() {
  ZERO(viz);
  T-=1;
  int t=0,force=-1;
  while(t<2*N) {
    if(t%2==T) {
      // my turn
      if(force!=-1) {
        choose(force);
        force=-1;
      } else {
        vector<II> ps;
        FORE(i,1,2*N)if(!viz[i]) ps.emplace_back((Q[i]>0?1e4:0)+P[i],i);
        sort(ALL(ps)); reverse(ALL(ps));
        int v=ps.front().first;
        vector<II> qs;
        REP(i,SZ(ps)) if(ps[i].first==v) {
          int j=ps[i].second;
          int part=0;
          if(Q[j]>0) part=P[Q[j]];
          qs.emplace_back(part,j);
        }
        sort(ALL(qs));
        auto it=lower_bound(ALL(qs),make_pair(1,-1));
        if(it==qs.end()) it=qs.begin();
//        dump2(it->first,it->second);
        choose(it->second);
      }
    } else {
      // opponent turn
      int x=xread();
      if(Q[x]>0&&!viz[Q[x]]) force=Q[x];
    }
    ++t;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,2*N) cin>>P[i+1];
  REP(i,M) {
    int a,b; cin>>a>>b;
    Q[a]=b;
    Q[b]=a;
  }
  cin>>T;
  
  solve();
  
  return 0;
}
