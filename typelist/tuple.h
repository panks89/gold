#ifndef TUPLE_H
#define TUPLE_H

#include <type_traits>
#include "typelist.h"

namespace TL {

  namespace cpp14 {
    template <typename... types>
    struct VariadicTypelist;

    template<>
    struct VariadicTypelist<> {
      using Result = ::TL::NullType;
    };
    
    template <typename type, typename... types>
    struct VariadicTypelist<type, types...> {
      using Result = ::TL::typelist<type, typename VariadicTypelist<types...>::Result>;
    };
  }

  template<typename type, typename... types>
  using tupleType = typename cpp14::VariadicTypelist<type, types...>::Result;

}


#endif /* TUPLE_H */
