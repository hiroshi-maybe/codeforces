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

// $ cp-batch EugeneAndAnArray | diff EugeneAndAnArray.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EugeneAndAnArray.cpp && ./a.out

/*
 
 4/8/2020
 
 7:48-8:52 WA
 9:16 fix overflow bug and AC
 
 Index is tricky. Using a closed interval seems to be straighforward.
 Also don't miss overflow bug.
 https://codeforces.com/contest/1333/submission/75858522
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

LL solve() {
  map<LL,int> lpos;
  int lmax=0;
  LL sum=0,res=0;
  lpos[0]=0;
  REP(i,N) {
    sum+=A[i];
    if(lpos.count(sum)) {
      SMAX(lmax,lpos[sum]+1);
//      dump(i,lpos[sum],lmax);
    }
//    dump(i,A[i],lmax,i-lmax+1);
    res+=i-lmax+1;
    lpos[sum]=i+1;
  }
  
  return res;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  N=genRandNum(1,100);
  VI AA=genRandSeq(N,0,5);
  REP(i,N) AA[i]=genRandNum(0,2)==0?AA[i]:-AA[i];
//  VI AA={1,2,-3};
  REP(i,N) A[i]=AA[i];
  LL exp=0;

  REP(j,N)REPE(i,j) {
    bool ok=true;
    FORE(s,i,j) {
      LL sum=0;
      FORE(k,s,j) {
        sum+=AA[k];
        if(sum==0) {
          ok=false;
          break;
        }
      }
    }
    if(ok) {
      exp+=1;
    }
  }
  
  dumpc(AA);
  LL act=solve();
  dump(exp,act);
  if(exp!=act) {
    dump(exp,act);
  }
  assert(act==exp);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;
  
  return 0;
}
