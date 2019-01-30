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
#include <cassert>

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

/*
  1. Stable Sort
  2. In-place
  3. Online
  Variant : keep the list always sorted
  if new element comes , find sorted location and insert.
  time complexity - O(n^2)
*/

void insertionSort(vector<int> &v) {
  auto b {v.begin()}, e{v.end()};
  for (auto i = b ; i != e; ++i) {
    const auto itr = upper_bound(b, i, *i);
    rotate(itr, i, next(i));
    assert(is_sorted(b, next(i)));
  }
}

int main()
{
  vector<int> v {7, 8, 1, 5, 6, 6};
  insertionSort(v);
  for (auto i : v) { cout << i << " "; }
  
  //ios::sync_with_stdio(0);
  //cin.tie(0);
  
}
