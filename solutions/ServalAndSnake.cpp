#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef tuple<int,int,int,int> IIII;
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

// $ cp-batch ServalAndSnake | diff ServalAndSnake.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ServalAndSnake.cpp && ./a.out

/*
 
 4/16/2019
 
 17:42-18:55, 21:30-22:15 give up
 22:15-23:15 read editorial and got AC
 
 https://codeforces.com/blog/entry/66539
 https://cinnamo-coder.hatenablog.com/entry/2019/04/14/183311
 https://twitter.com/satanic0258/status/1117099725239382017
 https://twitter.com/yamerarenaku/status/1117097659313954816
 
 The idea to check each column or row was correct.
 However sticking to divide and conquer was shit 😡.
 If brute-force is plausible, try more various way 😡😡.
 
 We can have maximum 2000 queries.
 Let's check each column one by one and divide into two cases (max. 999 queries).
 
 1) two columns with odd query result
 
 Head and tail are in separated columns
 Binary search by q(i1,j,mid,j+1) and find a row of odd query result (10x2 queries)
 
 2) all columns return even query result
 
 Head and tail are in the same column. However it's unknown.
 Query each row by q(i1,0,i1+1,N) to know which row has head or tail. (max. 999 queries)
 Head and tail exists in the same column. They are connected.
 That means there should be two rows with odd query result.
 In either row, we can binary search by q(r,j1,r+1,N) and find the column with head or tail. (max. 10 queries)
 
 Summary:
  - I had only idea starting with binary search. However we can query more. I should have digged brute-force first.
  - Brute-force first in even interactive problem. Optimize it by smart idea.
 
 */

int N;
vector<II> res;
void answer(int i1, int j1, int i2, int j2) {
  cout<<"! "<<i1+1<<" "<<j1+1<<" "<<i2+1<<" "<<j2+1<<endl;
  int res; cin>>res;
  exit(0);
}
int ask(IIII rec) {
  int i1,j1,i2,j2; tie(i1,j1,i2,j2)=rec;
  cout<<"? "<<j1+1<<" "<<i1+1<<" "<<j2<<" "<<i2<<endl;
  int res; cin>>res;
  if(res==-1) exit(0);
  return res;
}

void searchrow(int j) {
  int l=0,r=N;
  while(r-l>1) {
    int m=(l+r)/2;
    int x=ask({l,j,m,j+1});
    (x%2==1?r:l)=m;
  }
  res.emplace_back(l,j);
}
int searchcol(int i) {
  int l=0,r=N;
  while(r-l>1) {
    int m=(l+r)/2;
    int x=ask({i,l,i+1,m});
    (x%2==1?r:l)=m;
  }
  res.emplace_back(i,l);
  return l;
}

void solve() {
  VI cs;
  REP(j,N-1) {
    int x=ask({0,j,N,j+1});
    if(x%2==1) cs.push_back(j);
  }
  if(SZ(cs)==1) cs.push_back(N-1);
  assert(SZ(cs)==0||SZ(cs)==2);
  if(SZ(cs)==2) {
    searchrow(cs[0]),searchrow(cs[1]);
  } else {
    VI rs;
    REP(i,N-1) {
      int x=ask({i,0,i+1,N});
      if(x%2==1) rs.push_back(i);
    }
    if(SZ(rs)==1) rs.push_back(N-1);
    assert(SZ(rs)==2);
    int j=searchcol(rs[0]);
    res.emplace_back(rs[1],j);
  }
  assert(SZ(res)==2);
  answer(res[0].second,res[0].first,res[1].second,res[1].first);
}

/*
void addres(int i1, int j1) {
  res.emplace_back(i1,j1);
  if(SZ(res)==2) answer(res[0].second,res[0].first,res[1].second,res[1].first);
}
bool onecell(IIII rec) {
  int i1,j1,i2,j2; tie(i1,j1,i2,j2)=rec;
  return j2-j1<=1&&i2-i1<=1;
}

void f(IIII rec) {
  int i1,j1,i2,j2; tie(i1,j1,i2,j2)=rec;
  dump(i1,j1,i2,j2);
  if(onecell(rec)) return;
  IIII r1,r2;
  if(j2-j1<=1) {
    // vert
    r1={i1,j1,(i1+i2)/2,j2},r2={(j1+j2)/2,j1,i2,j2};
  } else {
    // horz
    r1={i1,j1,i2,(j1+j2)/2},r2={i1,(j1+j2)/2,i2,j2};
  }
  int x=ask(r1);
  if(onecell(r1)) {
    if(x==1) addres(get<0>(r1),get<1>(r1));
  } else if(x==0) {
    f(r2);
    return;
  }
  int y=ask(r2);
  if(onecell(r2)) {
    if(y==1) addres(get<0>(r2),get<1>(r2));
    return;
  } else if(y==0) {
    f(r1);
    return;
  }
  f(r1),f(r2);
}
void 💩() {
  FOR(i2,1,N) {
    int res=ask({0,0,i2,N});
    if(res>0) f({0,0,i2,N}),f({i2,0,N,N});
  }
  FOR(j2,1,N) {
    int res=ask({0,0,N,j2});
    if(res>0) f({0,0,N,j2}),f({0,j2,N,N});
  }
  assert(false);
}*/

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  solve();
  
  return 0;
}
