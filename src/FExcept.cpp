#include "laudanum/Fexcept.hpp"

#include <ctime>
#include <cstdarg>
#include <cstdio>

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

}