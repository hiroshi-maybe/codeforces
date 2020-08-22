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

// $ cp-batch TwoTypesOfSpells | diff TwoTypesOfSpells.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TwoTypesOfSpells.cpp && ./a.out

/*

 8/14/2020

 8:33-9:35 give up

 8/20/2020

 9:20-10:30, 21:42-22:12 RE

 8/21/2020

 22:20-23:11 WA

 8/22/2020

 8:20-9:24 AC after 14WA

 https://twitter.com/hanseilimak/status/1297214868781588482
 https://codeforces.com/contest/1398/submission/90648912
 https://codeforces.com/blog/entry/81506

 https://twitter.com/laycrs/status/1294311771348414466
 https://twitter.com/n_vip/status/1294312926887608320
 https://twitter.com/natsugir/status/1294314046544474113
 https://twitter.com/ajis_ka/status/1294313761558298624

 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  LL tot=0;

  set<pair<LL,int>> D;
  LL dsum=0; VI dcnt(2);
  int dsize=0;

  auto addtod=[&](pair<LL,int> p) {
    dsum+=p.first,dcnt[p.second]++,D.emplace(p);
  };
  auto remfromd=[&](pair<LL,int> p) {
    D.erase(p),dcnt[p.second]--,dsum-=p.first;
  };
  auto mind=[&]() -> pair<LL,int> { return *D.begin(); };

  vector<set<LL>> R(2);

  int N; cin>>N;

  VI cnt(2,0);

  REP(i,N) {
    int t; cin>>t;
    LL x; cin>>x;
    tot+=x;
    if(t==1) {
      if(x<0) dsize-=1;
      else dsize+=1;
    }
    dump(i,t,x,dsize);

    if(x<0) {
      cnt[t]--;
      // rem
      x=-x;
      if(D.count({x,t})) {
        remfromd({x,t});
      } else {
        assert(R[t].count(x));
        R[t].erase(x);
      }
    } else {
      cnt[t]++;
      // add
      addtod({x,t});
    }

    while(SZ(D)>dsize) {
      auto p=mind();
      remfromd(p);
      R[p.second].emplace(p.first);
    }
    while(SZ(D)<dsize) {
      const LL Inf=1e16;
      pair<LL,int> x[2]={{-Inf,0},{-Inf,1}};
      REP(i,2) if(SZ(R[i])) x[i]={*R[i].rbegin(),i};
      auto a=max(x[0],x[1]);
      if(x[0].first==x[1].first) a=x[0];
      addtod(a);
      //assert(a.first!=-Inf);
      R[a.second].erase(a.first);
    }

    assert(SZ(D)==dsize);
    dump(SZ(D),dsize);
    dumpc(D);
    dumpc(R[0]);
    dumpc(R[1]);

    REP(i,2) if(SZ(R[i])&&SZ(D)) {
      assert(mind().first>*R[i].rbegin());
    }

    while(SZ(D)) {
      auto p=mind();
      if(SZ(R[0])&&*R[0].rbegin()>p.first) {
        addtod({*R[0].rbegin(),0}),R[0].erase(*R[0].rbegin());
      } else if(SZ(R[1])&&*R[1].rbegin()>p.first) {
        addtod({*R[1].rbegin(),1}),R[1].erase(*R[1].rbegin());
      } else break;
      remfromd(p),R[p.second].emplace(p.first);
    }

    LL res=tot+dsum;
    if(dcnt[0]==0&&SZ(D)) {
      //assert(SZ(R[1])==0);
      res-=mind().first;
      if(SZ(R[0])) res+=*R[0].rbegin();
    }

    dump(cnt[0],dcnt[0],SZ(R[0]));
    dump(cnt[1],dcnt[1],SZ(R[1]));
    assert(cnt[0]==dcnt[0]+SZ(R[0]));
    assert(cnt[1]==dcnt[1]+SZ(R[1]));

    cout<<res<<endl;
  }
}

/*
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int N; cin>>N;
  LL sum=0,tier1=0;
  int cnt0=0;

  set<pair<LL,int>> Q1,Q2;
  auto erasetier1=[&](LL d, int t) -> bool {
    if(d>0) d=-d;
    if(!Q1.count({d,t})) return false;
    Q1.erase({d,t});
    tier1+=d;
    if(t==0) cnt0-=1;
    return true;
  };
  auto addtier1=[&](LL d, int t) {
    if(d>0) d=-d;
    Q1.emplace(d,t);
    tier1-=d;
    if(t==0) cnt0++;
  };

  REP(i,N) {
    int t; cin>>t;
    LL d; cin>>d;
    sum+=d;
    if(d<0) {
      if(erasetier1(d,t)) {
        if(SZ(Q2)) {
          auto it=Q2.begin();
          addtier1(it->first,it->second);
        }
      } else if(Q2.count({d,t})) {
        Q2.erase({d,t});
      }
    } else {
      if(SZ(Q1)) {

      }
    }

    LL res=sum+tier1;
    if(cnt0==)
  }

  return 0;
}*/
