#include <boost/config.hpp>
#include "api.h"
#include "secret_api.h"

struct plugin_b : public abstract_plugin {
    int value() const override {
        return 456;
    }
};

struct plugin_b_secret : public abstract_plugin_secret {
    float value() const override {
        return 531.5;
    }
};

extern "C" BOOST_SYMBOL_EXPORT plugin_b plugin;
plugin_b plugin;

extern "C" BOOST_SYMBOL_EXPORT plugin_b_secret plugin_secret;
plugin_b_secret plugin_secret;
