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

// $ cp-batch Nirvana | diff Nirvana.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Nirvana.cpp && ./a.out

/*
 
 5/13/2019
 
 19:37-19:48 WA
 19:57 WA
 20:11 AC
 
 https://cinnamo-coder.hatenablog.com/entry/2019/03/30/000000
 https://codeforces.com/blog/entry/66301
 
 Bug due to implementatin mistake 😞
 
 */

LL N;

LL solve() {
  LL res=1;
  string S=to_string(N);
  reverse(ALL(S));
  int L=SZ(S);
  REP(i,L) res=res*(S[i]-'0');
//  dump(N,res);

  REP(i,L-1) {
    LL a=1;
    REP(j,L) {
      if(j<=i) a*=9;
      else if(j==i+1) {
        int d=S[j]-'0';
        if(!(d==1&&j==L-1))a*=S[j]-'0'-1;
      } else a*=S[j]-'0';
    }
    SMAX(res,a);
    /*
    REP(j,i+1) a*=9;
    if(S[i+1]=='0') continue;
    LL b=(S[i+1]-'0'-1);
    if(i==L-2&&b==0)b=1;
    LL c=1;
    if(i<L-1) FOR(j,i+2,L) c*=S[j]-'0';
//    dump(i,L,a,b,c,a*b*c);
    SMAX(res,a*b*c);*/
  }
  return res;
}

void test() {
  FOR(n,1,100) {
    N=n;
    LL a=solve();
    LL b;
    FORE(i,1,n) {
      LL ans=1;
      string x=to_string(i);
      REP(i,SZ(x)) ans*=x[i]-'0';
      SMAX(b,ans);
    }
    if(a!=b) {
      dump(N,a,b);
    }
    assert(a==b);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>N;
  cout<<solve()<<endl;
  
  return 0;
}
