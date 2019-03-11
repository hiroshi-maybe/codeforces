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

// $ cp-batch DianaAndLiana | diff DianaAndLiana.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DianaAndLiana.cpp && ./a.out

/*
 
 3/3/2019
 
 12:02-13:05 AC
 
 https://codeforces.com/blog/entry/65679
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N],B[MAX_N];
int M,K,N,S;
int BB[MAX_N];

void nope() {
  println("%d",-1);
  exit(0);
}
void yup(VI &res) {
  assert(M-SZ(res)>=N*K);
  println("%d", SZ(res));
  REP(i,SZ(res)) printf("%d ", res[i]+1);
  println("");
  exit(0);
}
int g(int l, int r) {
  return (r-l)/K;
}
void f(int l, int r) {
  int mrem=r-l-K,ext=r-l-S;
//  dump(l,r,mrem);
  if(mrem>ext) return;
  int s=K-(r-l),ss=max(0,s);
  dump(l,r,s);
  
  VI res;
  auto remM=[&]() {
    VI cur(M+1,0);
    FOR(i,l,r) {
      int t=A[i];
      if(cur[t]<BB[t]) cur[t]++;
      else if(mrem>0) res.push_back(i),--mrem;
    }
  };
  
  // rem from left
  int x=g(0,l-ss),y=g(r,M);
  if(x+y+1>=N) {
    dump(l-ss,l,r,x,y,N);
//    int rem=l-x*K;
//    REP(i,rem) res.push_back(i);
    remM();
//    rem=K*y;
//    REP(i,rem) res.push_back(N-i-1);
    yup(res);
  }
  x=g(0,l),y=g(r+ss,M);
  if(x+y+1>=N) {
    dump(l,r,r+ss);
    remM();
    yup(res);
  }
}
void solve() {
  REP(i,S) BB[B[i]]++;
  int r=0,cnt=0;
  map<int,int> cur;
  REP(l,M) {
    while(r<M&&cnt<S) {
      int t=A[r];
      cur[t]++;
      if(cur[t]<=BB[t]) ++cnt;
      ++r;
    }
    dump(l,r,cnt);
    if(cnt==S) f(l,r);
    int t=A[l];
    if(cur[t]<=BB[t]) --cnt;
    cur[t]--;
  }
  nope();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>M>>K>>N>>S;
  REP(i,M) cin>>A[i];
  REP(i,S) cin>>B[i];
  solve();
  
  return 0;
}
