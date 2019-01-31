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

// $ cp-batch Compression | diff Compression.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Compression.cpp && ./a.out

/*
 
 1/26/2019
 
 8:18-9:10 give up
 
 1/30/2019
 
 10:25-11:10 gifured out bug
 
 Are you crazy? Monotone property NEVER holds 🖕🖕🖕🖕🖕🖕🖕🖕🖕
 If a is ok, a*k (k>=1) holds. However no linear monotone property exists. Fuck.
 
 11:15-11:35, 12:30-14:00 bug fix and got AC.
 
 My bug fix was correct. However due to bug of test data generator and standard input, I wasted tons of time 🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕
 
 https://codeforces.com/blog/entry/64847
 https://betrue12.hateblo.jp/entry/2019/01/28/205015
  - gcd is necessary and sufficient
 
 https://codeforces.com/blog/entry/64833
  - 2d cumulative sum
  - beautiful complexity analysis leveraging 𝜻(2), Riemann zeta function
 
 Condition can be reduced to sqare area. It makes sense to use 2d cumulative sum to query the match.
 
 */

const int MAX_N=5200+1;
int A[MAX_N][MAX_N];
int N;

map<int,int> primeFactors(LL n) {
  assert(n>=1);
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) while(n%p==0) {
    res.push_back(p);
    n/=p;
  }
  if(n>1) res.push_back(n);
  map<int,int> ans;
  FORR(n,res) ans[n]++;
  return ans;
}

bool ok(int len) {
//  dump2(N,len);
  REP(i,N/len) REP(j,N/len) {
    int v=A[i*len][j*len];
    REP(k,len)REP(l,len) {
//      dump4(i,j,i*len+k,j*len+l);
      if(A[i*len+k][j*len+l]!=v) {
        /*
        REP(k,len) {
          REP(l,len) cerr<<A[i*len+k][j*len+l];
          cout<<endl;
        }
        */
        return false;
      }
    }
  }
  return true;
}

LL pow(LL a, LL b) {
  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a;
    a*=a;
  }
  return res;
}

int f(int p, int cnt) {
  int good=0,bad=cnt+1;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    bool a=ok(pow(p,m));
    (a?good:bad)=m;
  }
  return good;
}

// original solution
int solve_primefact() {
  /*
  REP(i,N) {
    REP(j,N)cout<<A[i][j];
    cout<<endl;
  }*/
  auto ps=primeFactors(N);
  int res=1;
  FORR(kvp,ps) {
    int p=kvp.first,cnt=kvp.second;
    int x=f(p,cnt);
    dump(p,x,cnt);
    res*=pow(p,x);
  }
  return res;
}

int cum[MAX_N][MAX_N];

int okok(int x) {
  REP(i,N/x)REP(j,N/x) {
    int a=x*i,b=x*j,c=x*(i+1),d=x*(j+1);
    int area=cum[c][d]-cum[a][d]-cum[c][b]+cum[a][b];
    if(area!=x*x&&area!=0) return false;
  }
  return true;
}
int solve() {
  ZERO(cum);
  REP(i,N)REP(j,N) cum[i+1][j+1]=A[i][j]+cum[i+1][j]+cum[i][j+1]-cum[i][j];
  int res=1;
  FORE(x,2,N)if(N%x==0&&okok(x)) res=x;
  return res;
}

int dec(char c) {
  if(isdigit(c)) return c-'0';
  return 10+(c-'a');
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
  N=5040;
  int X=140;
  string z(X/4,'0'),f(X/4,'F');
  MINUS(A);
  
  SETI T;
  vector<string> ss;
  REP(i,N/X){
    VI S=genRandSeq(N/X,0,2);
    string s; REP(i,SZ(S)) s+=(S[i])?f:z;
    assert(SZ(s)==N/4);
    REP(ii,X) {
      ss.push_back(s);
      REP(j,SZ(s)) {
        int x=dec(s[j]);
        REP(k,4) {
          A[i*X+ii][4*j+3-k]=(x>>k)&1;
          T.emplace((i*X+ii)*N+4*j+3-k);
        }
      }
    }
  }
  
  /*
  REP(i,N/X) REP(j,N/X) {
    int v=genRandNum(0,2);
    REP(k,X)REP(l,X) {
      A[i*X+k][j*X+l]=v;
    }
  }
  REP(i,N)REP(j,N) assert(A[i][j]!=-1);*/
  
  int res=solve();
  if(res!=X) {
    cout<<N<<endl;
//    REP(i,SZ(ss)) cout<<ss[i]<<endl;
    dump(res);
  }
  assert(res==X);
}

bitset<27040000> S;
char buf[5300];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  scanf("%d",&N);
  REP(i,N) {
//    string s; cin>>s;
    scanf("%s",buf);
    
    REP(j,N/4) {
      int x=dec(buf[j]);
      REP(k,4) {
        A[i][4*j+3-k]=(x>>k)&1;
        S[i*N+4*j+3-k]=1;
      }
    }
  }
  assert(S.count()==N*N);
  cout<<solve()<<endl;
  return 0;
}
