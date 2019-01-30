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

int main()
{
  
  //ios::sync_with_stdio(0);
  //cin.tie(0);
  ll T;
  cin >> T;
  while (T--) {
    ll m, n, sm = 0, sn = 0, x;
    cin >> m >> n;
    for (ll i = 1; i<m ; ++i) { cin >> x; sm +=x; }
    for (ll i = 1; i<n ; ++i) { cin >> x; sn +=x; }
    cout << min ((sm + (m+1)*sn), (sn + (n+1)*sm));
  }
}
