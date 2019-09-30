#ifndef TUPLE_H
#define TUPLE_H

#include <type_traits>
#include "typelist.h"

namespace TL {

  namespace cpp14 {

    template <typename... types>
    struct VariadicTypelist;
    
    template <typename type, typename... types>
    struct VariadicTypelistHelper {
      using Result = ::TL::typelist<type, typename VariadicTypelist<types...>::Result>;
    };
    
    template <typename... types>
    struct VariadicTypelist {
      static constexpr bool cond { sizeof...(types) == 0 };
    public:
      using Result = std::conditional_t<cond, ::TL::NullType, typename VariadicTypelistHelper<types...>::Result>;
    };
  }
}


#endif /* TUPLE_H */
