#ifndef _F_DEFINES_HPP
#define _F_DEFINES_HPP

#define FPROJECT_NAMEU "LAUDANUM"
#define FPROJECT_NAMEC "Laudanum"
#define FPROJECT_NAMEL "laudanum"

#define FWINDOW_FALLBACK_W 1280
#define FWINDOW_FALLBACK_H 720

// from:
// Stackoverflow: How to detect reliably Mac OS X, iOS, Linux, Windows in C preprocessor?
// Answer by: Evgeny Gavrin
#ifdef _WIN32
#define FOS_WIN
#ifdef _WIN64
#define FOS_WIN64
#else
#define FOS_WIN32
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#define FOS_SIM
#elif TARGET_OS_IPHONE
#define FOS_IOS
#elif TARGET_OS_MAC
#define FOS_APL
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

#endif