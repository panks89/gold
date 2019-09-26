// TypeList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "typelist.h"
//#include "GenScatterHierarchy.h"

using namespace std;

int main()
{
  std::cout << "Hello World!\n";
  using types = TYPELIST_4(int, string, char, double);
  cout << "Length of typelist = " << TL::Length<types>::value << endl;
  cout << "Type at " << 0 << ": " << typeid(TL::TypeAt<types, 0>::result).name() << endl;
  cout << "Type at " << 1 << ": " << typeid(TL::TypeAt<types, 1>::result).name() << endl;
  cout << "Type at " << 2 << ": " << typeid(TL::TypeAt<types, 2>::result).name() << endl;
  cout << "Type at " << 3 << ": " << typeid(TL::TypeAt<types, 3>::result).name() << endl;
  //cout << "Type at " << 4 << ": " << typeid(TL::TypeAt<types, 4>::result).name() << endl;

  cout << " char is at index : " << TL::IndexOf<types, char>::value << endl;
  cout << " int is at index : " << TL::IndexOf<types, int>::value << endl;
  cout << " double is at index : " << TL::IndexOf<types, double>::value << endl;
  cout << " string is at index : " << TL::IndexOf<types, string>::value << endl;
  cout << " float is at index : " << TL::IndexOf<types, float>::value << endl;

  using newtypes = TL::Append<types, float>::result;
  cout << " float is at index : " << TL::IndexOf<newtypes, float>::value << " after append." << endl;
	
  using afterErase = TL::Erase<newtypes, float>::result;
  cout << " float is at index : " << TL::IndexOf<afterErase, float>::value << " After erase." <<  endl;

  cout << "Append int type again!!!\n";
  using afterAppend = TL::Append<afterErase, int>::result;
  cout << "Type at " << 0 << ": " << typeid(TL::TypeAt<afterAppend, 0>::result).name() << endl;
  cout << "Type at " << 4 << ": " << typeid(TL::TypeAt<afterAppend, 4>::result).name() << endl;
  cout << "EraseAll int from the typelist . . .\n";
  using afterEraseAll = TL::EraseAll<afterAppend, int>::result;
  cout << "Size after eraseAll : " << TL::Length<afterEraseAll>::value << endl;
  cout << "Append some duplicates!!!\n";
  using dups = TL::Append<TL::Append<TL::Append<TL::Append<types, int>::result, string>::result, double>::result, int>::result;
  cout << "Length of dups typelist = " << TL::Length<dups>::value << endl;
  using nodups = TL::NoDuplicates<dups>::result;
  cout << "Length of nodups typelist = " << TL::Length<nodups>::value << endl;
  cout << "Type at " << 0 << ": " << typeid(TL::TypeAt<nodups, 0>::result).name() << endl;
  cout << "Type at " << 1 << ": " << typeid(TL::TypeAt<nodups, 1>::result).name() << endl;
  cout << "Type at " << 2 << ": " << typeid(TL::TypeAt<nodups, 2>::result).name() << endl;
  cout << "Type at " << 3 << ": " << typeid(TL::TypeAt<nodups, 3>::result).name() << endl;
  cout << "Replace All ints to string in dups typelist!!!\n";
  using noints = TL::ReplaceAll<dups, int, string>::result;
  cout << "Type at " << 0 << ": " << typeid(TL::TypeAt<noints, 0>::result).name() << endl;
  cout << "Type at " << 1 << ": " << typeid(TL::TypeAt<noints, 1>::result).name() << endl;
  cout << "Type at " << 2 << ": " << typeid(TL::TypeAt<noints, 2>::result).name() << endl;
  cout << "Type at " << 3 << ": " << typeid(TL::TypeAt<noints, 3>::result).name() << endl;
  cout << "Type at " << 4 << ": " << typeid(TL::TypeAt<noints, 4>::result).name() << endl;
  cout << "Type at " << 5 << ": " << typeid(TL::TypeAt<noints, 5>::result).name() << endl;
  cout << "Type at " << 6 << ": " << typeid(TL::TypeAt<noints, 6>::result).name() << endl;
  cout << "Type at " << 7 << ": " << typeid(TL::TypeAt<noints, 7>::result).name() << endl;
  /*
  using WidgetInfo = TL::GenScatterHierarchy<types, TL::ObjectHolder>;
  WidgetInfo object;
  (static_cast<TL::ObjectHolder<string>&>(object)).value = "pankaj";
  (static_cast<TL::ObjectHolder<int>&>(object)).value = 6;
  cout << (static_cast<TL::ObjectHolder<string>&>(object)).value << endl;
  cout << (static_cast<TL::ObjectHolder<int>&>(object)).value << endl;
  */
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
