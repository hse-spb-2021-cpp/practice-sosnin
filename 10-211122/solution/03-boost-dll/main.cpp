#include <boost/dll/import.hpp>
#include <boost/version.hpp>
#include <iostream>
#include "api.h"
#include "secret_api.h"

#if BOOST_VERSION >= 107600
#define boost_dll_import_symbol ::boost::dll::import_symbol
#else
#define boost_dll_import_symbol ::boost::dll::import
#endif

int main(int, char *argv[]) {
    boost::shared_ptr<abstract_plugin> plugin =
        boost_dll_import_symbol<abstract_plugin>(argv[1], "plugin");
    std::cout << "value=" << plugin->value() << "\n";

    boost::shared_ptr<abstract_secret_plugin> secret_plugin =
        boost_dll_import_symbol<abstract_secret_plugin>(argv[1],
                                                        "secret_plugin");
    std::cout << "secret=" << secret_plugin->secret_value() << "\n";
    return 0;
}
