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

// $ ../batch VasyaAndTemplates | diff VasyaAndTemplates.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address VasyaAndTemplates.cpp && ./a.out

/*
 
 12/30/2018
 
 17:14-18:00 pause
 
 1/1/2019
 
 16:00-17:32 give up (test case #3 does not pass)
 17:32-18:44 read editorial and got AC
 
 https://codeforces.com/blog/entry/64078
 https://betrue12.hateblo.jp/entry/2018/12/26/002629
 
 My designed algorithm is correct. Implementation is shit.
 
 Key:
  - at most 3 paths in search path because of greedy property to satisfy lexicographical order
  - keeping less/more flags following digit dp strategy makes implementation simpler
 
 I figured out search space and greedy strategy. However implementation is fucked up.
 
 */

//const int MAX_N=1e6+1;
int T,K;
void nope() {
  println("NO");
}
string S,A,B;
void yup(VI &P, VI &viz) {
  int K=SZ(P);
  dumpAR(P);
  dumpAR(viz);
  REP(i,K) if(P[i]==-1) {
    REP(j,K) if(!viz[j]) {
      P[i]=j,viz[j]=1;
      break;
    }
    assert(P[i]!=-1);
  }
  string res(K,'#');
  REP(i,K) res[i]='a'+P[i];
  println("YES");
  println("%s",res.c_str());
  
  string SS(SZ(S),'#');
  REP(i,SZ(S)) SS[i]=res[S[i]-'a'];
  dump(SS);
  assert(A<=SS);
  assert(SS<=B);
}

VI P;
VI viz;
bool dfs(int i, bool more, bool less) {
  int N=SZ(S);
  if(i==N) {
    dump4(K,S,A,B);
    dumpAR(P);
    dumpAR(viz);
    return true;
  }
  int s=S[i]-'a',a=A[i]-'a',b=B[i]-'a';
  if(more&&less) {
    if(P[s]!=-1) return dfs(i+1,more,less);
    REP(c,K) if(!viz[c]) {
      P[s]=c,viz[c]=true;
      return dfs(i+1,more,less);
    }
  } else if(more) {
    // along B boundary
    if(P[s]!=-1) {
      if(P[s]>b) return false;
      if(P[s]<b) return dfs(i+1,more,true);
      return dfs(i+1,more,less);
    }
    REPE(c,b) if(!viz[c]) {
      P[s]=c,viz[c]=true;
      bool res=dfs(i+1,more,less|(c<b));
      if(!res) P[s]=-1,viz[c]=false;
      return res;
    }
  } else if(less) {
    // along A boundary
    if(P[s]!=-1) {
      if(P[s]<a) return false;
      if(P[s]>a) return dfs(i+1,true,less);
      return dfs(i+1,more,less);
    }
    for(int c=K-1; c>=a; --c) if(!viz[c]) {
      P[s]=c,viz[c]=true;
      bool res=dfs(i+1,more|(c>a),less);
      if(!res) P[s]=-1,viz[c]=false;
      return res;
    }
  } else {
    // pref(A)=pref(B)=pref(SS)
    if(P[s]!=-1) {
      int c=P[s];
      if(c<a) return false;
      if(c>b) return false;
      return dfs(i+1,more|(c>a),less|(c<b));
    }
    FOR(c,a+1,b) if(!viz[c]) {
      P[s]=c,viz[c]=true;
      bool res=dfs(i+1,true,true);
      if(!res) P[s]=-1,viz[c]=false;
      return res;
    }
    if(P[s]==-1&&!viz[a]) {
      P[s]=a,viz[a]=true;
      if(dfs(i+1,more,less|(a<b))) return true;
      P[s]=-1,viz[a]=false;
    }
    if(P[s]==-1&&!viz[b]) {
      P[s]=b,viz[b]=true;
      if(dfs(i+1,more|(b>a),less)) return true;
      P[s]=-1,viz[b]=false;
    }
  }
  return false;
}

void solve(int K, string &S, string &A, string &B) {
  P=VI(K,-1);
  viz=VI(K,0);
  if(dfs(0,false,false)) {
    yup(P,viz);
  } else {
    nope();
  }
}

void solve_wrong(int K, string &S, string &A, string &B) {
  dump4(K,S,A,B);
  int N=SZ(S);
  VI P(K,-1);
  VI viz(K,0);
  int i=0;
  while(i<N&&A[i]==B[i]) {
    int x=A[i]-'a',z=S[i]-'a';
    if(P[z]!=-1) {
      if(P[z]!=x) { nope(); return; }
    } else {
      if(!viz[x]) P[z]=x,viz[x]=1;
      else { nope(); return; }
    }
    ++i;
  }
//  dump(i);
  if(i==N) { yup(P,viz); return; }
  if(B[i]-A[i]>1) {
    int z=S[i]-'a';
    FOR(c,A[i]-'a'+1,B[i]-'a') {
      if(P[z]==-1&&!viz[c]) {
        P[z]=c,viz[c]=1;
        yup(P,viz);
        return;
      }
    }
  }
  bool ok=true;
  VI P1=P,viz1=viz;
  int c=A[i]-'a',z=S[i]-'a';
  if(P1[z]==-1&&!viz1[c]) P1[z]=c,viz1[c]=1;
  if(P1[z]!=c) goto BBBB;
  FOR(j,i+1,N) {
    int x=A[j]-'a',z=S[j]-'a';
    dump3(j,x,z);
    if(P1[z]!=-1) {
      if(P1[z]==x) continue;
      else if(P1[z]>x) break;
      else { ok=false; break; }
    } else {
      int zz=-1;
      FOR(c,x+1,K) if(!viz1[c]) zz=c;
      if(zz==-1) {
        if(!viz1[x]) { P1[z]=x,viz1[x]=1; continue; }
        else { ok=false; break; }
      } else {
        P1[z]=zz,viz1[zz]=1; break;
      }
    }
  }
  if(ok) { yup(P1,viz1); return; }
  
BBBB:;
  VI P2=P,viz2=viz;
  c=B[i]-'a',z=S[i]-'a';
  if(P2[z]==-1&&!viz2[c]) P2[z]=c,viz2[c]=1;
  if(P2[z]!=c) goto NOPE;
  ok=true;
  FOR(j,i+1,N) {
    int y=B[j]-'a',z=S[j]-'a';
    dump3(j,y,z);
    if(P2[z]!=-1) {
      if(P2[z]==y) continue;
      else if(P2[z]<y) break;
      else { ok=false; break; }
    } else {
      int zz=-1;
      REP(c,y) if(!viz2[c]) zz=c;
      if(zz==-1) {
        if(!viz2[y]) { P2[z]=y,viz2[y]=1; continue; }
        else { ok=false; break; }
      } else {
        P2[z]=zz,viz2[zz]=1; break;
      }
    }
  }
  if(ok) { yup(P2,viz2); return; }
    
NOPE:;
  nope();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>T;
  REP(i,T) {
    cin>>K>>S>>A>>B;
    solve(K,S,A,B);
  }
  
  return 0;
}
