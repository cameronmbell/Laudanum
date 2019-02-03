#include <laudanum/FExcept.hpp>

#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

namespace _details {

void FRawLog(const char* precursor_text, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    std::time_t time = std::time(0);
    std::tm* current = std::localtime(&time);

    std::printf("[%02d:%02d:%02d %s] ", 
        current->tm_hour % 12 == 0?12:current->tm_hour % 12,
        current->tm_min, current->tm_sec,
        current->tm_hour >= 12?"PM":"AM");

    if (precursor_text)
        std::printf("[%s] ", precursor_text);
    std::vprintf(fmt, args);
    std::putchar('\n');

    va_end(args);
}

void FRawAssert(int line, const char* file, const char* function, const char* expression) {
    // path is guarenteed to begin with a path separator
    const char* clean_file = std::strrchr(file, '/') + 1;

    FRawLog("ASRT", "(%s):(%d) Debug assertion failed in function: %s whilst evaluating: %s", 
        clean_file, line, function, expression);

    std::exit(1);
}

}