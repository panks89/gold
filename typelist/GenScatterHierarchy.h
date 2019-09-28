#ifndef GENSCATTERHIERARCHY_H
#define GENSCATTERHIERARCHY_H

#include "typelist.h"

namespace TL {
  template <typename TList, template<typename> class Unit>
  struct GenScatterHierarchy;

  template <typename head, typename tail, template<typename> class Unit>
  struct GenScatterHierarchy<typelist<head, tail>, Unit> :
    public GenScatterHierarchy<head, Unit>,
    public GenScatterHierarchy<tail, Unit> {
    using LeftBase = GenScatterHierarchy<head, Unit>;
    using RightBase = GenScatterHierarchy<tail, Unit>;
  };

  template <typename atomicType, template<typename> class Unit>
  struct GenScatterHierarchy : public Unit<atomicType> {
    using LeftBase = Unit<atomicType>;
  };

  template <template<typename> class Unit>
  struct GenScatterHierarchy<NullType, Unit> {};

  template <typename T>
  struct ObjectHolder {
    T value;
  };
}

#endif /* GENSCATTERHIERARCHY_H */
