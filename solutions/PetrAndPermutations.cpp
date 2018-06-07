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
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
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
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 5/29/2018
 
 25:47-26:00 give up
 
 5/6/2018
 
 18:00-18:46 Read editorials and add solution
 
 Editorials:
  - https://codeforces.com/blog/entry/59758
  - http://par.hateblo.jp/entry/2018/05/30/101309
  - http://yosupo.hatenablog.com/entry/2018/05/30/034234
 
 Tweets:
  - https://togetter.com/li/1232170
  - https://twitter.com/_TTJR_/status/1001520890360676352
  - https://twitter.com/tempura_pp/status/1001527223382233088
  - https://twitter.com/satanic0258/status/1001522786878144512
  - https://twitter.com/ei1333/status/1001520510763646976
 
 Parity of permutation:
  - https://en.wikipedia.org/wiki/Symmetric_group#Transpositions
  - https://en.wikipedia.org/wiki/Parity_of_a_permutation
  - https://mathtrain.jp/permutation
 
 Summary:
  - I had no idea about even/odd permutation 😞
  - I completely missed description "takes a random pair of `different` elements and swaps them"
 
 */
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e6+1;
vector<int> P;
int N;
const string pet="Petr",umn="Um_nik";

struct BIT {
public:
  int N;
  vector<int> T; // T[1..N] has values (1-based index)
  BIT(int N): N(N) {
    T.resize(N+1,0);
  }
  
  // query in [0,r] : ∑ { sum[i] : i=0..r }
  int query(int r) {
    ++r; // 0-based index to 1-based index
    int res=0;
    while(r>0) {
      res+=T[r];
      r-=lsone(r);
    }
    return res;
  }
  
  // query ∑ { sum[i] : i=l..r }
  int query(int l, int r) {
    assert(l<=r&&0<=l&&r<N);
    return query(r)-query(l-1);
  }
  
  // sum[i]+=x
  void add(int i, int x) {
    assert(0<=i&&i<=N);
    ++i; // 0-based index to 1-based index
    while(i<=N) {
      T[i]+=x;
      i+=lsone(i);
    }
  }
  
  // sum[i]=x
  void update(int i, int x) {
    int v1=query(i)-query(i-1);
    add(i,x-v1);
  }
  
  // compute total inversions
  int inversions(vector<int> ns) {
    int N=ns.size(),res=0;
    for(int i=N-1; i>=0; --i) {
      // Count elements which stays in right side and smaller
      res+=query(ns[i]-1);
      add(ns[i],1);
    }
    return res;
  }
private:
  int lsone(int i) { return i&-i; }
};

string solve() {
  BIT bit(N);
  int inv=bit.inversions(P);
  if(N%2==0) return inv%2==0?pet:umn;
  else return inv%2==0?umn:pet;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  P.resize(N);
  REP(i,N) cin>>P[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
