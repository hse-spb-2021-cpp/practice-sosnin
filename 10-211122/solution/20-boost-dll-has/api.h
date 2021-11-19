#ifndef API_H_
#define API_H_

#include <boost/config.hpp>

struct BOOST_SYMBOL_VISIBLE abstract_plugin {
    virtual int value() const = 0;
    virtual ~abstract_plugin() = default;
};

#endif  // API_H_
