// bАse.h
#pragma once


#include <string_view>


// Define cpp version
// MSVC
#ifdef _MSC_VER
#if _MSVC_LANG >= 202302L
#define CPP_VERSION 23
#elif _MSVC_LANG >= 202002L
#define CPP_VERSION 20
#elif _MSVC_LANG >= 201703L
#define CPP_VERSION 17
#elif _MSVC_LANG >= 201402L
#define CPP_VERSION 14
#else
#define CPP_VERSION 11
#endif

// Other compilers
#else
#if __cplusplus >= 202302L
#define CPP_VERSION 23
#elif __cplusplus >= 202002L
#define CPP_VERSION 20
#elif __cplusplus >= 201703L
#define CPP_VERSION 17
#elif __cplusplus >= 201402L
#define CPP_VERSION 14
#else
#define CPP_VERSION 11
#endif
#endif


// NOTE: dangerous macro usage. Fix later.
// CSTR = constant string value
// SCSTR = static constant string value

#if CPP_VERSION >= 17
#define SCCHR static constexpr char
#define CSTR constexpr std::string_view
#define SCSTR static constexpr std::string_view
#else
#define CCHR const char
#define CSTR const char*
#define SCSTR static const char*
#endif
