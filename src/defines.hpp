#ifndef __re_defines_hpp_defined
#define __re_defines_hpp_defined

#if defined(_DEBUG) || defined(QT_QML_DEBUG)
#define RE_DEBUG
#endif

#define REPTRCAST __fastcall

/* Inline function calls. */
#ifdef _MSC_VER
#define REINL __forceinline
#else
#define REINL inline
#endif
#endif
