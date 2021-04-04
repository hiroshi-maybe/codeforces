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

// $ cp-batch BalanceTheBits | diff BalanceTheBits.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BalanceTheBits.cpp && ./a.out

/*

 4/3/2021

 8:24-9:50 give up

 23:25-23:35 read solution tweets and got AC
 24:35 Add proof in https://twitter.com/hanseilimak/status/1378598290061619201

 https://codeforces.com/blog/entry/89319
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.48x1wywqnwxu

 https://twitter.com/laycrs/status/1378390444959141891
 https://twitter.com/n_vip/status/1378390380400402433
 https://twitter.com/kiri8128/status/1378390061205516291

 */

string S;
int N;

bool ok(string s) {
  int bal=0;
  REP(i,N) {
    if(s[i]=='(') ++bal;
    else bal--;
    //dump(s,i,bal);
    if(bal<0) return false;
  }
  return bal==0;
}

void solve() {
  int cnt1=count(ALL(S),'1');
  if(S[0]=='0'||S[N-1]=='0'||cnt1%2) {
    cout<<"NO"<<endl;
    return;
  }

  string A,B;
  int curcnt1=0,par=0;
  REP(i,N) {
    if(S[i]=='1') {
      char c=(curcnt1<cnt1/2)?'(':')';
      A.push_back(c),B.push_back(c);
      curcnt1++;
    } else {
      char c=par==0?'(':')';
      A.push_back(c),B.push_back(c==')'?'(':')');
      par^=1;
    }
  }
  //dump(A,B);

  assert(ok(A)&&ok(B));
  if(ok(A)&&ok(B)) {
    cout<<"YES"<<endl;
    cout<<A<<endl;
    cout<<B<<endl;
  } else {
    cout<<"NO"<<endl;
  }
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
