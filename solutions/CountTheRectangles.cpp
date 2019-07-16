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
#define UNIQUE(A) sort((A).begin(),(A).end()),(A).erase(std::unique((A).begin(), (A).end()), (A).end());
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

// $ cp-batch CountTheRectangles | diff CountTheRectangles.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CountTheRectangles.cpp && ./a.out

template <typename T> struct BIT {
public:
  int N;
  vector<T> A;
  BIT() {}
  BIT(int N) { init(N); }
  void init(int N) {
    this->N=N;
    A=vector<T>(N+1,0);
  }
  // query ∑ { sum[i] : i=l..<r }
  T query(int l, int r) {
    assert(l<=r&&0<=l&&r<=N);
    return query(r)-query(l);
  }
  // min index s.t. dat[0..i]>x
  int upperbound(T x) {
    int good=N+1,bad=0;
    while(abs(good-bad)>1) {
      int m=(good+bad)/2;
      (query(m)>x?good:bad)=m;
    }
    return good-1;
  }
  // sum[i]+=x
  void add(int i, T x) {
    assert(0<=i&&i<N);
    ++i;
    while(i<=N) A[i]+=x,i+=lsone(i);
  }
  // sum[i]=x
  void update(int i, T v) {
    T pre=query(i+1)-query(i);
    add(i,v-pre);
  }
private:
  int lsone(int i) { return i&-i; }
  // query in [0,r) : ∑ { sum[i] : i=0..r-1 }
  T query(int r) {
    assert(0<=r&&r<=N);
    T res=0;
    while(r>0) res+=A[r],r-=lsone(r);
    return res;
  }
};

/*
 
 7/15/2019
 
 13:58-15:40 give up
 
 Approach by cumulative sum is completely wrong.
 That does not solve the problem.
 
 17:10-18:36 read editorial and got AC
 
 https://codeforces.com/blog/entry/68405
 https://twitter.com/hanseilimak/status/1150974409374441472

 Sweep line in y1=0..N and iterate all horizontal bottom lines.
 Relevant vertical lines can be easily found by checking if they cross.
 Move line y2=y1..N and query # of lines in range [H[y2].x1, H[y2].x2).
 Per requirement to remove lines when moving line goes beyond top edge, we can use BIT.
 
 */

const int MAX_N=1e4+10;

vector<II> H[MAX_N],V[MAX_N];

void solve() {
  LL res=0;
  REP(y,MAX_N)FORR(p,H[y]) {
    BIT<int> bit(MAX_N);
    VV<int> del(MAX_N);
    int l=p.first,r=p.second;
    FOR(x,l,r)FORR(v,V[x]) {
      int y1=v.first,y2=v.second;
      if(y1<=y&&y<y2) {
        bit.add(x,1);
        del[y2].push_back(x);
      }
    }
    FOR(yy,y+1,MAX_N) {
      FORR(delx,del[yy]) bit.add(delx,-1);
      FORR(h,H[yy]) {
        LL cnt=bit.query(h.first,h.second);
        res+=cnt*(cnt-1)/2;
      }
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  const int base=5000;
  int N; cin>>N;
  REP(i,N) {
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    x1+=base,y1+=base,x2+=base,y2+=base;
    if(y1==y2) {
      // hor
      if(x1>x2) swap(x1,x2);
      H[y1].emplace_back(x1,x2+1);
    } else {
      // ver
      assert(x1==x2);
      if(y1>y2) swap(y1,y2);
      V[x1].emplace_back(y1,y2+1);
    }
  }
  solve();
  
  return 0;
}

/*
struct TwoDimCumSum {
public:
  int R,C;
  TwoDimCumSum(vector<vector<int>> &X) {
    this->R=X.size();
    if(R==0) return;
    this->C=X[0].size();
    this->cum=vector<vector<int>>(R+1,vector<int>(C+1,0));
    
    for(int i=0; i<R; ++i) for(int j=0; j<C; ++j) {
      cum[i+1][j+1]=cum[i][j+1]+cum[i+1][j]-cum[i][j]+X[i][j];
    }
  }
  // query of sum in rectangle r in [i1,i2), c in [j1,j2)
  int query(int i1, int j1, int i2, int j2) {
    return cum[i2][j2]-cum[i1][j2]-cum[i2][j1]+cum[i1][j1];
  }
private:
  vector<vector<int>> cum;
};
vector<III> H;

map<int,int> XI,YI;
VI X,Y;
map<int,map<int,int>> V;
void solve() {
  FORR(kvp,V) {
    int x=kvp.first;
    X.push_back(x);
    FORR(kvp2,kvp.second) {
      Y.push_back(kvp2.first);
    }
  }
  UNIQUE(Y);
  REP(i,SZ(X)) XI[X[i]]=i;
  REP(i,SZ(Y)) YI[Y[i]]=i;
  int XN=SZ(X),YN=SZ(Y);
  VV<int> A(XN,VI(YN,0));
  FORR(kvp,V) {
    int x=kvp.first;
    FORR(kvp2,kvp.second) {
      int y=kvp2.first;
      A[XI[x]][YI[y]]=kvp2.second;
    }
  }
  TwoDimCumSum cum(A);
  sort(ALL(H));
  int N=SZ(H);
  LL res=0;
  REP(j,N)REP(i,j) {
    int y1,l1,r1; tie(y1,l1,r1)=H[i];
    int y2,l2,r2; tie(y2,l2,r2)=H[j];
    dump(i,j,l1,y1,r1,y1);
    dump(i,j,l2,y2,r2,y2);
    int l=max(l1,l2),r=min(r1,r2);
    y2+=1;
    if(l>=r) continue;
    int li=lower_bound(ALL(X),l)-X.begin(),ri=lower_bound(ALL(X),r)-X.begin();
    int y1i=lower_bound(ALL(Y),y1)-Y.begin(),y2i=lower_bound(ALL(Y),y2)-Y.begin();
    LL cnt=cum.query(li,y1i,ri,y2i);
    dump(l,y1,r,y2,cnt);
    res+=cnt*(cnt-1)/2;
  }
  cout<<res<<endl;
}

int main_wrong() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  const int base=0;
  int N; cin>>N;
  REP(i,N) {
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    x1+=base,y1+=base,x2+=base,y2+=base;
    if(y1==y2) {
      // hor
      if(x1>x2) swap(x1,x2);
      H.emplace_back(y1,x1,x2+1);
    } else {
      // ver
      assert(x1==x2);
      if(y1>y2) swap(y1,y2);
      V[x1][y1]+=1;
      V[x1][y2+1]-=1;
    }
  }
  solve();
  
  return 0;
}
*/
