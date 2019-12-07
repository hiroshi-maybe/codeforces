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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch BeautifulSequence | diff BeautifulSequence.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BeautifulSequence.cpp && ./a.out

/*
 
 12/5/2019
 
 7:27-8:33 WA
 8:40 fixed a bug
 21:30- another bug fix
 
 */

int A[4];

VV<int> res;
void dfs(int p, VI &cur, VV<int> &path) {
  if(accumulate(ALL(cur),0)==0) {
    res=path;
    return;
  }
  if(p<0||p>=4) {
    return;
  }
  if(cur[p]==0) {
    return;
  }
  dump(p);
  dumpc(cur);
  assert(cur[p]>0);
  VI nei={p-1,p+1};
  FORR(i,nei) {
    if(i<0||i>=4) continue;
    if(cur[i]>0) {
      int delta=min(cur[p],cur[i]);
      if(cur[i]==cur[p]) {
        // go throu (3)
        int next=i>p?(i+1):(i-1);
        path.push_back({p,i,next});
        cur[i]-=delta,cur[p]-=delta;
        dfs(next,cur,path);
        cur[i]+=delta,cur[p]+=delta;
        path.pop_back();
      } else if(cur[i]>cur[p]) {
        // go through
        int next=i>p?(i+1):(i-1);
        path.push_back({p,i});
        cur[i]-=delta,cur[p]-=delta;
        dfs(next,cur,path);
        cur[i]+=delta,cur[p]+=delta;
        path.pop_back();
      } else {
        // turn back
        int next=i>p?(p-1):(p+1);
        path.push_back({p,i,p});
        cur[i]-=delta,cur[p]-=delta+1;
        dfs(next,cur,path);
        cur[i]+=delta,cur[p]+=delta+1;
        path.pop_back();
      }
    }
  }
}
void solve() {
  if(accumulate(A,A+4,0)==1) {
    REP(i,4)if(A[i]) {
      println("YES");
      println("%d ", i);
      return;
    }
  }
  REP(i,4) {
    VI cur(A,A+4);
    VV<int> path;
    dfs(i,cur,path);
    if(SZ(res)) break;
  }
  if(res.empty()) {
    println("NO");
  } else {
    VI AA(A,A+4);
    VI ans;
    FORR(turn, res) {
      assert(SZ(turn));
      if(SZ(turn)==2) {
        int a=turn[0],b=turn[1];
        int x=min(A[a],A[b]);
        REP(_,x) ans.push_back(a),ans.push_back(b);
        A[a]-=x,A[b]-=x;
      } else {
        assert(SZ(turn)==3);
        int a=turn[0],b=turn[1];
        int x=min(A[a],A[b]);
        REP(_,x) ans.push_back(a),ans.push_back(b);
        if(turn[2]==a) ans.push_back(a);
        A[a]-=x,A[b]-=x;
        if(turn[2]==a) A[a]-=1;
      }
    }
    
    assert(accumulate(A,A+4,0)==0);
    println("YES");
    map<int,int> cnt;
    REP(i,SZ(ans)) printf("%d ", ans[i]),cnt[ans[i]]++;
    println("");
    REP(i,4) assert(cnt[i]==AA[i]);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  REP(i,4)cin>>A[i];
  solve();
  
  return 0;
}
