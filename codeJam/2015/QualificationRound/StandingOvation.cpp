#include <iostream>
#include <string>

using namespace std;

int main() {
  using ll = long long;
  ll T, smax;
  cin >> T;
  for (ll t = 1; t <= T; ++t) {
    string s;
    cin >> smax >> s;
    ll ans = 0, counter = 0;
    for (ll i = 0; i <= smax; ++i) {
      int ppl {s[i] - '0'};
      if (counter >= i) { counter += ppl; }
      else {
	auto extra {i - counter};
	ans += extra; counter += extra + ppl;
      }
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
}
