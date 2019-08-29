#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
vector<ll> coins {1, 2, 5, 10, 20, 50, 100, 200};
vector<vector<ll>> dp(201, vector<ll>(coins.size(), 0));

ll ways(ll type, ll sum) {
  if (sum == 0) { return dp[0][type] = 1; }
  else if (sum < 0) { return 0; }
  else if (type == 8) { return 0; }
  else {
    if (dp[sum][type] != 0) { return dp[sum][type]; }
    return dp[sum][type] = ways(type, sum - coins[type]) + ways(type + 1, sum);
  }
}

int main()
{
  cout << ways(0, 200);
  
}
