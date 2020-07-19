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

// $ cp-batch AcaciusAndString | diff AcaciusAndString.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AcaciusAndString.cpp && ./a.out

/*

 7/19/2020

 2:00-2:40 WA
 3:00 AC

 11:30-11:34 OMG. O(N^2) works. Add simpler O(N^2) solution.

 https://twitter.com/hanseilimak/status/1284920113410400256
 https://codeforces.com/blog/entry/80216

 */

string S;
int N;

bool found(string &s, int i) {
  string x="abacaba";
  if(i>SZ(s)-7) return false;
  bool ok=true;
  REP(j,7) ok&=s[i+j]==x[j];
  return ok;
}
int check(string &S) {
  int cnt=0;
  REP(i,N) cnt+=found(S,i);
  return cnt;
}

void solve() {
  string T="abacaba";
  int cnt=check(S);
  if(cnt>1) {
    cout<<"No"<<endl;
    return;
  }

  REP(i,N) {
    string s=S;
    bool ok=true;
    REP(j,7) {
      if(s[i+j]!='?'&&s[i+j]!=T[j]) ok=false;
      if(s[i+j]=='?') s[i+j]=T[j];
    }
    if(check(s)==1) {
      REP(i,N) if(s[i]=='?') s[i]='z';
      cout<<"Yes"<<endl;
      cout<<s<<endl;
      return;
    }
  }
  cout<<"No"<<endl;
}

void solve_org() {
  string s="abacaba";
  VI ps0,ps1;
  //dump(N,S,N-7);
  REP(i,N-6) {
    bool ok=true;
    int cnt=0;
    REP(j,7) {
      if(S[i+j]!='?'&&S[i+j]!=s[j]) {
        ok=false;
      }
      if(S[i+j]=='?') cnt++;
    }
    //dump(i,ok);
    if(ok) {
      (cnt==0?ps0:ps1).push_back(i);
    }
  }

  //dumpc(ps0);
  //dumpc(ps1);

  bool res=true;
  if(SZ(ps0)>1) res=false;
  if(res==false) {
    cout<<"No"<<endl;
    return;
  }

  if(SZ(ps0)==1) {
    REP(i,N) if(S[i]=='?') S[i]='z';
    assert(check(S)==1);
    cout<<"Yes"<<endl;
    cout<<S<<endl;
    return;
  }

  string t=S;
  int p=-1;
  set<int> ng;
  FORR(i,ps1) if(!ng.count(i)) {
    REP(j,7) t[i+j]=s[j];
    if((found(t,i+4)||found(t,i+6))) {
      if(S[i]!='?'&&S[i+1]!='?'&&S[i+2]!='?'&&S[i+3]!='?'&&found(t,i+4)) ng.emplace(i+4);
      continue;
    }
    p=i;
    break;
  }

  if(p==-1) {
    cout<<"No"<<endl;
    return;
  }

  REP(j,7) S[p+j]=s[j];
  REP(i,N) if(S[i]=='?') S[i]='z';
  assert(check(S)==1);
  cout<<"Yes"<<endl;
  cout<<S<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>S;
    solve();
  }

  return 0;
}
