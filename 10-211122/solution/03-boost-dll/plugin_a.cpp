#include <boost/config.hpp>
#include "api.h"

struct plugin_a : public abstract_plugin {
    int value() const override {
        return 123;
    }
};

extern "C" BOOST_SYMBOL_EXPORT plugin_a plugin;
plugin_a plugin;
