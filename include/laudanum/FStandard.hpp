#ifndef _F_STANDARD_HPP
#define _F_STANDARD_HPP

#include <cmath>

// from make_unique and perfect forwarding by Herb Sutter
namespace FStandard {
    template<typename T, typename... Args>
    std::unique_ptr<T> makeUnique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    constexpr double m_pi(double mul=1.0) { return std::atan(1) * 4.0 * mul; }
    constexpr float m_pif(float mul=1.0) { return (float)std::atan(1) * 4.0f * mul; }
};

#endif