#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <utility>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <limits>
#include <climits>
#include <iterator>
#include <functional>
#include <memory>
#include <fstream>

using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP1(i, a, b) for (auto i = a; i <= b; ++i)
#define REP(i, n) for (auto i = 0; i < n; ++i)
#define FD(i, a, b) for (auto i = a; i >= b ; --i)

class findUnion {
  vector<ll> rank;
  // vector of {p, {whomICanEat, whoCanEatMe}}
  vector<pair<ll, pair<ll, ll>>> p;
public:
  void printP() {
    return;
    cout << "============\n";
    for (auto i : p) {
      cout << "{" << i.F << ", " << "{" << i.S.F << ", " << i.S.S << "} } ";
    }
    cout << "\n============\n";
  }
  
  findUnion(ll n) {
    p.assign(n, {0, {-1, -1}}); rank.assign(n, 1);
    // -1 means I can't eat anyone
    for (auto i = 0; i < n; ++i) { p[i].F = i; } 
  }
  pair<ll, pair<ll, ll>> findSet(ll i) {
    return (p[i].F == i) ? p[i] : (p[i] = findSet(p[i].F));
  }
  bool isSameSet(ll i, ll j) { return findSet(i).F == findSet(j).F; }
  void unionSet(ll i, ll j) {
    if (!isSameSet(i,j)) {
      auto x = findSet(i), y = findSet(j);
      if (rank[x.F] > rank[y.F]) {
	p[y.F] = x;
      } else {
	p[x.F] = y;
	if (rank[x.F] == rank[y.F]) { ++rank[y.F]; }
      }
    }
  }
  void allowEat(ll i, ll j) // i can eat j
  {
    //cout << "Modify eating details\n";
    auto &x = p[i];
    auto &y = p[j];
    /*
      cout << "x : " << "{" << x.F << ", " << "{" << x.S.F << ", " << x.S.S << "} } \n";
      cout << "y : " << "{" << y.F << ", " << "{" << y.S.F << ", " << y.S.S << "} } \n";
    */
    if (x.S.F == -1) {
      x.S.F = y.F;
      y.S.S = x.F;
      y.S.F = x.S.S;
    } else {
      unionSet(x.S.F, j);
    }
    /*
      cout << "x : " << "{" << x.F << ", " << "{" << x.S.F << ", " << x.S.S << "} } \n";
      cout << "y : " << "{" << y.F << ", " << "{" << y.S.F << ", " << y.S.S << "} } \n";
    
      cout << "Modification over\n";
    */
  }
};

int main()
{
  
  //ios::sync_with_stdio(0);
  //cin.tie(0);

  ll t, n, k, x, y, ans, d;
  cin >> t;
  while (t--) {
    ans = 0;
    cin >> n >> k;
    findUnion us(n);
    for (ll cnt = 1; cnt <= k; ++cnt)
      {
	us.printP();
	cin >> d >> x >> y;
	if (x > n || y > n) {
	  ++ans;
	  //cout << "##" <<cnt << endl;
	  continue;
	}
	if (d == 1) {
	  if (us.isSameSet(x-1, y-1)) { continue; }
	  auto x_p = us.findSet(x-1);
	  if (x_p.S.F != -1 && us.isSameSet(x_p.S.F, y-1)) {
	    // x eat y => violation
	    ++ans;
	    //cout << "1##" <<cnt << endl;
	    continue;
	  }
	  auto y_p = us.findSet(y-1);
	  if (y_p.S.F != -1 && us.isSameSet(y_p.S.F, x-1)) {
	    // y eat x => violation
	    ++ans;
	    //cout << "2##" << cnt << endl;
	    continue;
	  }
	  // all good
	  us.unionSet(x-1, y-1);
	} else if (d == 2) {
	  // x can eat y
	  // violations:
	  // is Both are in same set or y can eat x
	  if (us.isSameSet(x-1, y-1)) {
	    ++ans;
	    //cout << "3##" << cnt << endl;
	    continue;
	  }
	  auto y_p = us.findSet(y-1);
	  if (y_p.S.F != -1 && us.isSameSet(y_p.S.F, x-1)) {
	    // y eat x => violation
	    ++ans;
	    //cout << "4##" << cnt << endl;
	    continue;
	  }
	  us.allowEat(x-1, y-1);
	}
      }
    cout << ans << endl;
  }
}
