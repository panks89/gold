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

bool ifWins(const vector<string> &v, const string winner) {
  for (auto s : v) {
    if (s == winner) { return true; }
  }
  for ( auto i = 0; i < 3; ++i) {
    string s = { v[0][i], v[1][i], v[2][i]};
    if (s == winner) { return true; }
  }
  string s = {v[0][0], v[1][1], v[2][2]};
  if (s == winner) { return true; }
  s = {v[2][0], v[1][1], v[0][2]};
  if (s == winner) { return true; }
  return false;
}

int main()
{
  
  //ios::sync_with_stdio(0);
  //cin.tie(0);
  ll N, x, o;
  vector<string> v(3, "");
  cin >> N;
  while (N--) {
    x = 0, o = 0;
    for (auto &s: v) {
      cin >>s;
      for (auto j : s) {
	if (j == 'X') { ++x; }
	else if (j == 'O') { ++o; }
      }
    }
    bool ans = true;
    bool xWins = ifWins(v, "XXX"), oWins = ifWins(v, "OOO");
    if (o != x && x != (o+1)) { ans = false; }
    if (ans && xWins && x != o+1) { ans = false; }
    if (ans && oWins && x != o) { ans = false; }
    if (ans && xWins && oWins) { ans = false; }
    if (ans) { cout << "yes"; }
    else { cout << "no"; }
    cout << endl;
  }
}
