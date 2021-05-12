#ifndef TYPELISTMACROS_H
#define TYPELISTMACROS_H

#define TYPELIST_1(T1) ::TL::typelist<T1, ::TL::NullType>
#define TYPELIST_2(T1, T2) ::TL::typelist<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) ::TL::typelist<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) ::TL::typelist<T1, TYPELIST_3(T2, T3, T4)>
#define TYPELIST_5(T1, T2, T3, T4, T5) ::TL::typelist<T1, TYPELIST_4(T2, T3, T4, T5)>
#define TYPELIST_6(T1, T2, T3, T4, T5, T6) ::TL::typelist<T1, TYPELIST_5(T2, T3, T4, T5, T6)>


#endif /* TYPELISTMACROS_H */
