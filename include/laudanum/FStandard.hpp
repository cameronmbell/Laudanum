#ifndef _F_STANDARD_HPP
#define _F_STANDARD_HPP

// from make_unique and perfect forwarding by Herb Sutter
namespace FStandard {
    template<typename T, typename... Args>
    std::unique_ptr<T> makeUnique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
};

#endif