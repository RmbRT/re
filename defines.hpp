#ifndef __re_defines_hpp_defined
#define __re_defines_hpp_defined

#ifdef _DEBUG
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