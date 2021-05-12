#ifndef TUPLE_H
#define TUPLE_H

#include <type_traits>
#include "typelist.h"
#include "GenScatterHierarchy.h" 

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

  template <typename... types>
  using tupleType = typename cpp14::VariadicTypelist<types...>::Result;

  template <typename... types>
  using tuple = typename ::TL::GenScatterHierarchy<tupleType<types...>, ::TL::ObjectHolder>;

  template <unsigned int i, typename H>
  auto& Get(H & obj) {
    return ::TL::Field<i>(obj).value;
  }
}


#endif /* TUPLE_H */
