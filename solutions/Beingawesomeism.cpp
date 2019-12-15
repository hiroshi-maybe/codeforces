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

// $ cp-batch Beingawesomeism | diff Beingawesomeism.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Beingawesomeism.cpp && ./a.out

/*
 
 12/14/2019
 
 22:41-23:51 WA
 23:54 AC
 
 */

const int MAX_N=60+1;
string A[MAX_N],AA[MAX_N];
int N,M;

//const int Inf=100;
int f() {
//  dump(N,M);
//  REP(i,N) dump(A[i]);

  {
    bool ok=true;
    REP(i,N) ok&=(A[i][0]=='A');
    if(ok) return 1;
  }
  
  {
    if(A[0][M-1]=='A'||A[0][0]=='A') return 2;
    REP(j,M) {
      bool ok=true;
      REP(i,N)ok&=A[i][j]=='A';
      if(ok) return 2;
    }
    
    int l=M,r=0;
    REP(j,M)if(A[0][j]=='P') SMIN(l,j),SMAX(r,j);
    if(l<=r) {
      REP(i,N) {
        bool ok=true;
        FORE(j,l,r) ok&=A[i][j]=='A';
        if(ok) return 2;
      }
    }
  }
  
  {
    REP(i,N)if(A[i][0]=='A') return 3;
  }
  
  return 4;
}

void rotate() {
  REP(i,N) AA[i]=A[i];
  REP(i,N) reverse(AA[i].begin(),AA[i].begin()+M);
  REP(i,N)REP(j,M) A[j][i]=AA[i][j];
  swap(N,M);
}

string solve() {
  map<char,int> cnt;
  REP(i,N)REP(j,M) cnt[A[i][j]]++;
  if(cnt['P']==0) return "0";
  if(cnt['A']==0) return "MORTAL";
  int res=4;
  REP(_,4) {
    SMIN(res,f());
//    dump(res);
    rotate();
  }

  return to_string(res);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  REP(i,MAX_N)A[i]=AA[i]=string(MAX_N,'.');
  
  int T; cin>>T;
  REP(i,T) {
    cin>>N>>M;
    REP(i,N) {
      string S; cin>>S;
      REP(j,M) A[i][j]=S[j];
    }
    cout<<solve()<<endl;
  }
  
  return 0;
}
