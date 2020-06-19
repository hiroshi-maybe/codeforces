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

// $ cp-batch EvenPicture | diff EvenPicture.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EvenPicture.cpp && ./a.out

/*

 6/18/2020

 8:30-9:25 AC

 https://twitter.com/hanseilimak/status/1274084099813027840
 https://codeforces.com/blog/entry/79027

 https://scrapbox.io/snuke/Codeforces_Global_Round_8
 https://twitter.com/laycrs/status/1273667288701390848
 https://twitter.com/satanic0258/status/1273670859681525760?s=20

 */

int N;

void solve() {
  set<II> viz;
  vector<II> res,Q;

  auto add=[&](int x, int y) {
    if(viz.count({x,y})) return;
    res.emplace_back(x,y);
    viz.emplace(x,y);
  };
  add(0,0);

  Q.emplace_back(0,0);
  REP(i,N-1) {
    add(2*i+1,0),add(2*i+2,0);
    Q.emplace_back(2*i+2,0);
  }

  auto paint=[&](int x, int y, int lx, int rx, int ly, int ry) {
    FORE(dx,lx,rx)FORE(dy,ly,ry) {
      //if(x+dx==x&&y+dy==y) continue;
      if(dx==(lx+rx)/2&&dy==(ly+ry)/2) continue;
      add(x+dx,y+dy);
    }
  };
  assert(SZ(Q)==N);
  REP(i,N) {
    auto p=Q[i];
    int x=p.first,y=p.second;
    if(i==0) paint(x,y,-2,0,0,2); // top left
    if(i%2==1) paint(x,y,0,2,0,2); // top
    if(i%2==0) paint(x,y,0,2,-2,0); // bottom
  }

/*
  VV<int> B(2*N+10,VI(10,0));
  FORR(p,res) {
    B.at(p.first+4).at(p.second+4)=1;
  }
  REP(i,SZ(B)) {
    REP(j,SZ(B[i])) {
      cout<<B.at(i).at(j);
    }
    cout<<endl;
  }*/

  cout<<SZ(res)<<endl;
  REP(i,SZ(res)) cout<<res[i].first<<" "<<res[i].second<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  solve();

  return 0;
}
