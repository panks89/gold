#include <iostream>
#include <string>
#include "typelist.h"
#include "tuple.h"
#include "GenScatterHierarchy.h"


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

  using WidgetInfo = TL::GenScatterHierarchy<types, TL::ObjectHolder>;
  WidgetInfo object;
  (static_cast<TL::ObjectHolder<string>&>(object)).value = "pankaj";
  (static_cast<TL::ObjectHolder<int>&>(object)).value = 6;
  cout << (static_cast<TL::ObjectHolder<string>&>(object)).value << endl;
  cout << (static_cast<TL::ObjectHolder<int>&>(object)).value << endl;
  /* Using field wrapper */
  cout << TL::Field<string>(object).value << endl;
  cout << TL::Field<int>(object).value << endl;
  //cout << TL::Field<float>(object).value << endl;
  cout << TL::Field<1>(object).value << endl;
  cout << TL::Field<0>(object).value << endl;
  //cout << TL::Field<5>(object).value << endl;

  using tupleTypes = TL::tupleType<int, double, float, char, string>;
  cout << " Size of newtypes : " << TL::Length<tupleTypes>::value << endl;
  cout << "Type at " << 0 << ": " << typeid(TL::TypeAt<tupleTypes, 0>::result).name() << endl;
  cout << "Type at " << 1 << ": " << typeid(TL::TypeAt<tupleTypes, 1>::result).name() << endl;
  cout << "Type at " << 2 << ": " << typeid(TL::TypeAt<tupleTypes, 2>::result).name() << endl;
  cout << "Type at " << 3 << ": " << typeid(TL::TypeAt<tupleTypes, 3>::result).name() << endl;
  cout << "Type at " << 3 << ": " << typeid(TL::TypeAt<tupleTypes, 4>::result).name() << endl;

  ::TL::tuple<int, string, float> widget;
  TL::Field<1>(widget).value = "This is tuple";
  cout << TL::Field<1>(widget).value << endl;
  cout << ::TL::Get<1>(widget) << endl;
}
