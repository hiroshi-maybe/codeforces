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

// $ cp-batch BinaryPalindromes | diff BinaryPalindromes.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BinaryPalindromes.cpp && ./a.out

/*
 
 10/24/2019
 
 8:14-9:03 AC
 
 https://codeforces.com/blog/entry/70860
 
 */

const int MAX_N=50+1;
string S[MAX_N];
int N;

void solve() {
  VI cnt(2,0),cntlen(2,0);
  REP(i,N){
    cntlen[SZ(S[i])%2]++;
    REP(j,SZ(S[i])) cnt[S[i][j]-'0']++;
  }
  int res=N;
  if(cntlen[1]==0) {
    if(cnt[0]%2==1) res=N-1;
  } else if(cntlen[1]%2==0) {
    // noop
  } else {
    // noop
  }
  cout<<res<<endl;
}

void solve_wrong() {
  VI cnt(2,0);
  REP(i,N)REP(j,SZ(S[i])) cnt[S[i][j]-'0']++;
  int k=0,res=0;
  REP(i,N) {
    int L=SZ(S[i]);
    dump(i,cnt[0],cnt[1],k,L);

    int a=min(k>=2?0:cnt[k],L);
    if(a>0)cnt[k]-=a;
    if(k<2&&cnt[k]==0) ++k;
      int b=min(k>=2?0:cnt[k],L-a);
      if(b>0)cnt[k]-=b;
      if(k<2&&cnt[k]==0) ++k;
    dump(i,a,b);
    assert(a+b==L);
    if(L%2==0&&a%2==0&&b%2==0) ++res;
    else if(L%2==1&&((a%2==0&&b%2==1)||(a%2==1&&b%2==0))) ++res;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(i,T) {
    cin>>N;
    REP(i,N) cin>>S[i];
    solve();
  }
  
  return 0;
}
