#ifndef SECRET_API_H_
#define SECRET_API_H_

#include <boost/config.hpp>

struct BOOST_SYMBOL_VISIBLE abstract_plugin_secret {
    virtual float value() const = 0;
    virtual ~abstract_plugin_secret() = default;
};

#endif  // SECRET_API_H_
