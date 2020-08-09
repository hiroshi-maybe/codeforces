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

// $ cp-batch ApplejackAndStorages | diff ApplejackAndStorages.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ApplejackAndStorages.cpp && ./a.out

/*

 8/7/2020

 7:44-8:13 TLE
 8:18 TLE
 8:50 give up

 8/8/2020

 10:00-10:40, 22:14-22:50 AC

 8/9/2020

 14:08-14:50 Add editorial solution

 https://twitter.com/hanseilimak/status/1292153979153997824

 https://twitter.com/laycrs/status/1291774931533836288
 https://twitter.com/ei1333/status/1291775261864628224
 https://twitter.com/kzyKT_M/status/1291775101034041345

 */
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

void gentestcase() {
  int N=1e5;
  VI as=genRandSeq(N, 1, (int)1e5);
  cout<<N<<endl;
  FORR(a, as) cout<<a<<" ";
  cout<<endl;

  cout<<N<<endl;
  REP(i,N) {
    int x=genRandNum(0,2),y;
    if(x==0) {
      y=genRandNum(1,(int)1e5);
      as.push_back(y);
    } else {
      while(true) {
        int i=genRandNum(0,SZ(as));
        if(as[i]!=-1) {
          y=as[i],as[i]=-1;
          break;
        }
      }
    }
    cout<<(x?'-':'+')<<' '<<y<<endl;
  }
}

const int MAXA=1e5+10;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  VI cnt(MAXA,0);
  int N; cin>>N;
  REP(i,N) {
    int a; cin>>a;
    cnt[a]++;
  }

  vector<II> cnts = {{8,0},{6,0},{4,0},{2,0}};
  REP(i,MAXA) {
    int a=cnt[i];
    FORR(p,cnts) if(a>=p.first) {
      p.second++;
    }
  }

  int Q; cin>>Q;
  while(Q--) {
    char c; int a; cin>>c>>a;
    if(c=='+') {
      cnt[a]++;
      REP(i,4) if(cnts[i].first==cnt[a]) {
        cnts[i].second++;
      }
    } else {
      cnt[a]--;
      REP(i,4) if(cnts[i].first==cnt[a]+1) {
        cnts[i].second--;
      }
    }
    //dumpc(cnts);

    if(cnts[0].second>0||(cnts[1].second>0&&cnts[3].second>1)||(cnts[2].second>1)||(cnts[2].second>0&&cnts[3].second>2)) {
      cout<<"YES"<<endl;
    } else {
      cout<<"NO"<<endl;
    }
  }
}

int main_orderedset() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

   auto start = chrono::high_resolution_clock::now();
  auto measure=[&]() -> int {
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    start = stop;
    //dump(duration.count());
    return duration.count();
  };

  //gentestcase();
  //return 0;

  int N; cin>>N;
  VI cnt(MAXA);
  REP(i,N) {
    int a; cin>>a;
    cnt[a]++;
  }
  vector<II> tr(SZ(cnt));
  int c=0;
  REP(a,MAXA) if(cnt[a]>0) tr[c++]={-cnt[a],a};
  set<II> S(ALL(tr));
  //FORR(kvp,cnt) S.emplace(-kvp.second,kvp.first);

  auto top3=[&]() -> VI {
    vector<II> res;
    //dump(SZ(S));
    int L=SZ(S);
    REP(_,min(3,L)) {
      auto it=S.begin();
      res.push_back(*it);
      S.erase(it);
    }
    //dumpc(res);
    VI ans;
    //dump(3,SZ(res),measure());
    FORR(p,res) S.emplace(p),ans.push_back(-p.first);
    //dump(4,measure());
    return ans;
  };

  measure();

  int Q; cin>>Q;
  while(Q--) {
    char c; cin>>c;
    int a; cin>>a;
    int delta = c=='+'?1:-1;
    int cur=cnt[a];
    cnt[a]+=delta;
    if(S.count({-cur,a})) S.erase({-cur,a});
    S.emplace(-cnt[a],a);
    //dump(1,measure());
    auto as=top3();
    //dump(2,measure());
    int sum=0;
    /*
    dump(c,a);
    dumpc(S);
    dumpc(as);*/
    REP(i,SZ(as)) sum+=as[i]/2;
    cout<<(sum>=4&&as[0]>=4?"YES":"NO")<<endl;
  }

  return 0;
}