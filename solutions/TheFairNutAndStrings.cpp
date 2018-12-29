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

// $ ../batch TheFairNutAndStrings | diff TheFairNutAndStrings.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheFairNutAndStrings.cpp && ./a.out

/*
 
 12/25/2018
 
 15:09-15:30
 
 12/28/2018
 
 14:15-16:00 give up
 
 Worked
  - Cut prefixes of S and T at position of smallest `i` s.t. S[i]!=T[i]
  - Manage # of possible prefixes from left to right
 
 Did not work
  - special processing of S and T
  - missing addition of # of common prefixes of S and T
 
 However I couldn't process condition: # of strings is K.
 
 https://codeforces.com/blog/entry/63753
 https://codeforces.com/contest/1083/submission/46861814 by @yosupo
 https://codeforces.com/contest/1083/submission/46863302 by @tempura0224
 https://codeforces.com/contest/1083/submission/46923939 by @HIR180
 
 18:18 understood solution and got AC
 
 There are two steps to solve this problem.
 
 Reduce to binary tree. Keep observing # of nodes in every depth.
 
 cnt -> 2*cnt -1 (if left boundary S[i] is 'b') -1 (if right boundary T[i] is 'a')
 cnt = min(_, K) // at most K strings
 cnt = max(_, 1) // at least 1 string
 
 Accumulate this up to index N-1
 
 Two typical techniques:
  - # of prefix is # of nodes in Trie tree
  - # of binary numbers in left and right boundary can be calculated observing each binary digit
 
 */

const int MAX_N=1e6+1;
int N;
LL K;
string S,T;

LL dp[MAX_N];
LL solve_wrong() {
  int p=0;
  while(p<N&&S[p]==T[p]) ++p;
  ZERO(dp);
  if(p==N) return 1;
//  dump(p);
  dp[p]=min(K,2LL);
  LL res=p+dp[p];
  dp[p]-=1;
  FOR(i,p+1,N) {
    dp[i]=min(K,dp[i-1]*2LL);
    if(S[i]=='a') dp[i]=min(dp[i]+1,K);
    if(T[i]=='b') dp[i]=min(dp[i]+1,K);
    SMIN(dp[i],K);
    res=res+dp[i];
//    if(dp[i]<=K-2)res+=2LL;
    dp[i]-=1;
    SMAX(dp[i],0LL);
//    dump3(i,dp[i],res);
  }
  return res;
}

LL solve() {
  LL res=0,cnt=1;
//  dump(S);
//  dump(T);
//  dump(K);
  REP(i,N) {
    cnt*=2LL;
    if(S[i]=='b') cnt-=1;
    if(T[i]=='a') cnt-=1;
    SMIN(cnt,K);
    SMAX(cnt,1LL);
    res+=cnt;
//    dump3(i,cnt,res);
  }
  return res;
}

LL yosupo() {
  LL dif = 0, ans = 0;
  for (int i = 0; i < N; i++) {
    dif *= 2;
    if (S[i] == 'b') dif--;
    if (T[i] == 'b') dif++;
    dif = min(dif, (LL)1e10);
    ans += min(K, dif + 1);
    dump3(i,dif,ans);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K>>S>>T;
  cout<<solve()<<endl;
//  cout<<yosupo()<<endl;
  
  return 0;
}
