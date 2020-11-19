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

// $ cp-batch BinaryTable | diff BinaryTable.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BinaryTable.cpp && ./a.out

/*

 11/18/2020

 0:01-01:25 WA
 1:47 AC

 https://twitter.com/kzyKT_M/status/1328742328320724993
 https://twitter.com/laycrs/status/1328742283768827904
 https://twitter.com/ngtkana/status/1328742564095164417
 https://twitter.com/kinaba/status/1328750699698552832

 */

const int MAX_N=1e2+1;
string S[MAX_N];
int N,M;

bool val(int i, int j) { return S[i][j]-'0'; }
void solve() {
  VV<int> res;
  auto tr=[&](int i, int j, vector<II> op) {
    dump(i,j);
    VI opop;
    FORR(d,op) {
      d.first+=i,d.second+=j;
      assert(d.first<N);
      assert(d.second<M);
      S[d.first][d.second]=(char)('0'+(1-val(d.first,d.second)));
      opop.push_back(d.first),opop.push_back(d.second);
    }
    res.push_back(opop);
  };
  auto f2=[&](auto &&self, int i, int j) {
    int cnt=0;
    REP(dx,2)REP(dy,2) cnt+=val(i+dy,j+dx);
    if(cnt==0) return;
    vector<II> op;
    if(cnt==4) {
      op={{0,0},{0,1},{1,0}};
    } else if(cnt==3) {
      REP(dx,2)REP(dy,2) if(val(i+dy,j+dx)) {
        op.emplace_back(dy,dx);
      }
    } else {
      bool t1=false;
      int cnt0=0;
      REP(dx,2)REP(dy,2) {
        if((cnt0<2&&val(i+dy,j+dx)==0)||(val(i+dy,j+dx)&&!t1)) {
          op.emplace_back(dy,dx);
          if(val(i+dy,j+dx)) t1=true;
          else ++cnt0;
        }
      }
    }
    //dump(cnt);
    //dumpc(op);
    assert(SZ(op)==3);
    tr(i,j,op);
    self(self,i,j);
  };

  auto f23=[&](auto &&self, int i, int j) {
    vector<II> op;
    if(val(i,j)&&val(i+1,j)) {
      op.emplace_back(0,0),op.emplace_back(1,0),op.emplace_back(0,1);
    } else if(val(i,j)) {
      op.emplace_back(0,0),op.emplace_back(0,1),op.emplace_back(1,1);
    } else if(val(i+1,j)) {
      op.emplace_back(1,0),op.emplace_back(0,1),op.emplace_back(1,1);
    }
    if(SZ(op)>0) tr(i,j,op);
    assert(val(i,j)==0);
    assert(val(i+1,j)==0);
  };

  auto f32=[&](auto &&self, int i, int j) {
    vector<II> op;
    if(val(i,j)&&val(i,j+1)) {
      op.emplace_back(0,0),op.emplace_back(0,1),op.emplace_back(1,0);
    } else if(val(i,j)) {
      op.emplace_back(0,0),op.emplace_back(1,0),op.emplace_back(1,1);
    } else if(val(i,j+1)) {
      op.emplace_back(0,1),op.emplace_back(1,1),op.emplace_back(1,0);
    }
    if(SZ(op)>0) tr(i,j,op);
    assert(val(i,j)==0);
    assert(val(i,j+1)==0);
  };

  if(N==2&&M==2) {
    true;
  } else {
    if(M>2) for(int i=0; i<N-1; i+=2) for(int j=0; j<M-1; j+=1) {
      dump("f23-1",i,j);
      f23(f23,i,j);
    }
    //REP(i,N) dump(S[i]);

    for(int j=0; j<M-1; j+=1) {
      dump("f23-2",N-2,j);
      f23(f23,N-2,j);
    }
    for(int i=0; i<N-1; i+=1) {
      dump("f32",i,M-2);
      f32(f32,i,M-2);
    }
  }

  f2(f2,N-2,M-2);

  dump(SZ(res));
  assert(SZ(res)<=N*M);
  cout<<SZ(res)<<endl;
  FORR(op,res) {
    FORR(a,op) cout<<a+1<<" ";
    cout<<endl;
  }

  REP(i,N) dump(S[i]);
  REP(i,N)REP(j,M) assert(!val(i,j));
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
template <typename Integer>
vector<Integer> genRandSeq(int size, Integer lb, Integer ub) {
  if (size==0) return {};
  vector<Integer> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
void test() {
  N=genRandNum(2,10),M=genRandNum(2,10);
  REP(i,N) {
    VI as=genRandSeq(M,0,2);
    S[i]=string(M,'0');
    REP(j,M) if(as[j]) S[i][j]='1';
  }
  cout<<N<<" "<<M<<endl;
  REP(i,N) cout<<S[i]<<endl;
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int t; cin>>t;
  while(t--) {
    cin>>N>>M;
    REP(i,N) cin>>S[i];
    solve();
  }

  return 0;
}
