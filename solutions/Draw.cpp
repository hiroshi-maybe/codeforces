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

// $ cp-batch Draw | diff Draw.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Draw.cpp && ./a.out

/*
 
 2/23/2019
 
 2:32-3:02 AC
 
 Data: Sequence of pairs
 Condition: pair[i] should happen at some moment
 Unknown: # of possible pair (x,x)
 
 Keep in mind that unknown is clearly defined.
 Number of unique pair (x,x) is the unknown to be solved.
 It was not clearly in my mind during the contest. Thus it was tough quickly.
 From the idea of pair (x,x), it's obvious that we should subtract 1 if previous pair is (x',x').
 
 https://codeforces.com/blog/entry/65487
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N],B[MAX_N];
int N;

void solve() {
  LL res=1;
  FORE(i,1,N) {
    LL a0=A[i-1],a=A[i],b0=B[i-1],b=B[i];
    LL l=max(a0,b0),r=min(a,b);
    //    dump(i,l,r);
    res+=max(0LL,r-l+1);
    if(a0==b0) --res;
  }
  cout<<res<<endl;
}

void solve_org() {
  LL res=0;
  
  LL lb=-1;
  FORE(i,1,N) {
    LL l1=max(lb,A[i-1]),r1=A[i],l2=max(lb,B[i-1]),r2=B[i];
    LL l=max(l1,l2),r=min(r1,r2);
//    dump(i,l,r);
    res+=max(0LL,r-l+1);
    lb=r+1;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i+1]>>B[i+1];
  solve();
  
  return 0;
}
