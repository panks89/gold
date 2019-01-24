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
#include <chrono>
#include <random>

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

using Point = pair<double, double>;
using Points = pair<Point, Point>;

double distanceBetweenPonts(const Point &p1, const Point &p2) {
  return (p1.F - p2.F)*(p1.F - p2.F) + (p1.S - p2.S)*(p1.S - p2.S);
}

// O(n^2) Naive algorithm
pair<double, Points> closestPairNaive(const vector<Point> &p)
{
  if (p.size() < 2) { return {-1, {{0,0}, {0,0}} }; }
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
  auto p_xMid = p_x.at((size/2) - 1).F;
  copy_if(begin(p_y), end(p_y), back_inserter(p_yl),
	  [&p_xMid] (const Point &point) {
	    return point.F <= p_xMid;
	  });
  copy_if(begin(p_y), end(p_y), back_inserter(p_yr),
	  [&p_xMid] (const Point &point) {
	    return point.F > p_xMid;
	  });

  auto left = closestPair(p_xl, p_yl);
  auto right = closestPair(p_xr, p_yr);
  auto answer = (left.F <= right.F) ? left : right;
  auto delta = answer.F;
  /* Construct yDash array - all points within the 2 * delta wide vertical strip */
  Point xRange = { p_xMid - delta , p_xMid + delta };
  vector<Point> yDash;
  copy_if(begin(p_y), end(p_y), back_inserter(yDash),
	  [&xRange] (const Point &point) {
	    return point.F >=  xRange.F && point.F <= xRange.S;
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
  cout << "(" << p.F << ", " << p.S << ")\n"; 
}

int main()
{
  
  //ios::sync_with_stdio(0);
  //cin.tie(0);

  default_random_engine re
    (chrono::system_clock::to_time_t(chrono::system_clock::now()));
  uniform_real_distribution<double> distrib(-500.0, 500.0);
  vector<Point> p(100);
  generate(begin(p), end(p),
	   [&distrib, &re] () {
	     return Point {1000 + distrib(re), 1000 + distrib(re) };
	   });
  vector<Point> px = p;
  vector<Point> py = p;
  auto answer = closestPairNaive(p);
  cout << "Closest Pair [Naive]: " << answer.F << "\n";
  printPoint(answer.S.F);
  printPoint(answer.S.S);
  sort(begin(px), end(px),
       [](const Point &left, const Point &right) {
	 return left.F < right.F;
       });
  sort(begin(py), end(py),
       [](const Point &left, const Point &right) {
	 return left.S < right.S;
       });
  answer = closestPair(px, py);
  cout << "Closest Pair [O(nlgn)]: " << answer.F << "\n";
  printPoint(answer.S.F);
  printPoint(answer.S.S);
}
