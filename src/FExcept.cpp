#include "laudanum/Fexcept.hpp"

#include <ctime>
#include <cstdarg>
#include <cstdio>

void Flog(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    std::time_t time = std::time(0);
    std::tm* current = std::localtime(&time);

    printf("[%02d:%02d:%02d %s] ", 
        current->tm_hour % 12 == 0?12:current->tm_hour % 12,
        current->tm_min, current->tm_sec,
        current->tm_hour >= 12?"PM":"AM");

    vprintf(fmt, args);

    putchar('\n');

    va_end(args);
}