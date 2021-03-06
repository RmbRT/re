#ifndef __re_defines_hpp_defined
#define __re_defines_hpp_defined

#if defined(_DEBUG) || defined(QT_QML_DEBUG) || defined(DEBUG)
/** Defined when in debug mode. */
#define RE_DEBUG
#endif

#ifdef _MSC_VER
/** Inline functions. */
#define REIL __forceinline
#else
/** Inline functions. */
#define REIL inline
#endif

/** Constexpr define. */
#define RECX REIL constexpr


#ifndef _countof
#define _countof(x) (sizeof(x) / sizeof(*(x)))
#endif

#ifdef RE_DEBUG
#define RE_DBG(x) x
#define RE_RLS(x)
#define RE_SWITCH(DBG,RLS) DBG
#else
#define RE_DBG(x)
#define RE_RLS(x) x
#define RE_SWITCH(DBG,RLS) RLS
#endif

#define RE_LAST(Enumerator) Enumerator,  __re_last_field = Enumerator
#define RE_COUNT(Enum) (size_t(Enum::__re_last_field)+1)
#define RE_IN_ENUM(Constant, Enum) (size_t(Constant) < RE_COUNT(Enum))

/** Constexpr with debug assertions. */
#define RECXDA RE_SWITCH(REIL,RECX)


#define CXX11 201103L
#if __cplusplus < CXX11
#error Needs C++11 or higher.
#endif

#if __cplusplus > CXX11
#define RECX14 RECX
#define RECXDA14 RECXDA
#else
#define RECX14 REIL
#define RECXDA14 REIL
#endif

#endif
