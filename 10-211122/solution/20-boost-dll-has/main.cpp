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
    boost::dll::shared_library lib(argv[1]);

    boost::shared_ptr<abstract_plugin> plugin =
        boost_dll_import_symbol<abstract_plugin>(lib, "plugin");
    std::cout << "value=" << plugin->value() << "\n";

    if (lib.has("secret_plugin")) {
        boost::shared_ptr<abstract_secret_plugin> secret_plugin =
            boost_dll_import_symbol<abstract_secret_plugin>(lib,
                                                            "secret_plugin");
        std::cout << "secret=" << secret_plugin->secret_value() << "\n";
    } else {
        std::cout << "no secrets\n";
    }
    return 0;
}
