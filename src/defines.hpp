#ifndef __re_defines_hpp_defined
#define __re_defines_hpp_defined

#if defined(_DEBUG) || defined(QT_QML_DEBUG)
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
#define RE_COUNT(Enum) size_t(Enum::__re_last_field)

/** Constexpr with debug assertions. */
#define RECXDA RESWITCH(REIL,REIL RECX)

#endif
