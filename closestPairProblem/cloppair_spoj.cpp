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
#include <iomanip>
#include <cmath>

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

using Point = pair<ll, pair<double, double>>;
using Points = pair<Point, Point>;

double distanceBetweenPonts(const Point &p1, const Point &p2) {
  return sqrt((p1.S.F - p2.S.F)*(p1.S.F - p2.S.F) +
	      (p1.S.S - p2.S.S)*(p1.S.S - p2.S.S));
}

// O(n^2) Naive algorithm
pair<double, Points> closestPairNaive(const vector<Point> &p)
{
  if (p.size() < 2) { return {-1, {{-1, {0,0}}, {-1, {0,0}}}}; }
  double minDistance = distanceBetweenPonts(p[0], p[1]);
  Points minDistancePair = {p[0], p[1]};
  auto e = end(p);
  for (auto i = begin(p); i != (e - 1); ++i) {
    for (auto j = i+1; j != e; ++j) {
      double distance = distanceBetweenPonts(*i, *j);
      if (distance < minDistance) {
	minDistance = distance;
	minDistancePair = {*i, *j};
      }
    }
  }
  return {minDistance, minDistancePair};
}

#if 1
// O(nlgn) Divide-and-conquer approach
pair<double, Points> closestPair(const vector<Point> &p_x, const vector<Point> &p_y)
{
  /* p_x and p_y are preSorted arrays with respect to coordinates */
  if (p_x.size() <= 3) {
    return closestPairNaive(p_x);
  }
  /* setup */
  auto size = p_x.size();
  vector<Point> p_xl, p_xr;
  copy(begin(p_x), begin(p_x) + size/2, back_inserter(p_xl));
  copy(begin(p_x) + size/2, end(p_x), back_inserter(p_xr));
  vector<Point> p_yl, p_yr;
  auto p_xMid = p_x.at((size/2) - 1).S.F;
  copy_if(begin(p_y), end(p_y), back_inserter(p_yl),
	  [&p_xMid] (const Point &point) {
	    return point.S.F <= p_xMid;
	  });
  copy_if(begin(p_y), end(p_y), back_inserter(p_yr),
	  [&p_xMid] (const Point &point) {
	    return point.S.F > p_xMid;
	  });

  auto left = closestPair(p_xl, p_yl);
  auto right = closestPair(p_xr, p_yr);
  auto answer = (left.F <= right.F) ? left : right;
  auto delta = answer.F;
  pair<double, double> xRange = { p_xMid - delta , p_xMid + delta };
  vector<Point> yDash;
  copy_if(begin(p_y), end(p_y), back_inserter(yDash),
	  [&xRange] (const Point &point) {
	    return point.S.F >=  xRange.F && point.S.F <= xRange.S;
	  });
  /* O(n) combine routine */
  auto e = end(yDash);
  for (auto i = begin(yDash); i != (e-1); ++i) {
    auto counter = 0;
    for (auto j = i+1; j != e && counter < 7; ++j, ++counter) {
      auto minDistance = distanceBetweenPonts(*i, *j);
      if (minDistance < delta) {
	delta = minDistance;
	answer = {delta, {*i, *j}};
      }
    }
  }
  return answer;
}

#endif

void printPoint(const Point &p) {
  cout << "(" << p.S.F << ", " << p.S.S << ")\n"; 
}

int main()
{
  
  //ios::sync_with_stdio(0);
  //cin.tie(0);

  ll N, a, b;
  cin >> N;
  vector<Point> p(N);
  for (ll i = 0; i < N; ++i) {
    cin >> a >> b;
    p[i] = {i, {a, b}};
  }
  vector<Point> px = p;
  vector<Point> py = p;
  sort(begin(px), end(px),
       [](const Point &left, const Point &right) {
	 return left.S.F < right.S.F;
       });
  sort(begin(py), end(py),
       [](const Point &left, const Point &right) {
	 return left.S.S < right.S.S;
       });
  auto answer = closestPair(px, py);
  Point u {answer.S.F}, v {answer.S.S};
  if (u.F > v.F) {swap(u,v);}
  cout << u.F << " " << v.F << " ";
  cout << setprecision(6) << fixed << answer.F << endl;
}
