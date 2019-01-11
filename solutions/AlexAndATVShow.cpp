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
#include <bitset>
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

// $ ../batch AlexAndATVShow | diff AlexAndATVShow.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AlexAndATVShow.cpp && ./a.out

/*
 
 1/8/2019
 
 10:08-11:15 give up
 
 My analysis:
 
 Result of query is parity. Thus we want to drop unnecessary data to save memory.
 max V is not so large (7e3). bitset<7e3> S[MAX_N] fits in memory limit.
 This works for union and insertion operations too.
 However I couldn't figure out how to process production by GCD 😞
 
 I tried prime factorization though, I couldn't find any clue.
 
 Auxiliary problem: efficient data structure to map GCD to parity of multiset.
 
 19:10-19:47, 22:00-23:00 read editorials.
 
 https://codeforces.com/blog/entry/64310
 https://betrue12.hateblo.jp/entry/2019/01/05/170114
 https://ja.wikipedia.org/wiki/%E3%83%A1%E3%83%93%E3%82%A6%E3%82%B9%E9%96%A2%E6%95%B0
 
 Actually we need to resolve GCD part first.
 Find data structure to compute parity of GCDs and try to answer query 4.
 
 1/9/2018
 
 14:00-18:40, 20:40-23:30 read editorials
 
 1/10/2018
 
 16:30-19:30 understand editorials and got AC
 
 Two keys are way too far from my level
  - represent set by divisor set for weak convolution of GCD
  - IEP to restore number from divisor set
 
 - bitset
 - Convolution
 - Divisor set and GCD
 - Mobius inversion formula
 - Inclusion Exclusion Principle
 
 It took two days to understand why multiples of `v` works to know occurence of `v`.
 
 We gonna check out multiple of `v` which is represented by p*v (p>=1).
 We have all the divisors in S[x]. Let's show occurence of `p` for p=1..
 
       | divisor bits regarding p
 p p*v | 1 2 3 (4) 5 6 7 (8) 9 10 11 (12) 13
 1 4   | *
 2 8   | * *
 3 12  | *   *
 4 16  | *      *
 5 20  | *         *
 6 24  | * * *       *
 
         ^ We are interested in parity of here
 
 `p` of multiple of `v` affects occurence.
 Thus we want to take into account them by Inclusion Exclusion Principle.
 Let's focus on prime factors of `p`.
 
 f(v)=∑ { g(i) : i=1..MAX_N }, where g(i)=occurence of `i` which is multiple of v
 
 result of query(x,v) is g(v).
 f(v) includes v s.t. v has divisor 2*p, 3*p, 5*p... We subtract it.
 f(v) -= ∑ f(prime_i)
 Also adjust occurence which has both divisors (2*p,3*p), (2*p,5*p), ..
 f(v) += ∑ f(prime_i*prime_j) (prime_i<prime_j)
 
 This is process of Inclusion Exclusion Principle as seen in http://compro.tsutajiro.com/archive/181015_incexc.pdf
 The sign of ∏ { prime number } is Mobius function 𝜇(x) https://en.wikipedia.org/wiki/M%C3%B6bius_function
 
 */

const int MAX_N=7e3+10;
const int MAX_NN=1e5+10;
bitset<MAX_N> divs[MAX_N],mask[MAX_N],S[MAX_NN];
int sqfree[MAX_N];

int N,Q;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  REP(n,MAX_N) sqfree[n]=1;
  for(int n=2; n*n<MAX_N; ++n) for(int m=1; n*n*m<MAX_N; ++m) sqfree[n*n*m]=0;
  
//  REP(i,20) dump2(i,sqfree[i]);
  
  FOR(n,1,MAX_N) {
    for(int d=1; d*d<=n; ++d) if(n%d==0) {
      divs[n][d]=1;
      if(d*d!=n) divs[n][n/d]=1;
    }
    for(int m=n; m<MAX_N; m+=n) if(sqfree[m/n]) mask[n][m]=1;
  }
  
  cin>>N>>Q;
  
  string res;
  REP(i,Q) {
    int q; cin>>q;
    if(q==1) {
      int x,v; cin>>x>>v;
      S[x]=divs[v];
    } else if(q==2) {
      int x,y,z; cin>>x>>y>>z;
      S[x]=S[y]^S[z];
    } else if(q==3) {
      int x,y,z; cin>>x>>y>>z;
      S[x]=S[y]&S[z];
    } else if(q==4) {
      int x,v; cin>>x>>v;
      int p=(S[x]&mask[v]).count()%2;
      dump3(x,v,p);
      res.push_back('0'+p);
    } else assert(false);
  }
  cout<<res<<endl;
  
  return 0;
}


/*
//#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

bitset <7010> B[100010];
bitset <7010> mask[7010];
bitset <7010> single[7010];
int sign[7010];

int main(void){
  int i,j,k;
  
  REP(i,100010) B[i].reset();
  REP(i,7010) mask[i].reset();
  REP(i,7010) single[i].reset();
  
  for(i=1;i<7010;i++) sign[i] = 1;
  for(i=2;i*i<7010;i++) for(j=1;i*i*j<7010;j++) sign[i*i*j] = 0;
  
  REP(i,40) dump2(i,sign[i]);
  
  for(i=1;i<7010;i++) for(j=i;j<7010;j+=i){
    if(sign[j/i]) mask[i][j] = true;
    single[j][i] = true;
  }
  
  REP(i,40) dump2(i,mask[4][i]);
  
  dump2(single[1][1],mask[4].count());
  
  int N,Q,q;
  string ans;
  
  cin >> N >> Q;
  
  REP(q,Q){
    int t,x,y,z,v;
    scanf("%d", &t);
    
    if(t == 1){
      scanf("%d%d", &x, &v);
      B[x] = single[v];
    } else if(t == 2){
      scanf("%d%d%d", &x, &y, &z);
      B[x] = (B[y] ^ B[z]);
    } else if(t == 3){
      scanf("%d%d%d", &x, &y, &z);
      B[x] = (B[y] & B[z]);
    } else if(t == 4){
      scanf("%d%d", &x, &v);
      int c = (B[x] & mask[v]).count();
      ans += (char)('0' + c % 2);
    }
  }
  
  // REP(i,10) REP(j,1000) if(B[i][j]) cout << i << ' ' << j << endl;
  
  printf("%s\n", ans.c_str());
  
  return 0;
}
*/
