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

// $ cp-batch LostNumbers | diff LostNumbers.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LostNumbers.cpp && ./a.out

/*
 
 5/15/2019
 
 7:44-7:59 system test failed
 
 My original solution fails for {23 4 8 16 42 15}
 gcd(Q[0..3]) gives common divisor of A[1..3], too
 
 5/20/2019
 
 8:50-9:10 read editorial and got AC
 
 https://codeforces.com/blog/entry/67058
 https://cinnamo-coder.hatenablog.com/entry/2019/05/16/132831
 
 If four products are given as input, it's easy to verify by brute-force.
 Don't be confused by interactive problem.
 
 */

int ask(int i, int j) {
  cout<<"? "<<i+1<<" "<<j+1<<endl;
  int res; cin>>res;
  return res;
}
int gcd(int a, int b) { return b==0?a:gcd(b,a%b); }
void solve() {
  VI A={4,8,15,16,23,42};
  VI Q(4);
  REP(i,4) Q[i]=ask(0,i+1);
  do {
    bool ok=true;
    REP(i,4) ok&=Q[i]==A[0]*A[i+1];
    if(ok) {
      cout<<"! ";
      REP(i,6) {
        cout<<A[i];
        if(i==5) cout<<endl;
        else cout<<" ";
      }
      return;
    }
  } while(next_permutation(ALL(A)));
}

void solve_wrong() {
  VI AA={4,8,15,16,23,42};
  VI Q(4);
  REP(i,4) Q[i]=ask(0,i+1);
  int g=Q[0];
  REP(i,4) g=gcd(g,Q[i]);
  VI A(5); A[0]=g;
  if(find(ALL(AA),A[0])==AA.end()) A[0]=g=g/2;
  REP(i,4) A[i+1]=Q[i]/g;
  SETI S(ALL(A));
  FORR(x,AA) if(!S.count(x)) {
    A.push_back(x);
    break;
  }
  cout<<"! ";
  REP(i,6) {
    cout<<A[i];
    if(i==5) cout<<endl;
    else cout<<" ";
  }
  
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  solve();
  
  return 0;
}
