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

// $ cp-batch NezzarAndLuckyNumber | diff NezzarAndLuckyNumber.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NezzarAndLuckyNumber.cpp && ./a.out

/*

 1/28/2021

 6:39-7:11, 8:40-8:50 give up
 20:50-22:07 read editorials and got AC

 https://codeforces.com/blog/entry/87294
  -> dp
 https://codeforces.com/blog/entry/87294?#comment-754659
  -> adhoc

 https://twitter.com/hanseilimak/status/1355021740259241984

 https://twitter.com/kuuso1/status/1354836506125340674
 https://twitter.com/kzyKT_M/status/1354835551879192576
 https://twitter.com/prd_xxx/status/1354834846749605888

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,D;

bool f(LL a) {
  if(a>=10*D) {
    return true;
  }
  while(a>0) {
    a-=D;
    if(a>=0&&a%10==0) return true;
  }
  return false;
}
void solve() {
  REP(i,N) {
    LL a=A[i];
    cout<<(f(a)?"YES":"NO")<<endl;
  }
}

int cnt[10][10];
void solve_wrong() {
  REP(i,N) {
    LL a=A[i];
    bool res=false;
    while(a>0) {
      int d=a%10;
      int x=cnt[D][d];
      if(x>0&&a>=x*D) {
        res=true;
        break;
      }
      a/=10;
    }
    cout<<(res?"YES":"NO")<<endl;
  }
}

void prep() {
  FORE(d,1,9) {
    LL x=0; int y=0;
    while(true) {
      x+=d,++y;
      if(cnt[d][x%10]>0) break;
      cnt[d][x%10]=y;
    }
    dumpC(cnt[d],cnt[d]+10);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>D;
    REP(i,N) cin>>A[i];
    solve();
  }

  return 0;
}
