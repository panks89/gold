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
  In-place, O(n^2) time complexoty
  Generally performs worse than insertion sort
  Inefficient on large lists
  ===
  The algorithm divides the input list into two parts: 
  the sublist of items already sorted, 
  which is built up from left to right at the front (left) of the list. 
  And the sublist of items remaining to be sorted 
  that occupy the rest of the list. 
  Initially, the sorted sublist is empty and the unsorted sublist
  is the entire input list. The algorithm proceeds by finding the
  smallest (or largest, depending on sorting order) element in the 
  unsorted sublist, exchanging (swapping) it with the leftmost unsorted 
  element (putting it in sorted order), 
  and moving the sublist boundaries one element to the right.
  ===
*/

using vitr = vector<int>::iterator;
/*
  Heap sort is special case of selection.
  It reduces the complexity of minimum() to O(lgn) through heap DS.
  And, overall sorting is reduced to O(nlgn)
*/
vitr minimum(vitr b, vitr e) {
  // O(n)
  vitr minElement = b;
  int imin = *b;
  ++b;
  while (b != e) {
    if (*b < imin) { minElement = b; imin = *b; }
    ++b;
  }
  return minElement;
}
void selectionSort(vector<int> &v) {
  // O(n*n) ; inplace ; stable sort
  auto b = v.begin(), e = v.end();
  for (auto i = b; i != e; ++i) {
    auto j = minimum(i,e);
    swap(*i, *j);
  }
}

void selectionSortSTL(vector<int> &v) {
  auto b = begin(v), e = end(v);
  for (auto i = b ; i != e; ++i) {
    const auto selected = min_element(i, e);
    iter_swap(i, selected);
    assert(is_sorted(b, next(i)));
  }
}

int main()
{
  vector<int> v {7,5,3,0,1};
  selectionSortSTL(v);
  for (auto i:v) { cout << i << " "; }
  //ios::sync_with_stdio(0);
  //cin.tie(0);
}
