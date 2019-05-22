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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch RangeDeleting | diff RangeDeleting.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RangeDeleting.cpp && ./a.out

/*
 
 5/15/2019
 
 9:20-10:32 WA on 6
 
 5/20/2019
 
 22:15-23:15 try again by two pointers
 
 5/21/2019
 
 15:54-17:46 read editorial and got AC
 
 https://codeforces.com/blog/entry/67058
 https://cinnamo-coder.hatenablog.com/entry/2019/05/16/132831
 http://noimin.hatenablog.com/entry/2019/05/18/171500
 https://betrue12.hateblo.jp/entry/2019/05/16/222828
 https://twitter.com/armeria_betrue/status/1128706915989479424
 https://twitter.com/heno_code/status/1128701710220677120
 https://twitter.com/kyort0n/status/1128700669584596992
 
 Very tough implementation problem
 
 Smart code by @nuip:
 https://codeforces.com/contest/1167/submission/54189610
 
 coordinate compression vs consecutive
 => consecutive one should be chosen if it fits in memory
 
 LB and RB
 => once monotonic property is confirmed, either lb or rb matters. transform to it ({LB,RB}=>{L,R} in code)
 
 */

const int MAX_N=1e6+10;
LL A[MAX_N];
int N,X;

const int Inf=1e7;
int LB[MAX_N],RB[MAX_N];
void solve() {
  REPE(i,X) LB[i]=Inf,RB[i]=-Inf;
  LB[0]=RB[0]=-1,LB[X+1]=RB[X+1]=N;
  for(int i=N-1; i>=0; --i) LB[A[i]]=i;
  REP(i,N) RB[A[i]]=i;
//  for(int i=X; i>=0; --i) if(RB[i]==Inf) RB[i]=LB[i+1];
//  FORE(i,1,X+1) if(LB[i]==-Inf) LB[i]=LB[i-1];
  dumpC(LB,LB+X+2);
  dumpC(RB,RB+X+2);
  VI L(1,-1),R(1,N);
  FORE(i,1,X) {
    if(LB[i]<=L.back()) break;
    int a=max(RB[i],L.back());
    L.push_back(a);
  }
  dumpc(L);

  for(int i=X; i>=0; --i) {
    if(RB[i]>=R.back()) break;
    int a=min(LB[i],R.back());
    R.push_back(a);
  }
  reverse(ALL(R));
  dumpc(R);
  int r=0,M=SZ(R);
  LL res=0;
  REP(l,SZ(L)) {
    while(r<M&&(X-M+2+r<=l+1||L[l]>R[r])) ++r;
    dump(l,r,X-M+2-r,M-r);
    res+=M-r;
  }
  cout<<res<<endl;
}

bool okl(int s) {
  int pre=0;
  REP(i,N) if(A[i]<=s) {
    if(pre>A[i]) return false;
    pre=A[i];
  }
  return true;
}
bool okr(int s) {
  int pre=0;
  REP(i,N) if(A[i]>=s) {
    if(pre>A[i]) return false;
    pre=A[i];
  }
  return true;
}
void solve_wrong() {
  int good=0,bad=X+1;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    int res=okl(m);
    (res?good:bad)=m;
  }
  int a=good;
  good=X+1,bad=0;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    int res=okr(m);
    (res?good:bad)=m;
  }
  int b=good;
  dump(a,b);
  
  REPE(x,X)RB[x]=-1;
  REPE(x,X)LB[x]=MAX_N;

  REP(i,N) if(A[i]<=a) RB[A[i]]=i;
  for(int i=N-1; i>=0; --i) if(A[i]>=b) LB[A[i]]=i;
  FORE(x,1,a) SMAX(RB[x+1],RB[x]);
  for(int x=X-1; x>=b; --x) SMIN(LB[x],LB[x+1]);
  
  dumpC(RB,RB+a+1);
  dumpC(LB+b,LB+X+1);
  
  LL res=0;
  REPE(x,a) {
    int l=RB[x];
    int good=X+1,bad=max(x,b-1);
    while(abs(good-bad)>1) {
      int m=(good+bad)/2;
      int res=l<LB[m];
      (res?good:bad)=m;
    }
    int y=good;
    LL ans=(LL)(X-y+2);
    dump(x,y,X-y+2,RB[x],LB[y],ans);
    res+=ans;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>X;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
