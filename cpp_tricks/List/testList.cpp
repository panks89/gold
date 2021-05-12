#include <iostream>
#include <algorithm>
#include "List.h"

using namespace std;

int main()
{

  gold::List<int> lst;
  cout << lst;
  lst.push_back(5);
  lst.push_back(4);
  gold::List<string> slist { "you", "are", "my", "Sonia"};
  //lst.append(3);
  // lst.append(3);
  // lst.append(9);
  //lst.append(10);
  slist.push_front("song : ");
  // insert 10^9 items
  //  for (long long i = 0; i < 100007; ++i) {
  //  slist.push_back ("x");
  // }
  //lst<<cout;
  //slist << cout;
  cout << slist;
  cout << "\n Using iterator\n";
  gold::List<string>::iterator b = slist.begin(), e;
  for (auto i = b; i != e; ++i)
    {
      cout << *i << " ";
    }

  cout << endl;

  for (auto i = std::begin(slist); i != std::end(slist); ++i)
    {
      cout << *i << " ";
    }

  cout << endl;

  for (auto &i : slist) { cout << i << " "; }
  cout << endl;

  for (auto const &i : slist) { cout << i << " "; }
  cout << endl;

  auto itrM = begin(slist);
  std::advance(itrM, 2);
  cout << *itrM << endl;
  auto start = slist.begin();
  itrM.swap(start);
  swap(itrM, start);
  std::rotate(slist.begin(), itrM, slist.end());
  for (auto const &i : slist) { cout << i << " "; }
  cout << endl;
  
  
  /*
  == would not work ==
  for (auto &i : slist) { cout << i << " "; }
  cout << endl;
  */
}
