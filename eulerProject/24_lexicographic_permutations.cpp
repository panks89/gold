#include <iostream>
#include <vector>

using namespace std;
using ull = unsigned long long;

vector<ull> factorial {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

int main()
{
  string result {"0123456789"}, ans;
  ull order = 1000000;
  for (auto i = 9; i > 0; --i) {
    int num = order / factorial[i];
    int remainder = order % factorial[i];
    if (remainder == 0) { --num; }
    order -= num * factorial[i];
    char digit = result[num];
    result.erase(num, 1);
    ans += digit;
  }
  ans += result;
  cout << ans << endl;
}

