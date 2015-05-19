#ifndef __re_defines_hpp_defined
#define __re_defines_hpp_defined

/*Enables C++ 11 language features. For example templated typedefs.
Use RE_DONT_USE_CPP_11 on MSVC 2012 and older to prevent compiling errors.*/
#ifndef RE_USE_CPP_11
#ifndef RE_DONT_USE_CPP_11
#if (__cplusplus > 199711L)
/*C++11 Features are enabled.
If you get compiling errors because of C++11 features on MSVC, define RE_DONT_USE_CPP_11*/
#define RE_USE_CPP_11
#endif
#endif
#endif


#ifdef RE_USE_CPP_11
#define RE_ENUM(name) enum class name : int
#else
#define RE_ENUM(name) enum class name : int
#endif

#ifdef _DEBUG
#define RE_DEBUG
#endif

/*pointer casting calls.*/
#define REPTRCAST __fastcall

/*Inline function calls.*/
//#define REINL
#endif