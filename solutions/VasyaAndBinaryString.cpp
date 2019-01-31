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

// $ cp-batch VasyaAndBinaryString | diff VasyaAndBinaryString.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address VasyaAndBinaryString.cpp && ./a.out

/*
 
 1/30/2019
 
 14:10-14:40, 15:30-17:00 give up
 
 17:00-17:45, 20:00-20:35 read editorials and got AC
 
 https://codeforces.com/blog/entry/64833
 https://codeforces.com/blog/entry/64847
 
 If we are going to "merge" intervals in 1-d array, there is a structure of stack behind.
 
 Key:
  - Remember only length of prefix
  - Fix interval to process first. Continue successors keeping prefix
 
 */

const int MAX_N=1e2+1;
LL A[MAX_N];
int N;
string S;

LL memo1[MAX_N][MAX_N];

LL f_wrong(int l, int r) {
  LL &res=memo1[l][r];
  if(res>=0) return res;
  if(r-l<=0) return res=0;
  res=0;
  FOR(i,l,r) {
    char c=S[i];
    FORE(len,1,r-l) {
      if(S[i+len-1]!=c) break;
      SMAX(res,A[len-1]+f_wrong(l,i)+f_wrong(i+len,r));
    }
  }
  return res;
}

LL f_wrong2(int l, int r) {
  LL &res=memo1[l][r];
  if(res>=0) return res;
  if(r-l<=0) return res=0;
  res=0;
  LL sumb=0; int len1=0,len2=0;
  char c0=S[l];
  FOR(i,l,r) {
    char c=S[i];
    if(c==c0) {
      sumb+=f_wrong2(i-len2,i);
      len2=0;
      len1++;
      SMAX(res,A[len1]+sumb+f_wrong2(i+1,r));
    } else {
      len2+=1;
    }
  }
  if(len2) {
    sumb+=f_wrong2(r-len2,r);
    SMAX(res,A[len1]+sumb);
  }
  dump(l,r,len1,len2,sumb,res);
  return res;
}

LL memo[MAX_N][MAX_N][MAX_N];
LL f(int l, int r, int pref) {
  LL &res=memo[l][r][pref];
  if(res>=0) return res;
  if(r-l<=0) return res=0;
  res=A[pref+1]+f(l+1,r,0);
  FOR(i,l+1,r) if(S[i]==S[l]) {
    SMAX(res,f(i,r,pref+1)+f(l+1,i,0));
  }
//  dump(l,r,pref,res);
  return res;
}

void solve() {
  MINUS(memo);
  cout<<f(0,N,0)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>S;
  A[0]=0;
  REP(i,N) cin>>A[i+1];
  solve();
  
  return 0;
}
