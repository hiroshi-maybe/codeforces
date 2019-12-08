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
 21:30-12:05 fixed bug and got AC
 
 https://codeforces.com/blog/entry/71995
 
 */

int A[4];

VV<int> res;
void dfs(int p, VI &cur, VV<int> &path) {
  dump(p);
  dumpc(cur);

  assert(p>=0&&p<4);
  if(cur[p]==0) return;
  cur[p]--;
  if(accumulate(ALL(cur),0)==0) {
    path.push_back({p});
    res=path;
    path.pop_back();
    cur[p]++;
    return;
  }
  VI nei={p-1,p+1};
  FORR(i,nei) {
    if(i<0||i>=4) continue;
    if(cur[i]>0) {
      int delta=min(cur[p],cur[i]);
      if(cur[i]>=cur[p]+1) {
        // go throuh
        path.push_back({p,i});
        dumpc(path.back());
        cur[i]-=delta,cur[p]-=delta;
        dfs(i,cur,path);
        cur[i]+=delta,cur[p]+=delta;
        path.pop_back();
      } else {
        // turn back
        path.push_back({p,i,p});
        dumpc(path.back());
        cur[i]-=delta,cur[p]-=delta-1;
        dfs(p,cur,path);
        cur[i]+=delta,cur[p]+=delta-1;
        path.pop_back();
      }
    }
  }
  cur[p]++;
}
void solve() {
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
      if(SZ(turn)==1) {
        int a=turn.front();
        ans.push_back(a),A[a]--;
      } else if(SZ(turn)==2) {
        int a=turn[0],b=turn[1];
        ans.push_back(a),A[a]--;
        int x=min(A[a],A[b]);
        REP(_,x) ans.push_back(b),ans.push_back(a);
        A[a]-=x,A[b]-=x;
      } else {
        assert(SZ(turn)==3);
        int a=turn[0],b=turn[1];
        int x=min(A[a]-1,A[b]);
        REP(_,x) ans.push_back(a),ans.push_back(b);
        A[a]-=x,A[b]-=x;
      }
    }
    dumpC(A,A+4);
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
