#pragma once

#define ENUM_FLAG(TYPE)																			\
inline constexpr TYPE operator~ (TYPE a) { return (TYPE)~(int)a; }								\
inline constexpr TYPE operator| (TYPE a, TYPE b) { return (TYPE)((int)a | (int)b); }			\
inline constexpr bool operator& (TYPE a, TYPE b) { return (bool)((TYPE)((int)a & (int)b)); }			\
inline constexpr TYPE operator^ (TYPE a, TYPE b) { return (TYPE)((int)a ^ (int)b); }			\
inline constexpr TYPE& operator|= (TYPE & a, TYPE b) { return (TYPE&)((int&)a |= (int)b); }		\
inline constexpr TYPE& operator&= (TYPE & a, TYPE b) { return (TYPE&)((int&)a &= (int)b); }		\
inline constexpr TYPE& operator^= (TYPE & a, TYPE b) { return (TYPE&)((int&)a ^= (int)b); }	

#define STRINGIFY(CONSTANT) STRINGIFY_2(CONSTANT)
#define STRINGIFY_2(CONSTANT) #CONSTANT