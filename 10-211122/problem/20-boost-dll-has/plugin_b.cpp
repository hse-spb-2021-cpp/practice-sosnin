#include <boost/config.hpp>
#include "api.h"

struct plugin_b : public abstract_plugin {
    int value() const override {
        return 456;
    }
};

extern "C" BOOST_SYMBOL_EXPORT plugin_b plugin;
plugin_b plugin;
