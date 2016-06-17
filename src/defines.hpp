#ifndef __re_defines_hpp_defined
#define __re_defines_hpp_defined

#if defined(_DEBUG) || defined(QT_QML_DEBUG)
#define RE_DEBUG
#endif

/* Inline functions. */
#ifdef _MSC_VER
#define REIL __forceinline
#else
#define REIL inline
#endif

#define RECX constexpr

#define RECX REIL RECX

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
