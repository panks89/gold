#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

vector<ll> primes;
vector<string> sPrimes;

void setPrimes() {
  ll counter = 1;
  while (++counter <= 1000000) {
    bool flag = true;
    for (auto & i : primes) {
      if (counter % i == 0) {
	flag = false;
	break;
      }
    }
    if (flag) {
      primes.emplace_back(counter);
      sPrimes.emplace_back(to_string(counter));
    }
  }
}

void rotateRight(string &s) {
  int sz = s.size();
  char prev = s[0];
  for(auto i = 1; i < sz; ++i) {
    swap(prev, s[i]);
  }
  s[0] = prev;
}

bool ifCircularPrime(string s) {
  int sz = s.size();
  for (auto i = 1; i < sz; ++i) {
    rotateRight(s);
    if (find(sPrimes.begin(), sPrimes.end(), s) == sPrimes.end()) {
      return false;
    }
  }
  return true;
}

int main() {
  setPrimes();
  for (auto &i : sPrimes) { cout << " $$ " << i << endl; }
  ll count = 0;
  for (auto & i : sPrimes) {
    if (ifCircularPrime(i)) { ++count; }
  }
  cout << count << endl; 
}
