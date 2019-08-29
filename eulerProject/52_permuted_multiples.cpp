#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
using ll = long long;

int main()
{
  ll number = 1;
  bool flag =  true;
  while (flag) {
    cout << " checking number " << number << endl;
    string s { to_string(number) };
    sort(s.begin(), s.end());
    string s2 = to_string(2*number),
      s3 = to_string(3*number),
      s4 = to_string(4*number),
      s5 = to_string(5*number),
      s6 = to_string(6*number);
    sort(s2.begin(), s2.end());
    sort(s3.begin(), s3.end());
    sort(s4.begin(), s4.end());
    sort(s5.begin(), s5.end());
    sort(s6.begin(), s6.end());
    if (s == s2 && s == s3 && s == s4 && s == s5 && s == s6) { flag = false; }
    else { ++number; }
  }
  cout << number << endl;
}
