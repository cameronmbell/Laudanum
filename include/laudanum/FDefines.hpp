#ifndef _F_DEFINES_HPP
#define _F_DEFINES_HPP

// project properties, should grab from cmake
#define FPROJECT_NAMEU "LAUDANUM"
#define FPROJECT_NAMEC "Laudanum"
#define FPROJECT_NAMEL "laudanum"

// from:
// stackoverflow: How to detect reliably Mac OS X, iOS, Linux, Windows in C preprocessor?
// answer by: Evgeny Gavrin
#ifdef _WIN32
#define FOS_WIN
#ifdef _WIN64
#define FOS_WIN64
#else
#define FOS_WIN32
#endif
#elif __APPLE__
#define FOS_APL
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#define FOS_SIM
#elif TARGET_OS_IPHONE
#define FOS_IOS
#elif TARGET_OS_MAC
#define FOS_MAC
#else
#error "Unknown Apple platform"
#endif
#elif __linux__
#define FOS_LINUX
#elif __unix__ // all unices not caught above
#define FOS_UNIX
#elif defined(_POSIX_VERSION)
#define FOS_POSIX
#else
#error "Unknown compiler"
#endif

// determine compiler
#if defined(__clang__)
#define FCMP_CLANG
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#define FCMP_INTEL
#elif defined(__GNUC__) || defined(__GNUG__)
#define FCMP_GNU
#elif defined(__HP_cc) || defined(__HP_aCC)
#define FCMP_HP
#elif defined(__IBMC__) || defined(__IBMCPP__)
#define FCMP_IBM
#elif defined(_MSC_VER)
#define FCMP_MSC
#elif defined(__PGI)
#define FCMP_PORTLAND
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#define FCMP_ORACLE
#endif

#endif