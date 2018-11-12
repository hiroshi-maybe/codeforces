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
 
 11/11/2018
 
 13:56-14:49 give up
 
 Possible offset is {0, g, 2*g, .., ta-g}, g=gcd(ta,tb)
 
 I couldn't connect this with maximum length of overlapped segment.
 I tried to solve a special case where ta|tb.
 However it was just complex interval comparison. I couldn't find any clue.
 
 It's not possible to iterate all offsets.
 There should exit some greedy or mathematical way to find it.
 
 18:05-18:20, 19:50-22:19 got AC after reading editorial
 
 I went through Bezout's identity again by looking at some examples.
 Start of the interval follows k*g (k=0,1,..,tb/g-1) (mod tb).
 There are tb/g possible positions of start of the segment, where interval of positions is `g`.
 This was what I figured out when I tried by myself too.
 For each of interval, we want to know where to start `la`.
 Possible positions of `la{k}` is k*g + la (k=0,..,tb/g-1).
 
 ta segments:
 |----+----+----+----+----+----| +: k*g (start of segment)
   ^la1 ^la2 ^la3 ^la4 ^la5 ^la6
 
 tb segment:
 |---------************-------|  *: [lb,rb)
 
 la2, la3 and la4 are candidates of start of segments with maximum overlap (left boundary is closest)
 
 https://codeforces.com/blog/entry/63099
 https://math.stackexchange.com/questions/1656120/formula-to-find-the-first-intersection-of-two-arithmetic-progressions
 https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity
 
 Key:
  - Congruence: a*x ≡ c (mod b) <=> Bezou's identiry: a*x + b*y = c
   - solution exists iff c is multiple of gcd(a,b)
  - If intervals overlap, start of either interval should be contained in the other
  - Necessary shift from `x` to achive k (mod A) is possible by x (mod A)
   - k ≡ x + delta (mod A) <=> delta ≡ k - x (mod A)
   - helpful to find minimum shift to divide A
  - Modular arithmetic by % operator for negative number: (x%MOD+MOD)%MOD
 
 Summary:
  - figuring out relation to modular arithmetic is half way to the solution. I should have written more detailed figure.
 
 */

// 13:56-14:49 give up
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
LL la,ra,ta,lb,rb,tb;

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
void solve_org() {
  if(rb-lb>ra-la) swap(la,lb),swap(ra,rb),swap(ta,tb);
  LL g=gcd(ta,tb);
  LL k=(lb-la)/g;
  LL res=0;
  dump2(g,k);
  for(LL d=-1; d<=1; ++d) {
    LL kk=k+d;
    LL l1=g*kk+la;
    LL r1=l1+ra-la;
    SMAX(l1,0LL);
    dump4(l1,r1,lb,rb);
    if(l1<0) continue;
//    if(r1>tb) continue;
    LL l2=lb,r2=rb;
    LL x=min(r1,r2)-max(l1,l2);
    if(x>0) SMAX(res,x);
  }
  cout<<res<<endl;
}

LL f(LL la, LL ra, LL ta, LL lb, LL rb, LL tb) {
  LL d=gcd(ta,tb);
  LL x=lb-la;
  x=-x;
  x=(x%d+d)%d;
  LL y=lb+x;
  dump2(x,y);
  LL l1=lb,r1=rb;
  LL l2=y,r2=y+ra-la;
  dump4(l1,r1,l2,r2);
  LL l=max(l1,l2),r=min(r1,r2);
  return max(0LL,r-l);
}
void solve() {
  dump4(la,ra,ta,gcd(ta,tb));
  dump3(lb,rb,tb);
  LL a=f(la,ra,ta,lb,rb,tb),b=f(lb,rb,tb,la,ra,ta);
  dump2(a,b);
  cout<<max(a,b)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  /*
  set<int> S;
  int a=3,b=4;
  FORE(x,-10,10) FORE(y,-10,10) {
    int c=a*x+b*y;
    dump3(x,y,c);
    S.emplace(c);
  }
  dumpAR(S);*/
  
  cin>>la>>ra>>ta>>lb>>rb>>tb;
  ++ra,++rb;
  solve();
  
  return 0;
}
