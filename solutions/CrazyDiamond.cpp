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

// $ cp-batch CrazyDiamond | diff CrazyDiamond.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CrazyDiamond.cpp && ./a.out

/*
 
 6/1/2019
 
 8:53-9:28 WA
 9:39 AC
 
 https://codeforces.com/blog/entry/67366
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

vector<II> res;
int pos[MAX_N];
void f(int i, int j) {
  assert(i<=j);
  int a=A[i],b=A[j];
  auto doswap=[&](int i, int j) {
    assert(abs(i-j)>=N/2);
    res.emplace_back(i+1,j+1);
    swap(A[i],A[j]);
  };
  if (abs(j-i)>=N/2) {
    doswap(i,j);
    dump(i,j);
  } else if((i<N/2&&j<N/2)||(i>=N/2&&j>=N/2)) {
    int k=(i<N/2&&j<N/2)?N-1:0;
//    int c=A[k];
    dump(i,j,k);
    doswap(j,k),doswap(i,k),doswap(j,k);
  } else {
    int k1=i<N/2?0:N-1,k2=i<N/2?N-1:0;
    dump(i,j,k1,k2);
    //int c=A[k1],d=A[k2];
    doswap(j,k1),doswap(k1,k2),doswap(i,k2),doswap(k1,k2),doswap(j,k1);
  }
  swap(pos[a],pos[b]);
}
void solve() {
  REP(i,N) pos[A[i]]=i;
  REP(i,N-1) {
    if(i!=pos[i])f(i,pos[i]);
  }
  dumpC(A,A+N);
  REP(i,N)assert(A[i]==i);
  REP(i,N) assert(pos[i]==i);
  println("%d",SZ(res));
  REP(i,SZ(res)) println("%d %d",res[i].first,res[i].second);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) {
    cin>>A[i];
    --A[i];
  }
  solve();
  
  return 0;
}
