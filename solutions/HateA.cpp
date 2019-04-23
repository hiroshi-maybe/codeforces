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

// $ cp-batch HateA | diff HateA.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address HateA.cpp && ./a.out

/*
 
 4/20/2019
 
 11:09-11:23 AC
 
 https://cinnamo-coder.hatenablog.com/entry/2019/04/22/014951
 https://codeforces.com/blog/entry/66639
 
 Validate by # of non-'a' is easier.
 
 */

//const int MAX_N=1e6+1;
string T;

bool valid(string S, string T) {
  string s;
  int N=SZ(S);
  REP(i,N) if(S[i]!='a') s.push_back(S[i]);
  return s==T;
}
void nope() {
  cout<< ":("<<endl;
  exit(0);
}
void solve() {
  int N=SZ(T),cnt=0;
  REP(i,N) cnt+=T[i]!='a';
  if(cnt%2==1) nope();
  int cnta=N-cnt;
  string s=T.substr(0,cnt/2+cnta),ss=T.substr(cnt/2+cnta);
  string x; REP(i,SZ(s)) if(s[i]!='a') x.push_back(s[i]);
  if(x!=ss) nope();
  cout<<s<<endl;
}

void solve_org() {
  int N=SZ(T),cnt=0;
  VI cs(26,0);
  REP(i,N) if(T[i]!='a') cs[T[i]-'a']++,++cnt;
  string res;
  if(accumulate(ALL(cs),0)==0) {
    cout<<T<<endl;
    return;
  } else {
    VI cur(26,0);
    for(int i=N-1; i>=0; --i) {
      if(T[i]=='a') nope();
      cur[T[i]-'a']++;
      bool ok=true;
      REP(c,26) if(2*cur[c]!=cs[c]) {
        ok=false;
        break;
      }
      if(ok) {
        if(valid(T.substr(0,i),T.substr(i))) {
          cout<<T.substr(0,i)<<endl;
          return;
        } else nope();
      }
    }
  }
  nope();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>T;
  solve();
  
  return 0;
}
