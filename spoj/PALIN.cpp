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

/* Strip leading zero */
void stripZero(string &s) {
  s.erase(0, s.find_first_not_of('0'));
}

bool isLess(const string &s1, const string &s2) {
  if (s1.size() == s2.size())
    return s1 < s2;
  return s1.size() < s2.size();
}

string add1(const string& s) {
  string ans;
  reverse_copy(s.begin(),s.end(), back_inserter(ans));
  if (ans.size() == 0) { return "1"; }
  int carry = 1, pos = 0;
  do {
    int num = ans[pos] - '0';
    num = num + carry;
    carry = 0;
    if (num > 9) { carry = 1; ans[pos] = '0' + num%10; }
    else { ans[pos] = '0' + num; }
  } while(carry && ++pos < (int)ans.size());
  if (carry) { ans += '1'; }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main()
{
  ll N;
  string s;
  //ios::sync_with_stdio(0);
  //cin.tie(0);
  cin >> N;
  while (N--) {
    cin >> s;
    stripZero(s);
    if (s.empty()) { cout << "1";  continue; }
    string sstart, smid, send;
    bool isOdd = (s.size() % 2);
    auto pos = s.size()/2;
    if (isOdd) {
      smid = s[pos];
    }
    sstart = s.substr(0,pos);
    if (isOdd) { ++pos; }
    send = s.substr(pos, string::npos);

    //cout << "## " << sstart << ":" << smid << ":" << send << endl;
    string rsstart;
    reverse_copy(sstart.begin(),sstart.end(), back_inserter(rsstart));
    string ans = sstart + smid + rsstart;
    if (isLess(s, ans)) { cout << ans << endl; continue; }

    string newsmid {smid};
    do {
      /* handles both even and odd */
      newsmid = add1(newsmid);
      if (newsmid.size() > smid.size())
	{
	  smid = (isOdd) ? "0" : "";
	  break;
	}
      ans = sstart + newsmid + rsstart;
      //cout << "** " << ans << endl;
    } while (!isLess(s, ans));

    if (isLess(s, ans)) { cout << ans << endl; continue; }

    string newsstart {sstart};
    do {
      newsstart = add1(newsstart);
      string rsstart;
      reverse_copy(newsstart.begin(),newsstart.end(), back_inserter(rsstart));
      ans = newsstart + smid +rsstart;
      //cout << "** " << ans << endl;
    } while(!isLess(s, ans));

    // fix zero
    if (ans.size() - s.size() >= 2) {
      if (isOdd) { smid = {}; }
      else { newsstart.pop_back(); smid = "0"; }
      string rsstart;
      reverse_copy(newsstart.begin(),newsstart.end(), back_inserter(rsstart));
      ans = newsstart + smid +rsstart;
    }
    
    cout << ans << endl;
  }
}
