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

// $ ../batch NiceTable | diff NiceTable.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NiceTable.cpp && ./a.out

/*
 
 1/5/2019
 
 11:04-11:46 implement
 13:00-13:35 give up
 
 1/12/2019
 
 21:10-21:30 read editorials
 
 1/13/2019
 
 16:20-17:46 read editorials and got AC
 
 https://twishort.com/cktnc
 https://codeforces.com/blog/entry/64331
 
 Proof: https://codeforces.com/blog/entry/64331?#comment-483510
 
 Find symmetry property per row and column. Then we can test by flipping the grid.
 
 */

//const int MAX_N=1e6+1;
vector<string> A;
int N,M;

char P[4]={'A','C','G','T'};
const int Inf=1e8;

vector<string> ans;
int f(VV<char> cs, vector<string> &A) {
  ans.clear();
  int cost=0,N=SZ(A),M=SZ(A[0]);
  REP(i,N) {
    int a=Inf,fla=0;
    REP(fl,2) {
      int x=0;
      REP(j,M) x+=A[i][j]!=cs[i%2][(j%2)^fl];
      if(x<a) a=x,fla=fl;
    }
    string row(M,'?');
    REP(j,M) row[j]=cs[i%2][(j%2)^fla];
    ans.push_back(row);
    cost+=a;
  }
//  dump4(N,M,SZ(ans),SZ(ans[0]));
  assert(SZ(ans)==N&&SZ(ans[0])==M);
//  dump(cost);
  return cost;
}

vector<string> turn(vector<string> &X) {
  int N=SZ(X),M=SZ(X[0]);
  vector<string> res(M,string(N,'?'));
  REP(i,N)REP(j,M) res[j][i]=X[i][j];
  assert(SZ(res)==M&&SZ(res[0])==N);
  return res;
}

void solve() {
  int cost=Inf;
  vector<string> res;
  REP(i,4)FOR(j,i+1,4) {
    VV<char> cs(2);
    cs[0]={P[i],P[j]};
    REP(k,4)if(k!=i&&k!=j) cs[1].push_back(P[k]);
    
    // row-wise
    int cost1=f(cs,A);
    if(cost1<cost) res=ans,cost=cost1;
    
    // col-wise
    vector<string> B=turn(A);
    int cost2=f(cs,B);
    if(cost2<cost) res=turn(ans),cost=cost2;
    dump3(cost,cost1,cost2);
  }
  
  dump(cost);
  assert(SZ(res)==N&&SZ(res[0])==M);
  
  FORR(s,res) {
    println("%s",s.c_str());
  }
}

int pos1(int i, int j) {
  int x=i%2*2;
  x+=j%2;
  assert(0<=x&&x<4);
  return x;
}
int f1() {
  int res=0;
  REP(i,N)REP(j,M) {
    int x=pos1(i,j);
    res+=(P[x]!=A[i][j]);
  }
  return res;
}
int pos2(int i, int j) {
  int x=j%4;
  if(i%2==1) {
    x=(x+2)%4;
  }
  assert(0<=x&&x<4);
  return x;
}
int f2() {
  int res=0;
  REP(i,N)REP(j,M) {
    res+=P[pos2(i,j)]!=A[i][j];
  }
  return res;
}

void solve_wrong() {
  int cost=Inf;
  int p=-1; vector<char> perm;
  do {
    int a=f1(),b=f2();
    if(a<cost) p=0,perm=vector<char>(P,P+4),cost=a;
    if(b<cost) p=1,perm=vector<char>(P,P+4),cost=b;;
  } while(next_permutation(P,P+4));
  
  dump(cost);
  assert(cost!=Inf);
  vector<string> res(N,string(M,'?'));
  if(p==0) {
    int c=0;
    REP(i,N)REP(j,M) {
      res[i][j]=perm[pos1(i,j)];
      c+=(A[i][j]!=perm[pos1(i,j)]);
    }
    assert(c==cost);
  } else {
    int c=0;
    REP(i,N)REP(j,M) {
      res[i][j]=perm[pos2(i,j)];
      c+=(A[i][j]!=perm[pos2(i,j)]);
    }
    assert(c==cost);

  }
  
  FORR(s,res) {
    println("%s",s.c_str());
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) {
//    char x[MAX_N];
//    scanf("%s",x);
//    A[i]=string(x);
    string s; cin>>s;
    A.push_back(s);
  }
  solve();
  
  return 0;
}
