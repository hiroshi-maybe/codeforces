#include <iostream>
#include <iomanip>
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
 
 8/27/2018 AIM Tech Round 5
 
 11:17-12:00 time is up
 
 8/29/2018
 
 20:45-22:20 read editorials and add solution
 
 Editorials:
  - http://codeforces.com/blog/entry/61493

 Tweets:
  - https://togetter.com/li/1261045
  - https://twitter.com/satanic0258/status/1034153506381258755
  - https://twitter.com/uwitenpen/status/1034153111131054080
 
 I tried to solve with single bound divisor
 However it doesn't work because candidate of sell and buy cannot be determined by single bound.
 Suppose we are adding 1,2,3. In this case, divisor of sell/buy cannot be determined by single place.
 There exists 4 cases:
  - sell: {}, buy: {3,2,1}
  - sell: {3}, buy: {2,1}
  - sell: {3,2}, buy: {1}
  - sell: {3,2,1}, buy: {}
 
 I couldn't move forward any more because one boundary is not sufficient to represent boundary candidate.
 Thus we want to keep two values to keep boundary of sell/buy respectively or keep three sets for sell/unknown/buy.
 In this problem, having three sets works because elements in unknown goes into sell or buy sets only at most once. Thus amortized complexity is linear.
 
 Clean implementations:
  - Two sets:
   - http://codeforces.com/contest/1028/submission/42166524 by @LHiC
    - termination function with `end(0)` is cool 👍
   - http://codeforces.com/contest/1028/submission/42165714 by @OO0OOO00O0OOO0O00OOO0OO
  - One set with two boundary values
   - http://codeforces.com/contest/1028/submission/42162807 by @Egor
 
 Key:
  - ACC determines boundary
  - Inserted prices have three states { buy, sell, unknown }. value with unknown state can go in buy or sell when ACC happened
 
 Summary:
  - Implementation was pretty tough
  - Linked list is a bit hard to proceed. Ordered set would have been better option to take (price is unique)
   - random access and binary search is necessary
   - elements are unique
  - Try to clarify states that we need to keep. If that's not clear, analysis is not enough
  - Having two boundaries to represent an interval is typical. I should get familiar with it and reapply next time
   - boundary is not clear => keep interval to accomodate any possibility
  - I misunderstood problem about addition of non-boundary value
  - Adding 2 into buy bag for state sell: {6,5} and buy: {3,1} is valid.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=4e5+1;
int N;
LL P[MAX_N];
bool O[MAX_N];
const LL MOD=1e9+7;
const LL Inf=4e8;

/*
pair<list<LL>::iterator,list<LL>::iterator> bounds(map<LL,list<LL>::iterator> &M) {
  auto it1=M.begin(),it2=M.end(); --it2;
  return {it1,it2};
}
void solve() {
  LL res=1;
  map<LL,list<LL>::iterator> M;
  list<LL> ls;
  ls.push_front(0);
  M[0]=ls.begin();
  ls.push_back(Inf);
  auto it=M[0]; ++it;
  M[Inf]=it;
  bool s0=true;
  
  REP(i,N) {
    LL p=P[i];
    if(s0&&)
    
    auto it=*(M.lower_bound(p));
    if(O[i]) {
      // acc
      if(div!=-1&&*it!=div) res=0;
      else {
        res=2LL;
        ++it;
        div=*it;
      }
    } else {
      // add
      if(div==-1) {
        res*=2,res%=MOD;
        
      }
      LL l=M.begin()->first;
      auto it=M.end(); --it;
      LL r=it->first;
      
    }
  }
}*/

void end() {
  cout<<0<<endl;
  exit(0);
}

void solve() {
  set<int> buy,sell,unknown;
  buy.emplace(-1),sell.emplace(Inf);
  LL res=1;
  REP(i,N) {
    LL p=P[i];
    if(O[i]) {
      // acc
      if(buy.count(p)) {
        if(p!=*buy.rbegin()) end();
        buy.erase(p);
      } else if(sell.count(p)) {
        if(p!=*sell.begin()) end();
        sell.erase(p);
      } else {
        assert(unknown.count(p));
        unknown.erase(p);
        res=res*2LL%MOD;
      }
      FORR(x,unknown) (x<p?buy:sell).emplace(x);
      unknown.clear();
    } else {
      // add
      if(p<=*buy.rbegin()) {
        buy.emplace(p);
      } else if(p>=*sell.begin()) {
        sell.emplace(p);
      } else {
        unknown.emplace(p);
      }
    }
  }
  res=res*(SZ(unknown)+1)%MOD;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) {
    string o; LL p;
    cin>>o>>p;
    O[i]=o=="ACCEPT",P[i]=p;
  }
  solve();
  return 0;
}
