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

// $ cp-batch ChladniFigure | diff ChladniFigure.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ChladniFigure.cpp && ./a.out

/*
 
 7/26/2019
 
 13:50-14:45 pause
 
 7/29/2019
 
 13:00-13:34 give up (test case #7 does not make sense)
 14:30 read submit code and got AC
 
 Solution by string matching algorithm
  - https://codeforces.com/contest/1161/submission/53753800
 
 */

const int MAX_N=1e6+1;
int A[MAX_N][2];
int N,M;

vector<int> divisors(int N) {
  assert(N>=1);
  vector<int> res;
  for(int p=1; p*p<=N; ++p) if(N%p==0) {
    res.push_back(p);
    if(p!=N/p) res.push_back(N/p);
  }
  sort(res.begin(),res.end());
  return res;
}

II adjust(int a, int b) {
  if(a>b) swap(a,b);
  int l1=(N+b-a)%N,l2=N-l1,l=min(l1,l2);
  if((b+l)%N==a) swap(a,b);
  return {a,b};
}

bool solve() {
  map<II,int> X;
  REP(i,M) {
    auto p=adjust(A[i][0],A[i][1]);
//    dump(p);
    X[p]=SZ(X);
  }
//  FORR(kvp,X) dump(kvp.first.first,kvp.first.second);
  
  assert(SZ(X)==M);
  VI ds=divisors(N);
  assert(ds.back()==N);
  ds.pop_back();
//  dumpc(ds);
  FORR(d,ds) {
    VI viz(M,0);
    bool ok=true;
    FORR(kvp,X) {
      auto pp=kvp.first;
      int a=(pp.first+d)%N,b=(pp.second+d)%N;
      auto p=adjust(a,b);
      if(!X.count(p)||viz[X[p]]==1) {
        ok=false;
        break;
      }
      viz[X[p]]=1;
    }
    if(ok) {
      dump(d);
      return true;
    }
  }
  return false;
}

bool solve_wrong() {
  map<int,vector<int>> X;
  REP(i,M) {
    if(A[i][0]>A[i][1]) swap(A[i][0],A[i][1]);
    int l1=(N+A[i][1]-A[i][0])%N,l2=N-l1,l=min(l1,l2);
    int a,b;
    if((A[i][0]+l)%N==A[i][1]) a=A[i][0],b=A[i][1];
    else if((A[i][1]+l)%N==A[i][0]) a=A[i][1],b=A[i][0];
    else assert(false);
//    dump(l,a,b);
    if(l!=N/2) X[l].push_back(a);
  }
  VI ds=divisors(N);
  assert(ds.back()==N);
  ds.pop_back();
//  dumpc(ds);
  FORR(kvp,X) {
    VI B=kvp.second;
    sort(ALL(B));
//    dump(kvp.first);
//    dumpc(B);
    int L=SZ(B);
    map<int,int> inv; REP(i,L) inv[B[i]]=i;
    int s=lower_bound(ALL(ds),kvp.first)-ds.begin();
    VI viz(L,0);
    int cnt=0;
    while(cnt<L) {
      REP(i,L) if(!viz[i]) {
        int st=B[i];
        bool ok=false;
        FOR(j,s,SZ(ds)) {
          int d=ds[j];
          bool okok=true;
          if(st-d>=0) continue;
          for(int x=st; x<N; x+=d) {
            if(!inv.count(x)) {
              okok=false;
              break;
            }
          }
          if(okok) {
            for(int x=st; x<N; x+=d) viz[inv[x]]=1,++cnt;
            ok=true;
            break;
          }
        }
        if(!ok) return false;
      }
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,M)REP(j,2) cin>>A[i][j],A[i][j]--;
  cout<<(solve()?"Yes":"No")<<endl;
  
  return 0;
}
