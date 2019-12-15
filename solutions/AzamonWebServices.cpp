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

// $ cp-batch AzamonWebServices | diff AzamonWebServices.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AzamonWebServices.cpp && ./a.out

/*
 
 12/14/2019
 
 21:09-21:23 WA
 22:08 AC
 
 12:00-15:00 read solutions of other contestants
 
 https://twitter.com/hanseilimak/status/1206310136978915328
 
 Brute-force swapping alphabet greedily
 https://codeforces.com/contest/1281/submission/66904151
 
 Complexity of this solution is unsure. Isn't this O(N^3)? Or there is tighter analysis?
 https://codeforces.com/contest/1281/submission/66903686
 
 */

string S,C;

string solve() {
  if(S<C) return S;
  int N=SZ(S);
  VI posr(26,-1),posl(26,-1);
  REP(i,N) {
    int c=S[i]-'A';
    posr[c]=i;
  }
  for(int i=N-1; i>=0; --i) {
    int c=S[i]-'A';
    posl[c]=i;
  }
  REP(c1,26)if(posl[c1]>=0) {
    int i=posl[c1];
    REP(c,c1) if(posr[c]!=-1&&posr[c]>i) {
      int j=posr[c];
      swap(S[i],S[j]);
      if(S<C) return S;
      swap(S[i],S[j]);
    }
  }
  return "---";
}

string solve_org() {
  if(S<C) return S;
  int N=SZ(S),M=SZ(C);
  vector<deque<int>> cnt(26,deque<int>());
  for(int i=N-1; i>=0; --i) cnt[S[i]-'A'].push_back(i);
  REP(i,min(N,M)) {
    assert(cnt[S[i]-'A'].back()==i);
    cnt[S[i]-'A'].pop_back();
    if(S[i]!=C[i]) {
      if(S[i]<C[i]) return S;
      FOR(j,i+1,N)if(S[j]<=C[i]) {
        swap(S[i],S[j]);
        if(S<C) return S;
        swap(S[i],S[j]);
      }
      return "---";
    } else {
      int c=C[i]-'A';
      REP(cc,c) if(SZ(cnt[cc])) {
        int pos=cnt[cc].back(); cnt[cc].pop_back();
        swap(S[i],S[pos]);
        assert(S<C);
        return S;
      }
    }
  }
  return N<M?S:"---";
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
  int N=genRandNum(1,10),M=genRandNum(1,10);
  VI AA=genRandSeq(N,0,26),BB=genRandSeq(M,0,26);
  string A(N,'.'),B(M,'.');
  REP(i,N)A[i]='A'+AA[i];
  REP(i,M)B[i]='A'+BB[i];
  string exp="---";
  REP(j,N)REPE(i,j) {
    swap(A[i],A[j]);
    if(A<B) {
      exp=A;
      swap(A[i],A[j]);
      goto done;
    }
    swap(A[i],A[j]);
  }
  done:
  S=A,C=B;
  string act=solve();
  bool x=exp=="---",y=act=="---";
  if(x!=y) {
    dump(A,B,exp,act);
  }
  assert(x==y);
}

string gen() {
  VI A=genRandSeq(5000,0,26);
  string X(5000,'.');
  REP(i,SZ(A)) X[i]='A'+A[i];
  return X;
}
string gen2() {
  return string(2500,'b')+string(2500,'a');
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  /*
  string A=gen2(),B=string(5000,'b');
  dump(A);
  dump(B);
  return 0;*/
//  while(true) test();
  
  int T; cin>>T;
  REP(i,T) {
    cin>>S>>C;
    cout<<solve()<<endl;
  }
  
  return 0;
}
