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

// $ cp-batch VasyaAndArray | diff VasyaAndArray.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address VasyaAndArray.cpp && ./a.out

/*
 
 6/30/2019
 
 8:03-9:19 System test failed
 
 NO NEED of cooridnate expansion
 
 7/2/2019
 
 14:38-15:38 read editorial and got AC
 
 https://codeforces.com/blog/entry/68111
 
 https://codeforces.com/contest/1187/submission/56317181
 Very smart construction by @kmjp.
 
 Defferentiation is defined between two consecutive values.
 For condition [l,r], we need only [l,r) range. Thus no coordinate expansion is needed.
 If we verify all increasing condition, we can check if there is a spot where decrease happens.
 If that's never possible, result is "NO".
 Once we figure out that decrease can happen, we can do decrease as long as it's not increasing range (constructive).
 Also we can put 1e9/2 by default so that we don't need to be worried about violation of A[i]<1 condition.
 
 */

const int MAX_N=1e3+1;
int N,M;
//const int Inf=1e8;
int T[MAX_N],L[MAX_N],R[MAX_N];
vector<II> X;
int S[2*MAX_N];
void solve() {
  REP(i,M) {
    int t=T[i],l=L[i],r=R[i];
    --l,--r;
    if(t==1) FOR(j,l,r) S[j]=1;
  }
  REP(i,M) {
    int t=T[i],l=L[i],r=R[i];
    --l,--r;
    if(t==0) {
      int ok=false;
      FOR(j,l,r) if(S[j]!=1) {
        S[j]=-1;
        ok=true;
        break;
      }
      if(!ok) {
        cout<<"NO"<<endl;
        return;
      }
    }
  }
//  dumpC(S,S+N);
  VI res(N,100000);
  REP(i,N-1) {
    if(S[i]==1) res[i+1]=res[i]+1;
    else if(S[i]==-1) res[i+1]=res[i]-1;
  }
  println("YES");
  REP(i,N) printf("%d ", res[i]);
  println("");
}

void solve_wrong() {
  X.clear();
  REP(i,M) {
    int t=T[i],l=L[i],r=R[i];
    --l,--r;
    if(t==1) {
      FORE(i,2*l,2*r) S[i]=1;
    } else {
      X.emplace_back(l,r);
    }
  }
  
  vector<int> res(N,0);
  int cur=1;
  REP(i,N) {
    if(S[2*i]) {
      if(i==0||S[2*i-1]==0) cur=1;
      else cur++;
      res[i]=cur;
    }
  }
  dumpC(S,S+2*N);
  FORR(p,X) {
    int l,r; tie(l,r)=p;
    int cnt=count(S+2*l+1,S+2*r,0);
    dump(l,r,cnt);
    if(cnt==0) {
      cout<<"NO"<<endl;
      return;
    }
    FOR(i,l,r) if(res[i]>res[i+1]) {
      continue;
    }
    for(int i=2*l+1; i<=2*r; i+=2) {
      if(S[i]==0) {
        dumpc(res);
        dump(i,S[i]);
        assert(i%2==1);
        int ll=(i-1)/2,rr=(i+1)/2;
        if(S[i-1]&&S[i+1]) {
          assert(res[ll]>res[rr]);
          break;
        }
        if(S[i+1]) res[ll]=res[rr]+1;
        else res[rr]=res[ll]-1;
        break;
      }
    }
  }
  dumpc(res);
  int b=*min_element(ALL(res));
  if(b<1) {
    REP(i,N)res[i]+=-b+1;
  }
  FORR(p,X) {
    bool ok=false;
    FOR(i,p.first,p.second) if(res[i]>res[i+1]) ok=true;
    assert(ok);
  }
  println("YES");
  REP(i,N) printf("%d ", res[i]);
  println("");
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
  N=10;
  M=3;
  cerr<<N<<" "<<M<<endl;
  REP(i,M) {
    T[i]=genRandNum(0,2);
    L[i]=genRandNum(1,N);
    R[i]=genRandNum(L[i]+1,N+1);
    cerr<<T[i]<<" "<<L[i]<<" "<<R[i]<<endl;
  }
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N>>M;
  REP(i,M) {
    cin>>T[i]>>L[i]>>R[i];
  }
  solve();
  
  return 0;
}
