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

// $ cp-batch ConnectedComponentOnAChessboard | diff ConnectedComponentOnAChessboard.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ConnectedComponentOnAChessboard.cpp && ./a.out

/*
 
 7/24/2019
 
 17:22-17:57 WA
 18:17 give up
 
 Show what case is invalid first 😡
 
 7/25/2019
 
 9:50-11:05 read editorials
 
 Find easier implementation.
 In this problem, we can take color `a` with smaller number.
 Take cells with color `b` between them. Adjust by taking cells with color `b` above/below taken `a`.
 
 https://codeforces.com/blog/entry/68642
 https://codeforces.com/blog/entry/68655
 
 */

const int H=1e9;
const int MAX_N=1e6;
int qs[MAX_N][2];
int N;
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
int par(int i, int j) { return (i+j)%2; }
void solve() {
  REP(k,N) {
    int cnt[2]={qs[k][0],qs[k][1]};
    int a=min(cnt[0],cnt[1]),b=max(cnt[0],cnt[1]);
    if(b>3*a+1) {
      println("NO");
      continue;
    }
//    dump(a,b);
    set<II> viz;
    int i,j;
    if(cnt[0]<=cnt[1]) i=1,j=1;
    else i=1,j=2;
    REP(k,a) viz.emplace(i,j+2*k),viz.emplace(i,j+2*k+1);
    b-=a;
    if(b>0) viz.emplace(i,j-1),--b;
//    dump(a,b);
    for(int k=0; k<a&&b>0; ++k) {
      viz.emplace(i+1,j+2*k),--b;
      if(b>0) viz.emplace(i-1,j+2*k),--b;
    }
//    dump(a,b);
    assert(b==0);

    println("YES");
    FORR(p,viz) println("%d %d", p.first+1,p.second+1);
  }
}
void solve_wrong() {
  REP(i,N) {
    set<II> viz;
    queue<II> Q;
    int cnt[2]={qs[i][0],qs[i][1]};
    
    auto go=[&](int i, int j) {
      Q.emplace(i,j);
      viz.emplace(i,j);
      int p=par(i,j);
      cnt[p]--;
      dump(i,j,p,cnt[0],cnt[1]);
      assert(cnt[p]>=0);
    };
    
    if(cnt[1]>cnt[0]) {
      go(H/2,H/2);
    } else {
      go(H/2+1,H/2);
    }
    while((cnt[0]>0||cnt[1]>0)&&SZ(Q)) {
      int i,j; tie(i,j)=Q.front(); Q.pop();
      int p=par(i,j);
      vector<II> nxt;
      REP(i,4) {
        auto m=moves[i];
        int ii=i+m.first,jj=j+m.second;
        if(ii<0||ii>=H||jj<0||jj>=H) continue;
        if(viz.count({ii,jj})) continue;
        nxt.emplace_back(ii,jj);
      }
      int taken=0;
      REP(i,SZ(nxt)) {
        auto pi=nxt[i];
        int ii=pi.first,jj=pi.second;
        if(cnt[p^1]>=cnt[p]&&cnt[p^1]>0) go(ii,jj);
        if(taken==0&&cnt[1^p]>0&&i==SZ(nxt)-1) go(ii,jj);
      }
    }
    if(cnt[0]>0||cnt[1]>0) {
      println("NO");
    } else {
      println("YES");
      FORR(p,viz) println("%d %d", p.first+1,p.second+1);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>qs[i][1]>>qs[i][0];
  solve();
  
  return 0;
}
