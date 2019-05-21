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

// $ cp-batch BicoloredRBS | diff BicoloredRBS.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BicoloredRBS.cpp && ./a.out

/*
 
 5/15/2019
 
 8:09-8:34 WA
 9:18 AC
 
 I quickly figured out that greedy works though, my wrong solution was not considering a case such that there are multiple positions with maximum depth 😞
 
 https://codeforces.com/blog/entry/67058
 https://cinnamo-coder.hatenablog.com/entry/2019/05/16/132831
 
 It's nice to construct by parity
 
 */

const int MAX_N=1e6+1;
int N;
string S;
int res[MAX_N];

void solve() {
  int bal=0;
  REP(i,N) {
    if(S[i]=='(') {
      ++bal;
      res[i]=bal%2;
    } else {
      res[i]=bal%2;
      --bal;
    }
  }
  REP(i,N) printf("%d",res[i]);
  println("");
}

int dep(string &S) {
  int N=SZ(S);
  int d=0,res=0;
  REP(i,N) {
    if(S[i]=='(') ++d;
    else --d;
//        if(d<0) dump(S);
    assert(d>=0);
    SMAX(res,d);
  }
  assert(d==0);
  return res;
}

void solve_org() {
  int d=0,maxd=dep(S),D=(maxd+1)/2;
//  dump(maxd,D);
  REP(i,N) {
    if(d<D&&S[i]=='(') ++d;
    else if(d>0&&d<=D&&S[i]==')') --d;
    else res[i]=1;
  }
  REP(i,N) printf("%d",res[i]);
  println("");
  
  vector<string> X(2);
  REP(i,N) X[res[i]].push_back(S[i]);
  int d1=dep(X[0]),d2=dep(X[1]);
//  dump(d1,d2);
  assert(max(d1,d2)==D);
}

bool ok(int D) {
  int d=0; bool reached=false;
  ZERO(res);
  string T;
  REP(i,N) {
    if(!reached) {
      if(S[i]=='(') {
        ++d;
        if(d==D+1) {
          reached=true;
          T.push_back(S[i]);
          res[i]=1;
          --d;
        }
      } else {
        --d;
      }
    } else {
      if(d>0&&S[i]==')') --d;
      else {
        T.push_back(S[i]);
        res[i]=1;
      }
    }
  }
  if(!reached) return true;
//  dump(D,T);
  return (dep(T)<=D);
}
void solve_wrong() {
  int good=1e7,bad=0;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    bool a=ok(m);
    (a?good:bad)=m;
  }
//  dump(good);
  assert(ok(good));
  REP(i,N) printf("%d",res[i]);
  println("");
  
  vector<string> X(2);
  REP(i,N) X[res[i]].push_back(S[i]);
  int d1=dep(X[0]),d2=dep(X[1]);
  assert(max(d1,d2)==good);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>S;
  solve();
  
  return 0;
}
