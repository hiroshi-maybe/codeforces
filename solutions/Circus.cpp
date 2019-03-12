#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
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
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch Circus | diff Circus.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Circus.cpp && ./a.out

/*
 
 3/8/2019
 
 18:16-19:06 OMG I misunderstood problem...
 
 3/12/2019
 
 13:35-14:23 RE
 14:27 AC
 
 https://codeforces.com/blog/entry/65825
 
 Summary:
  - Read problem carefully
  - Define variable and make equations to clarify condition
 
 */

//const int MAX_N=1e6+1;
string SA,SC;
int N;

queue<int> A,C,B,E;

void f(int x, int y) {
  int onlya=SZ(A),both=SZ(B),onlyc=SZ(C);
  int z=2*x+y-both;
  if(z<0||z>onlya) return;
  int e1=N/2-x-y-(onlya-z);
  if(e1<0||e1>SZ(E)) return;
  int e2=N/2-(both-x)-z-(onlyc-y);
  if(e2<0||e2>SZ(E)) return;
  if(e1+e2!=SZ(E)) return;
  VI res;
  while(x--) res.push_back(B.front()),B.pop();
  while(y--) res.push_back(C.front()),C.pop();
  int zz=onlya-z;
  while(zz--) res.push_back(A.front()),A.pop();
  while(e1--) res.push_back(E.front()),E.pop();
  assert(SZ(res)==N/2);
  REP(i,SZ(res)) printf("%d ",res[i]);
  println("");
  exit(0);
}

void solve() {
  REP(i,N) {
    if(SA[i]=='1'&&SC[i]=='1') B.emplace(i+1);
    else if(SA[i]=='1') A.emplace(i+1);
    else if(SC[i]=='1') C.emplace(i+1);
    else E.emplace(i+1);
  }
  REPE(x,SZ(B))REPE(y,SZ(C)) f(x,y);
  println("-1");
}

void f_wrong(int x) {
  int y=N/2-x;
  queue<int> AA=A,CC=C,BB=B;
  VI res1,res2;
  while(SZ(res1)<x&&SZ(AA)) res1.push_back(AA.front()),AA.pop();
  while(SZ(res1)<x&&SZ(BB)) res1.push_back(BB.front()),BB.pop();
  if(SZ(res1)!=x) return;
  while(SZ(res2)<y&&SZ(CC)) res2.push_back(CC.front()),CC.pop();
  while(SZ(res2)<y&&SZ(BB)) res2.push_back(BB.front()),BB.pop();
  if(SZ(res2)!=y) return;
  int onlya=SZ(AA),onlyc=SZ(CC),both=SZ(BB);
  if(x>0)x-=min(x,onlyc);
  if(x>0)x-=min(x,both);
  if(x>0) return;
  if(y>0) y-=min(y,onlya);
  if(y>0) y-=min(y,both);
  if(y>0) return;
  assert(SZ(res1)+SZ(res2)==N/2);
  REP(i,SZ(res1)) printf("%d ",res1[i]);
  REP(i,SZ(res2)) printf("%d ",res2[i]);
  println("");
  exit(0);
}

void f_wrong2(int x, int y) {
  int onlya=SZ(A),onlyc=SZ(C),both=SZ(B);
  auto ok=[&](int x, int y)->bool {
    int a=x,c=y;
    a-=min(a,onlya);
    a-=min(a,both);
    if(a>0) return false;
    c-=min(c,onlyc);
    c-=min(c,both);
    if(c>0) return false;
    return true;
  };
  if(!ok(x,y)) return;
  if(!ok(x,y)) return;
  
    int z=N/2-x-y;
  dump(x,y,z);
  
  VI res1,res2,res3;
  while(SZ(res1)<x&&SZ(A)) res1.push_back(A.front()),A.pop();
  while(SZ(res1)<x&&SZ(B)) res1.push_back(B.front()),B.pop();
  while(SZ(res2)<y&&SZ(C)) res2.push_back(C.front()),C.pop();
  while(SZ(res2)<y&&SZ(B)) res2.push_back(B.front()),B.pop();
  while(SZ(res3)<z&&SZ(A)) res3.push_back(A.front()),A.pop();
  while(SZ(res3)<z&&SZ(C)) res3.push_back(C.front()),C.pop();
  while(SZ(res3)<z&&SZ(B)) res3.push_back(B.front()),B.pop();

  assert(SZ(res1)+SZ(res2)+SZ(res3)==N/2);
  REP(i,SZ(res1)) printf("%d ",res1[i]);
  REP(i,SZ(res2)) printf("%d ",res2[i]);
  REP(i,SZ(res3)) printf("%d ",res3[i]);
  println("");
  exit(0);
}
void solve_wrong() {
  REP(i,N) {
    if(SA[i]=='1'&&SC[i]=='1') B.emplace(i+1);
    else if(SA[i]=='1') A.emplace(i+1);
    else if(SC[i]=='1') C.emplace(i+1);
    else E.emplace(i+1);
  }
  REPE(x,N/2)for(int y=0; x+y<=N/2; ++y) f_wrong2(x,y);
  println("-1");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>SC>>SA;
  solve();
  
  return 0;
}
