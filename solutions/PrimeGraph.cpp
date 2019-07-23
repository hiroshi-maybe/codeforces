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

// $ cp-batch PrimeGraph | diff PrimeGraph.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PrimeGraph.cpp && ./a.out

/*
 
 7/20/2019
 
 9:16-10:13 WA
 10:20 AC
 
 I built triangles. It didn't work only for N=4.
 
 a) N%3==0
 
 Create N/3 triangles.
 Connect vertex `i` and `i+3` until # of edges reach a prime number (Maximum +N/2 edges)
 
 b) N%3==1
 
 N/3-1 triangles and one square.
 Connect vertex `i` and `i+3` until # of edges reach a prime number (Maximum +(N-3)/2 edges)
 
 c) N%3==2
 
 N/3-1 triangles and one pentagon
 Connect vertex `i` and `i+3` until # of edges reach a prime number (Maximum +(N-3)/2 edges)
 
 https://codeforces.com/blog/entry/68534
 => Making a cycle is simpler solution...
 
 */

int N;

set<int> sieve(int N) {
  assert(N>=1);
  vector<int> fs(N+1, true);
  fs[0]=fs[1]=false;
  for(long long p=2; p*p<=N; ++p) if(fs[p]) {
    for(long long q=p*p; q<=N; q+=p) fs[q]=false;
  }
  set<int> res;
  for(int n=2; n<=N; ++n) if(fs[n]) res.emplace(n);
  return res;
}

set<int> P;
void show(set<II> &res) {
  println("%d",SZ(res));
  FORR(p,res) println("%d %d", p.first+1,p.second+1);
}

void solve() {
  if(P.empty()) P=sieve(1e5);
  set<II> res;
  auto con=[&](int u, int v) {
    assert(u>=0&&u<N);
    assert(v>=0&&v<N);
    assert(u!=v);
    if(u>v) swap(u,v);
    res.emplace(u,v);
  };
  REP(i,N) con(i,(i+1)%N);
  int i=0;
  while(P.count(SZ(res))==0) {
    assert(i<N/2);
    con(i,i+N/2);
    ++i;
  }
  show(res);
}

void solve_org() {
  if(P.empty()) P=sieve(1e5);
  set<II> res;
  VI D(N,0);
  
  auto con=[&](int u, int v) {
    assert(u>=0&&u<N);
    assert(v>=0&&v<N);
    assert(u!=v);
    if(u>v) swap(u,v);
    res.emplace(u,v);
    D[u]++,D[v]++;
  };
  
  int cnt=N/3;
  for(int i=0; i<cnt-1; i++) {
    int a=3*i,b=3*i+1,c=3*i+2;
    con(a,b),con(b,c),con(c,a);
  }
  VI xs; for(int i=3*(cnt-1); i<N; ++i) xs.push_back(i);
  REP(i,SZ(xs)) con(xs[i],xs[(i+1)%SZ(xs)]);
  
  if(N==4) {
    con(0,2);
  } else {
    int i=0;
    while(i<N&&P.count(SZ(res))==0) {
      while(i<N) {
        if(i<N&&D[i]==2&&D[i+3]==2) {
          con(i,i+3);
          break;
        }
        ++i;
      }
    }
  }
  
//  dumpc(D);
  REP(i,N) assert(D[i]==2||D[i]==3);
  show(res);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

/*
  FORE(i,3,1000) {
    dump(i);
    N=i;
    solve();
  }*/
  
  cin>>N;
  solve();
  
  return 0;
}
