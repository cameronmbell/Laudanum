#ifndef _F_EXCEPT_HPP
#define _F_EXCEPT_HPP

#include "FDefines.hpp"

// debug logging
#define FLOG_LEVEL 0
#define FDEBUG

// return state from functions to be overloaded as a bool (char)
// this is preferred over exceptions because of the performance 
// implications of the latter
enum FState : char {
    F_GOOD=0,
    F_BAD=1
};

// provide compiler warnings for invalid printf format
// e.g. (..., "%s", 4)
#ifdef FCMP_GNU
#define FPRINTF_HINT(_i, _f) __attribute__((format(printf, (_i), (_f))))
#elif FCMP_CLANG
#define FPRINTF_HINT(_i, _f) __attribute__((__format__ (__printf__, (_i), (-f))))
#else
#define FPRINTF_HINT(_i, _f)
#endif

namespace _details {
    // log to stdout: "[current_time] [precursor_text] fmt..."
    void FRawLog(const char* precursor_text, const char* fmt, ...) FPRINTF_HINT(2, 3);

    // log assertion and kill
    void FRawAssert(int line, const char* file, const char* function, const char* expression);
};

#if !defined(FLOG_LEVEL) || FLOG_LEVEL < 1
#define FLog(f_, ...)   ::_details::FRawLog("INFO", (f_), ##__VA_ARGS__)
#endif
#if !defined(FLOG_LEVEL) || FLOG_LEVEL < 2
#define FWarn(f_, ...)  ::_details::FRawLog("WARN", (f_), ##__VA_ARGS__)
#endif
#if !defined(FLOG_LEVEL) || FLOG_LEVEL < 3
#define FErr(f_, ...)   ::_details::FRawLog("ERR ", (f_), ##__VA_ARGS__)
#endif

#if !defined(FDEBUG)
#define FAssert(expr) ((void)0)
#else
#define FAssert(expr) ((expr)? (void)0 : ::_details::FRawAssert(__LINE__, "/" __FILE__, FFUNC, #expr))
#endif

#endif