#ifndef __re_defines_hpp_defined
#define __re_defines_hpp_defined

#define RE_ENUM(name) enum class name : int

#ifdef _DEBUG
#define RE_DEBUG
#endif

/*pointer casting calls.*/
#define REPTRCAST __fastcall

/*Inline function calls.*/
#ifdef _MSC_VER
#define REINL __forceinline
#else
#define REINL inline
#endif
#endif