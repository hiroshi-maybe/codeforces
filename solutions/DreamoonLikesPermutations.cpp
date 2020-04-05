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

// $ cp-batch DreamoonLikesPermutations | diff DreamoonLikesPermutations.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DreamoonLikesPermutations.cpp && ./a.out

/*
 
 4/3/2020
 
 7:45-8:13 AC
 
 https://codeforces.com/blog/entry/75559
 
 The solution in the editorial is pretty smart.
 Find a necessary condition and check the sufficiency (each number shows up only once)
 
 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

bool ok(map<int,int> &cnt, multiset<int> &set) {
  int N=SZ(set);
  if(SZ(cnt)!=N) return false;
  if(SZ(set)==0) return false;
  auto it=set.rbegin();
  int maxa=*it;
  return maxa==N-1;
}

void solve() {
  map<int,int> cntl,cntr;
  multiset<int> setl,setr;
  REP(i,N) setr.emplace(A[i]),cntr[A[i]]++;
  
  auto add=[&](int a) {
    cntl[a]++,setl.emplace(a);
  };
  auto rm=[&](int a) {
    cntr[a]--;
    if(cntr[a]==0) cntr.erase(a);
    auto it=setr.find(a);
    setr.erase(it);
  };
  
  VI res;
  REP(i,N) {
    int a=A[i];
    add(a);
    rm(a);
    if(ok(cntl,setl)&&ok(cntr,setr)) res.push_back(i+1);
  }
  println("%d", SZ(res));
  FORR(M,res) {
    println("%d %d",M,N-M);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(i,T) {
    cin>>N;
    REP(i,N)cin>>A[i],A[i]--;
    solve();
  }
  
  return 0;
}
