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

// $ cp-batch MagicShip | diff MagicShip.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MagicShip.cpp && ./a.out

/*
 
 2/20/2019
 
 16:07-17:52 WA on #5
 18:11 WA on #7
 18:13 AC
 
 https://ferin-tech.hatenablog.com/entry/2019/02/19/Educational_Codeforces_Round_60_C._Magic_Ship
 https://codeforces.com/blog/entry/65365
 
 I did not clearly understand monotonous property of reachable area.
 Binary search is very typical to solve robot walk 😡
 Show that if cell (r,c) is reachable at `x` step, (r,c) is reachable at `x+𝛼` step too.
 
 Look at reachable area expanded in each step.
 When reachable area includes target position for the first time, it's the answer.
 
 In the worst case, wind makes the ship further from target position.
 However we can stay in the original position if ship moves against wind direction.
 Thus reachable positions keep expanding (never shrink).
 
 */

int N;
string S;
LL X,Y;

// grid move (clock wise order)
vector<pair<int,int>> moves = { {1,0}/*R*/,{0,-1}/*D*/,{-1,0}/*L*/,{0,1}/*U*/ };
string dir="RDLU";
map<char,II> ms;

const int MAX_N=1e5+1;
LL cumx[MAX_N],cumy[MAX_N];
void solve() {
  REP(i,4) ms[dir[i]]=moves[i];
  LL dx=0,dy=0;
  REP(i,N) {
    dx+=ms[S[i]].first,dy+=ms[S[i]].second;
    cumx[i+1]=dx,cumy[i+1]=dy;
  }
  
  auto ok=[&](LL s) -> bool {
    LL c=s/N,cc=s%N;
    LL x=cumx[N]*c+cumx[cc],y=cumy[N]*c+cumy[cc];
    return abs(x-X)+abs(y-Y)<=s;
  };
  
  LL good=1e15,bad=-1;
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2;
    (ok(m)?good:bad)=m;
  }
  if(!ok(good)) {
    println("-1");
    return;
  }
  println("%lld", good);
}

LL dx,dy;
bool ok(LL turn) {
  LL x=dx*(turn-1),y=dy*(turn-1),t=(turn-1)*N;
  if(abs(x-X)+abs(y-Y)<=t) return true;
  REP(i,N) {
    char c=S[i];
    x+=ms[c].first,y+=ms[c].second,++t;
    /*
    if(turn==2) {
      LL a=abs(x-X)+abs(y-Y);
      dump(t,x,y,a,t,a<=t);
    }*/
    if(abs(x-X)+abs(y-Y)<=t) return true;
  }
  return false;
}

void solve_org() {
  LL x=0,y=0;
  REP(i,4) ms[dir[i]]=moves[i];
  
  REP(i,N) {
    char c=S[i];
    x+=ms[c].first,y+=ms[c].second;
  }
  dx=x,dy=y;
  const LL Inf=1e10;
  LL good=Inf,bad=0;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    (ok(mid)?good:bad)=mid;
  }
  if(good>=Inf) {
    println("-1");
    return;
  }
//  assert(good<Inf);
  LL base=good-1;
  LL t=base*N;
//  dump(delta,base,t);
  x=base*x,y=base*y;
  int i=0;
  while(true) {
    if(abs(x-X)+abs(y-Y)<=t) {
      println("%lld", t);
      return;
    }
    char c=S[i];
    x+=ms[c].first,y+=ms[c].second;
    i=(i+1)%N;
    ++t;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  string x(100000,'D');
//  cout<<x<<endl;
  
  LL x1,y1,x2,y2;
  cin>>x1>>y1>>x2>>y2>>N>>S;
  X=x2-x1,Y=y2-y1;
  solve();
  
  return 0;
}
