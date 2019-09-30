
#ifndef TYPELIST_H
#define TYPELIST_H

#include "typelistMacros.h"

namespace TL {

  template <typename T, typename U>
  struct typelist {
    using head = T;
    using tail = U;
  };

  class NullType {};


  /*
    Length of typelist using recursion.
  */

  template <typename TList> 
  struct Length;
	
  template <>
  struct Length<NullType> {
    static constexpr int value = 0;
  };

  template <typename T, typename U>
  struct Length<typelist<T, U>> {
    static constexpr int value = 1 + Length<U>::value;
  };

  /*
    TypeAt(index) : Fetch type at the given index
  */

  template <typename TList, unsigned int index>
  struct TypeAt;

  template <typename head, typename tail>
  struct TypeAt<typelist<head, tail>, 0> {
    using result = head;
  };

  template <typename head, typename tail, unsigned int i>
  struct TypeAt<typelist<head, tail>, i> {
    using result = typename TypeAt<tail, i - 1>::result;
  };

  /*
    IndexOf(type) : Return index of given type in typelist, if present.
  */

  template <typename TList, typename type>
  struct IndexOf;

  template <typename type>
  struct IndexOf<NullType, type> {
    static constexpr int value = -1;
  };

  template <typename tail, typename type>
  struct IndexOf<typelist<type, tail>, type> {
    static constexpr int value = 0;
  };

  template <typename head, typename tail, typename type>
  struct IndexOf<typelist<head, tail>, type> {
  private:
    static constexpr int prev{ IndexOf<tail, type>::value };
  public:
    static constexpr int value{ (prev == -1) ? -1 : 1 + prev };
  };

  /*
    Append(type) : append type in typelist; functional style approach - I'll create new typelist.
  */

  template <typename TList, typename type>
  struct Append;

  template <typename type>
  struct Append<NullType, type> {
    using result = typename TYPELIST_1(type);
  };

  template <>
  struct Append<NullType, NullType> {
    using result = NullType;
  };

  template <typename head, typename tail, typename type>
  struct Append<typelist<head, tail>, type> {
    using result = typelist<head, typename Append<tail, type>::result>;
  };

  /* 
     Erase(type) : erase type from typelist.
  */

  template <typename TList, typename type>
  struct Erase;
	
  template <typename type>
  struct Erase<NullType, type> {
    using result = NullType;
  };

  template <typename type, typename tail>
  struct Erase<typelist<type, tail>, type> {
    using result = tail;
  };

  template <typename head, typename tail, typename type>
  struct Erase<typelist<head, tail>, type> {
    using result = typelist<head, typename Erase<tail, type>::result>;
  };

  /*
    EraseAll(type) : erase all occurances of type in typelist.
  */

  template <typename TList, typename type>
  struct EraseAll;

  template <typename type>
  struct EraseAll<NullType, type> {
    using result = NullType;
  };

  template <typename type, typename tail>
  struct EraseAll<typelist<type, tail>, type> {
    using result = typename EraseAll<tail, type>::result;
  };

  template <typename head, typename tail, typename type>
  struct EraseAll<typelist<head, tail>, type> {
    using result = typelist<head, typename EraseAll<tail, type>::result>;
  };

  /*
    NoDuplicates(typelist) : erase duplicate type entries from typelist.	
  */

  template <typename TList>
  struct NoDuplicates;

  template<>
  struct NoDuplicates<NullType> {
    using result = NullType;
  };

  template <typename head, typename tail>
  struct NoDuplicates<typelist<head, tail>> {
  private:
    using tempResult = typename EraseAll<tail, head>::result;
  public:
    using result = typelist<head, typename NoDuplicates<tempResult>::result>;
  };

  /*
    Replace(typelist, T, U) : replace first occurance of T with U in the typelist.
  */

  template <typename TList, typename T, typename U>
  struct Replace;

  template<typename T, typename U>
  struct Replace<NullType, T, U> {
    using result = NullType;
  };

  template <typename tail, typename T, typename U>
  struct Replace<typelist<T, tail>, T, U> {
    using result = typelist<U, tail>;
  };

  template <typename head, typename tail, typename T, typename U>
  struct Replace<typelist<head, tail>, T, U> {
    using result = typelist<head, typename Replace<tail, T, U>::result>;
  };

  /*
    ReplaceAll(typelist, T, U) : replace all occurances of T with U in the typelist.
  */

  template <typename TList, typename T, typename U>
  struct ReplaceAll;

  template<typename T, typename U>
  struct ReplaceAll<NullType, T, U> {
    using result = NullType;
  };

  template <typename tail, typename T, typename U>
  struct ReplaceAll<typelist<T, tail>, T, U> {
    using result = typelist<U, typename ReplaceAll<tail, T, U>::result>;
  };

  template <typename head, typename tail, typename T, typename U>
  struct ReplaceAll<typelist<head, tail>, T, U> {
    using result = typelist<head, typename ReplaceAll<tail, T, U>::result>;
  };

}

#endif /* TYPELIST_H */
