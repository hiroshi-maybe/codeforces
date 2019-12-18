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

// $ cp-batch DiverseMatrix | diff DiverseMatrix.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DiverseMatrix.cpp && ./a.out

/*
 
 12/17/2019
 
 7:26-7:48 AC
 
 https://codeforces.com/blog/entry/72243
 
 */

int R,C;
LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
void nope() {
  cout<<0<<endl;
  exit(0);
}
int mx[501][501];
void solve() {
  if(R==1&&C==1) nope();
  if(C==1) {
    REP(i,R) {
      println("%d", i+2);
      mx[i][0]=i+2;
    }
  } else {
    VI cs(C);
    REP(i,C)cs[i]=R+i+1;
    REP(i,R) {
      REP(j,C) {
        int a=(i+1)*cs[j];
        printf("%d ", a);
        mx[i][j]=a;
      }
      println("");
    }
  }

  VI B;
  REP(i,R) {
    int g=mx[i][0];
    REP(j,C) g=(int)gcd(g,mx[i][j]);
    B.push_back(g);
  }
  REP(j,C) {
    int g=mx[0][j];
    REP(i,R) g=(int)gcd(g,mx[i][j]);
    B.push_back(g);
  }
  sort(ALL(B));
  dumpc(B);
  assert(SZ(B)==R+C);
  REP(i,R+C) assert(B[i]==i+1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>R>>C;
  solve();
  
  return 0;
}
