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

using ITR = vector<int>::iterator;
void quickSortAux(ITR b, ITR e) {
  if (b == e) { return; }
  const auto axis = *b; //initial value
  const auto pivot1 = partition(b, e, [axis](const auto &i) {
				       return i < axis;});
  // set axis to its correct location
  const auto pivot2 = partition(pivot1, e, [axis](const auto &i) {
				       return i == axis;});
  quickSortAux(b, pivot1);
  quickSortAux(pivot2, e);
}

void quickSort(vector<int> &v) {
  quickSortAux(v.begin(), v.end());
}

int main()
{
  vector<int> v {8, 7, 6, 10, 4};
  quickSort(v);
  for (auto i : v) { cout << i << " "; }
  cout << endl;
  v = {};
  quickSort(v);
  for (auto i : v) { cout << i << " "; }
  cout << endl;
  v = {5};
  quickSort(v);
  for (auto i : v) { cout << i << " "; }
  cout << endl;
  //ios::sync_with_stdio(0);
  //cin.tie(0);
  
}
