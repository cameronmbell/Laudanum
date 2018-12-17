#ifndef _F_EXCEPT_HPP
#define _F_EXCEPT_HPP

enum FState : char {
    F_GOOD=0,
    F_BAD=1
};

void Flog(const char* fmt, ...);

#endif