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
 
 10/24/2018
 
 17:47-18:20 give up

 22:00-22:56 Read twitter comments and figured out coordinate compression. Got AC.
 
 BIT may work to count each element.
 However possible range of value is [-2e14,2e14]. I also figured out that actual values are sparse.
 I couldn't reach an idea of coordinate comression. Thus I couldn't solve.
 
 Sparse values => coordinate compression
 
 http://codeforces.com/blog/entry/61891
 http://betrue12.hateblo.jp/entry/2018/09/17/214937
 https://twitter.com/armeria_betrue/status/1041657349251915777
 
 Key:
  - count # of left boundary s.t. cum[l]>cum[r+1]-T
  - BIT with coordinate compression
 
 Summary:
  - How to solve it?
   - Here is a problem related to yours and solved before. Could you use it? Could you use its method?
   - Query on sparse data is related problem I've solved => coordinate compression should be associated
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
LL A[MAX_N];
LL S;
int N;

struct BIT {
public:
  int N;
  vector<int> T; // T[1..N] has values (1-based index)
  BIT(int N): N(N) {
    T=vector<int>(N+1,0);
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
    assert(0<=i&&i<N);
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

LL solve() {
  vector<LL> sums(1,0);
  LL sum=0;
  REP(i,N) sum+=A[i],sums.emplace_back(sum);
  sort(sums.begin(),sums.end());
  sums.erase(unique(sums.begin(),sums.end()), sums.end());
  
//  dumpAR(sums);
  
  int M=SZ(sums);
  map<LL,int> T; REP(i,SZ(sums)) T[sums[i]]=i;
  BIT bit(M);
  bit.add(T[0],1);
  LL res=0;
  sum=0;
  REP(i,N) {
    sum+=A[i];
    LL lb=sum-S;
    auto it=T.upper_bound(lb);
    if(it!=T.end()) {
      LL l=it->second;
      res+=bit.query(l,M-1);
    }
    assert(T.count(sum));
    bit.add(T[sum],1);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>S;
  REP(i,N) cin>>A[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
