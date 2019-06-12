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

// $ cp-batch BeautifulLyrics | diff BeautifulLyrics.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BeautifulLyrics.cpp && ./a.out

/*
 
 6/11/2019
 
 6:33-7:50 AC
 
 https://codeforces.com/blog/entry/67614
 
 Implementation by @hitonanode is much better than author's
 https://codeforces.com/contest/1182/submission/55443013
 
 */

const int MAX_N=1e6+1;
string S[MAX_N];
string T[MAX_N];
int N;
set<char> V={ 'a', 'e', 'o', 'i','u'};

void solve() {
  map<int,map<char,VI>> X;
  vector<II> A,B;
  map<int,VI> rest;
  REP(i,N) {
    int l=SZ(T[i]);
    char c=T[i].back();
    if(l==0) rest[l].push_back(i);
    else X[l][c].push_back(i);
  }
  FORR(kvp1,X)FORR(kvp2,kvp1.second) {
    int L=SZ(kvp2.second);
    REP(i,L/2) A.emplace_back(kvp2.second[2*i],kvp2.second[2*i+1]);
    if(L%2==1) rest[kvp1.first].push_back(kvp2.second.back());
  }
  FORR(kvp,rest) {
    int L=SZ(kvp.second);
    REP(i,L/2) B.emplace_back(kvp.second[2*i],kvp.second[2*i+1]);
  }
  while(SZ(A)>SZ(B)) B.push_back(A.back()),A.pop_back();
  println("%d",SZ(A));
  REP(i,SZ(A)) {
    int w0=B[i].first,w2=B[i].second,w1=A[i].first,w3=A[i].second;
    println("%s %s", S[w0].c_str(), S[w1].c_str());
    println("%s %s", S[w2].c_str(), S[w3].c_str());
  }
}

map<int,map<char,VI>> X;
void solve_org() {
  X.clear();
  REP(i,N) {
    int l=SZ(T[i]);
    if(l==0)T[i].push_back('$');
    char c=T[i].back();
    X[l][c].push_back(i);
  }
  int p0=0,p1=0;
  FORR(kvp1,X){
    int x=0;
    FORR(kvp2,kvp1.second) {
      int p=SZ(kvp2.second)/2;
      if(kvp2.first=='$') p=0;
      p0+=2*p;
      x+=SZ(kvp2.second)-2*p;
    }
    x=x/2*2;
    p1+=x;
  }
  p0/=2,p1/=2;
  int M=min(p0,(p0+p1)/2);
  dump(p0,p1,M);
  int m=M;
  vector<int> Y,Z;
  FORR(kvp1,X)FORR(kvp2,kvp1.second) {
    int p=SZ(kvp2.second)/2;
    if(kvp2.first=='$') p=0;
    int x=min(m,p);
    REP(i,SZ(kvp2.second)) {
      if(i<2*x) Y.push_back(kvp2.second[i]);
      else {
        if(SZ(Z)%2==1&&SZ(T[Z.back()])!=SZ(T[kvp2.second[i]])) Z.pop_back();
        Z.push_back(kvp2.second[i]);
      }
    }
    m-=x;
  }
  REP(i,SZ(Y)/2) {
    string a=T[Y[2*i]],b=T[Y[2*i+1]];
    dump(a,b);
    assert(SZ(a)==SZ(b));
    assert(a.back()!='$');
    assert(a.back()==b.back());
  }
  REP(i,SZ(Z)/2) {
    string a=T[Z[2*i]],b=T[Z[2*i+1]];
    dump(a,b);
    assert(SZ(a)==SZ(b));
  }
  assert(SZ(Y)>=2*M&&SZ(Z)>=2*M);
  println("%d",M);
  REP(i,M) {
    int w1=Y[2*i],w3=Y[2*i+1],w0=Z[2*i],w2=Z[2*i+1];
    assert(SZ(T[w0])==SZ(T[w2]));
    assert(SZ(T[w1])==SZ(T[w3]));
    assert(T[w1].back()==T[w3].back());
    println("%s %s", S[w0].c_str(), S[w1].c_str());
    println("%s %s", S[w2].c_str(), S[w3].c_str());
  }
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
  N=genRandNum(1,10);
  REP(i,N) {
    VI x=genRandSeq(genRandNum(0,4),0,5);
    string s; REP(j,SZ(x)) s.push_back('a'+x[j]);
    string t;
    FORR(c,s)if(V.count(c)) t.push_back(c);
    S[i]=s,T[i]=t;
  }
  dump(N);
  dumpC(S,S+N);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N;
  REP(i,N) {
    string s; cin>>s;
    string t;
    FORR(c,s)if(V.count(c)) t.push_back(c);
    S[i]=s,T[i]=t;
  }
  solve();
  
  return 0;
}
