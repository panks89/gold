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

void merge(vector<int> &v, const vector<int> &left, const vector<int> &right)
{
  // v has enough size to accomodate both sub arrays by construction
  auto vb {v.begin()};
  auto lb { left.begin()}, rb {right.begin()};
  auto le { left.end()}, re {right.end()};
  while (lb != le && rb != re) {
    if (*lb > *rb) { *(vb++) = *(rb++); }
    else { *(vb++) = *(lb++); }
  }
  vb = copy(lb, le, vb);
  copy(rb, re, vb);
}

/* stable sort */
/* space - O(n) time - O(nlgn) */
void mergeSort(vector<int> &v) {
  // base case
  if ( v.size() == 1) { return; }
  auto mid = v.begin() + (v.size() >> 1);
  vector<int> left(v.begin(), mid), right(mid, v.end());
  mergeSort(left); mergeSort(right);
  merge(v, left, right);
}

using ITR = vector<int>::iterator;
void mergeSortSTLAux(ITR b, ITR e) {
  const auto N = distance(b, e);
  if (N <= 1) { return; }
  auto mid = next(b, N/2);
  mergeSortSTLAux(b, mid);
  mergeSortSTLAux(mid,e);
  inplace_merge(b, mid, e);
}

void mergeSortSTL(vector<int> &v) {
  mergeSortSTLAux(v.begin(), v.end());
}

int main()
{
  vector<int> v {9,8};
  mergeSort(v);
  for (auto i : v) { cout << i << " "; }
  cout << endl;
  v = {5, 3, 7, 9};
  mergeSortSTL(v);
  for (auto i : v) { cout << i << " "; }
  cout << endl;

  //ios::sync_with_stdio(0);
  //cin.tie(0);
  
}
