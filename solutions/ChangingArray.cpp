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
 
 10/18/2018 Mail.Ru Cup 2018 R1
 
 10:33-12:05 time is up
 
 1. Maximize # of non-zero interval <=> Minimize # of zero interval. res = N*(N+1)/2 - {minimal # of zero intervals}
  => ✅
 2. Inversion changes parity of all the K bits
  => ✅
 3. XOR {A[i]} = 0 <=> sum of i-th bit is even (i=0..K-1)
  => ❌ this is not useful in this problem
 4. Experiment to find useful property
  => No luck. This may be useful if we look at prefix XOR
 5. Interval of bit manipulation => search range may be small due to small # of digits (This holds only when number of bits is monotone like OR or AND manipulations)
  => ❌ this is not useful because no monotone property is found
 6. Look at right boundary of intervals. Try to find maximal left boundaries where XOR{A[l..r]}=0
  => No luck. ❌ Inversion affects succeeding intervals.
 7. Operation is allowed and it's hard to try all the patterns => there should exist an optimal construcutive strategy
  => ✅ this helps to form arbitrary number of intervals in the same "group"
 8. If inversion condition is dropped, can you solve?
  => Unfortunately no 😡. ✅ this is the first step to solve. If I cannot solve this simpler problem, I can never solve original problem.
 
 http://codeforces.com/blog/entry/62563
 
 10/22/2018
 
 24:10-25:41 read editorials
 25:42-25:54 implement and AC (2WA: array size RE and missing M[0]++)
 
 One important property of XOR manipulation is a^a = 0.
 If we take cumulative XOR, this problem without inversion can be solved.

 A =    001, 100, 100, 111, 011, 100
 P = 0, 001, 101, 001, 110, 101, 001
 
 # of 0 intervals = C(3,2) (for 001) + C(2,2) (110) = 4
 
 XOR{A[0..l]}=XOR{A[0..r]} <=> XOR{A[l+1..r]} = 0
 
 Advantage of this method is that we can compute counting with hashtable after single linear scan.
 Inversion just changes all the bits. Inversion of A[i] affects all the succeeding cumulative XORs.
 
 A =    001, 100, 011, 111, 011, 100
 P = 0, 001, 101, 110, 001, 010, 110
                  ^ ~A[2] (100->011)
 
 However possible value is still ~P[i] or P[i]. If A[2] is inverted, P[3..6] are inverted as shown above.
 Also we can choose P[i] or ~P[i] by manipulating A[i] in preferred manner.
 If we want to invert only P[i] like {.., P[i-1], ~P[i], P[i+1], ..}...
 
 A[i-1] => A[i-1], A[i] => ~A[i], A[i+1] => ~A[i+1]
 
 If we want to make 0-interval, P[i]=`a` and `~a` matter. Also we can change them arbitrarily.
 Thus we can group each cumulative XORs by keeping `a` or `~a` and minimize 0-interval corresponding to each independently.
 
 f(x) = C(x,2) + C(k-x,2) if `a` or `~a` occurs `k` times. f(x) is minimal when x=k/2
 
 Key:
  - solving part of the problem leveraging property of a^a = 0 is the key
  - use hashtable to keep cumulative XORs in terms of prefixes
  - Possible value by inversion is only two values `a` or `~a` even if
  - If we have `a` in prefixes, we can make `a` or `~a` whichever we prefer (optimal construction is possible)
  - f(x) = C(x,2) + C(k-x,2) is minimal when x = k/2 due to differentiation f'(x)=0
 
 Summary:
  - I could not even solve part of the problem without inversion. This is really POOOOOOOOR performance 😡
  - Two sum is related problem. If single previous value matters, remember it in hash table
  - If decision of current position may affect, try to separate to groups and solve independently
  - Decomposing to independent group at the end was completely out of my mind.
  - This should be a new technique when decision of one element affects both left and right (dp does not work)
 
 How to solve it?
 
 Data: array A
 Condition: A[i] can be invert(A[i])
 Unknown: max |{(l,r) : XOR{A[i]:i=l..r}!=0 }|
 
 Problem => Complement problem => Drop inversion condition => Count # of same prefix XOR => Prove arbitrary `a` or `~a` is possible in prefix XOR => Minimize # of interval of the same "group" in prefix XOR
 
 Find the connection between the data and the unknown. You may be obliged to consider auxiliary problems if an immediate connection cannot be found.
  => Connection is not immediate. I should have solved part of the problem by dropping inversion condition. However I could not solve it by myself
 Have you seen it before? Or have you seen the same problem in a slightly different form?
  => I've seen similar problem to count 0-interval of XOR (Vasya and Good Sequences). However it was misleading to solve this problem
 Do you know a related problem? Do you know a theorem that could be useful?
  => a^a=0 in XOR was definitely useful thoerem. However I couldn't come up with it. If even ON bit property is not useful, I should try it too. Two sum or cumulative sum may have been brought as a related problem once I came up with a^a=0 theorem
 Here is a problem related to yours and solved before. Could you use it? could you use its result? Could you use its method? Should you introduce some auxiliary element in order to make its use possible?
  => If a^a=0 theorem hits me, two sum or cumulative sum should have been related problem
 Could you restate the problem? Could you restate it still differently? Go back to definitions
  => I should have restated the problem that find interval with A[0..l-1] = A[0..r]
 Could you solve a part of the problem? Keep only a part of the condition, drop the other part; how far is the unknown then determined, how can it vary? Could you derive something useful from the data?
  => Dropping inversion was definitely a path to the solution
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
LL A[MAX_N];
int N,K;

LL solve() {
  MAPII M;
  int mask=(1<<K)-1;
  int cur=0;
  M[0]=1;
  REP(i,N) {
    int a=A[i];
    cur^=a;
    M[min(cur,cur^mask)]++;
  }
  LL res=1LL*N*(N+1)/2LL;
  FORR(kvp,M) {
    LL k=kvp.second;
    LL x=k/2,y=k-x;
//    dump4(kvp.first,k,x,y);
    res-=x*(x-1)/2+y*(y-1)/2;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
