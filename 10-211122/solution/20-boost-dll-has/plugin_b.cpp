#include <boost/config.hpp>
#include "api.h"
#include "secret_api.h"

struct plugin_b : public abstract_plugin {
    int value() const override {
        return 456;
    }
};

extern "C" BOOST_SYMBOL_EXPORT plugin_b plugin;
plugin_b plugin;

struct secret_plugin_b : public abstract_secret_plugin {
    float secret_value() const override {
        return 531.5;
    }
};

extern "C" BOOST_SYMBOL_EXPORT secret_plugin_b secret_plugin;
secret_plugin_b secret_plugin;
