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
 
 4/29/2018 R477 div2 D
 
 23:43-24:42 time up
 
 5/31/2018
 
 17:30-18:30 AC
 
 Editorials:
  - http://codeforces.com/blog/entry/59173
  - http://hamko.hatenadiary.jp/entry/2018/04/30/024547
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 24:42 time up
const int MAX_N=300001;
int N;
LL X1,X2;
pair<LL,int> C[MAX_N];
bool flip=false;

string yes="Yes",no="No";
void solve_wrong() {
  int i=N-1;
  int K1,K2;
  vector<int> is[2];
  for(; i>=0; --i) {
    K2=N-i;
    LL p=X2/K2;
    is[1].push_back(C[i].second);
    if(C[i].first>=p) { break; }
  }
  
  if(i==0) {
    cout<<no<<endl;
    return;
  }
  int ii=i;
  i-=1;
  bool done=false;
  for(; i>=0; --i) {
    K1=ii-i;
    LL p=X1/K1;
    is[0].push_back(C[i].second);
    if(C[i].first>=p) { done=true; break; }
  }
  if(done==false) {
    cout<<no<<endl;
    return;
  }
  if(flip) {
    swap(K1,K2);
    swap(is[0],is[1]);
  }
  cout<<yes<<endl;
  cout<<K1<<" "<<K2<<endl;
  cout<<is[0][0];
  FOR(i,1,K1) cout<<" "<<is[0][i];
  cout<<endl;
  cout<<is[1][0];
  FOR(i,1,K2) cout<<" "<<is[1][i];
  cout<<endl;
}

void solve() {
  REP(ff,2) {
    LL K1,K2;
    int s1=-1,s2=-1;
    REP(i,N) {
      K1=(X1+C[i].first-1)/C[i].first;
      int j=i+K1;
      if(j<N) {
        K2=(X2+C[j].first-1)/C[j].first;
        if(j+K2<=N) {
          s1=i,s2=j;
          break;
        }
      }
    }
    
    if(s1!=-1) {
      cout<<yes<<endl;
      if(ff==1) {
        swap(s1,s2);
        swap(K1,K2);
      }
      cout<<K1<<" "<<K2<<endl;
      cout<<C[s1].second;
      FOR(i,1,K1) cout<<" "<<C[s1+i].second;
      cout<<endl;
      cout<<C[s2].second;
      FOR(i,1,K2) cout<<" "<<C[s2+i].second;
      cout<<endl;
      return;
    }
    swap(X1,X2);
  }

  cout<<no<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>X1>>X2;
  REP(i,N) {
    LL c; cin>>c;
    C[i]={c,i+1};
  };
  sort(C,C+N);
  solve();
  return 0;
}

