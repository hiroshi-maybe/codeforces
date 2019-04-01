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

// $ cp-batch PalindromicMatrix | diff PalindromicMatrix.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PalindromicMatrix.cpp && ./a.out

/*
 
 3/29/2019
 
 15:59-16:56 AC
 
 https://codeforces.com/blog/entry/65396
 
 */

const int MAX_N=30+1;
int A[MAX_N*MAX_N];
int N;

void nope() {
  println("NO");
  exit(0);
}
void solve() {
  map<int,int> cnt;
  REP(i,N*N) cnt[A[i]]++;
  VV<int> res(N,VI(N,-1));
  if(N%2==0) {
    FORR(kvp,cnt) if(kvp.second%4!=0) nope();
    REP(i,N/2) {
      REP(j,N/2) {
        auto p=*cnt.begin();
        cnt.erase(p.first);
        assert(p.second%4==0);
        res[i][j]=res[i][N-j-1]=res[N-i-1][j]=res[N-i-1][N-j-1]=p.first;
        p.second-=4;
        if(p.second) cnt.emplace(p);
      }
    }
    assert(cnt.empty());
  } else {
    queue<int> Q1,Q2,Q4;
    FORR(kvp,cnt) {
      int x=kvp.second;
      while(x>=4) Q4.emplace(kvp.first),x-=4;
      while(x>=2) Q2.emplace(kvp.first),x-=2;
      while(x>=1) Q1.emplace(kvp.first),x-=1;
    }
    REP(i,N/2) {
      REP(j,N/2) {
        if(Q4.empty()) nope();
        int a=Q4.front(); Q4.pop();
        res[i][j]=res[i][N-j-1]=res[N-i-1][j]=res[N-i-1][N-j-1]=a;
      }
    }
    while(SZ(Q4)) {
      int a=Q4.front(); Q4.pop();
      Q2.emplace(a),Q2.emplace(a);
    }
    REP(i,N/2) {
      if(Q2.empty()) nope();
      int a=Q2.front(); Q2.pop();
      res[i][N/2]=res[N-i-1][N/2]=a;
      if(Q2.empty()) nope();
      int b=Q2.front(); Q2.pop();
      res[N/2][i]=res[N/2][N-i-1]=b;
    }
    if(Q1.empty()) nope();
    res[N/2][N/2]=Q1.front();
  }
  
  println("YES");
  REP(i,N){
    REP(j,N) printf("%d ",res[i][j]);
    println("");
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N*N) cin>>A[i];
  solve();
  
  return 0;
}
