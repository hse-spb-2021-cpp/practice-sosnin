#ifndef SECRET_API_H_
#define SECRET_API_H_

#include <boost/config.hpp>

struct BOOST_SYMBOL_VISIBLE abstract_secret_plugin {
    virtual float secret_value() const = 0;
    virtual ~abstract_secret_plugin() = default;
};

#endif  // SECRET_API_H_
