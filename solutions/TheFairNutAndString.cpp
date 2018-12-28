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

// $ ../batch TheFairNutAndString | diff TheFairNutAndString.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheFairNutAndString.cpp && ./a.out

/*
 
 12/25/2018
 
 14:05-14:30 WA
 19:40-20:10, 21:56-22:37 AC
 
 How to avoid duplicated count by `b`?
 => Counting at every `a` worked
 
 Clean dp solution: https://codeforces.com/contest/1084/submission/46862188
 
 Analyze dependency carefully.
 
 https://codeforces.com/blog/entry/63753
 => combinatorics math solution is easier
 
 */

const int MOD=1e9+7;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};

const int MAX_N=1e6+1;
int N;
string S;

ModInt dp[MAX_N][3];
int solve_dp() {
  REP(i,MAX_N)REP(j,3)dp[i][j]=ModInt(0);
  
  int N=SZ(S);
  REP(i,MAX_N) dp[i][0]=ModInt(1);
  /*
  REP(i,N) {
    if(S[i]=='a') dp[i+1][0]+=dp[i][1];
    if(S[i]=='b') dp[i+1][1]+=dp[i][0];
    REP(r,2) dp[i+1][r]+=dp[i][r];
  }*/
  ModInt res;
  REP(i,N) {
//    dump3(i,dp[i][1],dp[i][2]);
    if(S[i]=='a') {
      // take
      dp[i+1][1]+=dp[i][0];
      dp[i+1][1]+=dp[i][2];
      res+=dp[i+1][1];
      // no take
      dp[i+1][1]+=dp[i][1];
      dp[i+1][2]+=dp[i][2];
    } else if(S[i]=='b') {
      dp[i+1][2]+=dp[i][1]+dp[i][2];
      dp[i+1][1]=0;
    } else {
      dp[i+1][1]+=dp[i][1];
      dp[i+1][2]+=dp[i][2];
    }
  }
  return res.val;
}

int solve_math() {
//  dump(S);
  vector<int> X;
  int cur=0,N=SZ(S);
  REP(i,N) {
    if(S[i]=='b'&&cur>0) X.push_back(cur),cur=0;
    else if(S[i]=='a') ++cur;
  }
  if(cur) X.push_back(cur);
//  dumpAR(X);

  ModInt res(1);
  FORR(x,X) res*=ModInt(x+1);
  return res.val-1;
}

int solve() {
  int N=SZ(S);
  ModInt dp[MAX_N]; REP(i,N+1)dp[i]=ModInt(0);
  dp[0]=1;
  int lastb=0;
  ModInt cur;
  REP(i,N) {
    if(S[i]=='a') cur+=dp[lastb];
    if(S[i]=='b') {
      dp[i]=dp[lastb]+cur;
      lastb=i,cur=0;
    }
  }
  ModInt res=dp[lastb]+cur-ModInt(1);
  return res.val;
}

#include <chrono>
#include <random>
// mt19937_64 for 64 bit unsigned integer
//mt19937 rnd(time(nullptr));
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  VI seq=genRandSeq(5,0,2);
  string s="";
  REP(i,SZ(seq)) s.push_back(seq[i]?'b':'a');
  S=s;
  
  int cnt=0;
  REP(mask,1<<SZ(seq)) {
    bool ok=true;
    VI ys;
    REP(i,SZ(seq)) if((mask>>i)&1) ys.push_back(i);
    if(SZ(ys)==0) continue;
    REP(i,SZ(ys)) if(S[ys[i]]!='a') ok=false;
    REP(i,SZ(ys)-1) {
      bool hasb=false;
      FOR(j,ys[i]+1,ys[i+1]) if(S[j]=='b') hasb=true;
      if(!hasb) ok=false;
    }
    if(ok) ++cnt;
  }
  int act=solve();
  if(act!=cnt) dump3(s,cnt,act);
  assert(act==cnt);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>S;
  int res=solve();
  cout<<res<<endl;
  
  return 0;
}
