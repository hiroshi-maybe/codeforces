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

// $ cp-batch ServalAndParenthesisSequence | diff ServalAndParenthesisSequence.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ServalAndParenthesisSequence.cpp && ./a.out

/*
 
 4/13/2019
 
 7:54-8:04 WA
 8:13 WA
 8:18 pause
 8:56-9:08 give up
 
 4/15/2019
 
 22:00-22:40 read editorials
 
 4/16/2019
 
 9:40-10:30 read editorial
 
 https://codeforces.com/blog/entry/66539
 https://cinnamo-coder.hatenablog.com/entry/2019/04/14/183311
 http://perogram.hateblo.jp/entry/cf_1153
 https://www.hamayanhamayan.com/entry/2019/04/14/103201
 
 We can greedily put '(' as long as occurence of '(' <=N/2.
 If this violates balance, there exists `i` s.t. B[i]<0.
 That can be verified by checking B[i].

 Key:
  - balanced => total # of '(' is N/2 (necessary condition)
 
 */

//const int MAX_N=1e6+1;
int N;
string SS;

void nope() {
  cout<<":("<<endl;
  exit(0);
}
void solve() {
  string S=SS;
  if(N%2==1) nope();
  if(S[0]==')'||S[N-1]=='(') nope();
  int cnt=0;
  REP(i,N) cnt+=S[i]=='(';
  int b=0;
  REP(i,N) {
    if(S[i]=='?') {
      if(cnt<N/2) S[i]='(',++cnt;
      else S[i]=')';
    }
    if(S[i]=='(') ++b;
    else if(S[i]==')') --b;
    if(i!=N-1&&b<=0) nope();
  }
  if(b!=0) nope();
  cout<<S<<endl;
}

void solve_wrong() {
  string S=SS;
  int b=0;
  REP(i,N) {
    if(S[i]=='?') {
      if(i==N-1||b>0) S[i]=')';
      else S[i]='(';
    }
    if(S[i]=='(') {
      ++b;
    } else if(S[i]==')') {
      --b;
    }
    if(b<0) nope();
  }
  if(b!=0) nope();
  
  b=0;
  VI X;
  REP(i,N) {
    if(S[i]=='(') {
      ++b;
    } else if(S[i]==')') {
      --b;
    }
    if(i!=N-1&&b==0) X.push_back(i);
  }
  dump(S);
  dumpc(X);
  REP(i,SZ(X)) {
    int l=X[i],r=X[i]+1;
    int L=i==0?0:X[i-1],R=i==SZ(X)-1?N:X[i+1];
    dump(l,r);
    while(l>=L&&SS[l]!='?') --l;
    while(r<=R&&SS[r]!='?') ++r;
    dump(l,r);
    if(SS[l]=='?'&&S[l]==')'&&SS[r]=='?'&&S[r]=='(') swap(S[l],S[r]),SS[l]='#',SS[r]='#';
    else nope();
  }
  cout<<S<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>SS;
  solve();
  
  return 0;
}
