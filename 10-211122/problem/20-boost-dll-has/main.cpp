#include <boost/dll/import.hpp>
#include <boost/version.hpp>
#include <iostream>
#include "api.h"

#if BOOST_VERSION >= 107600
#define boost_dll_import_symbol ::boost::dll::import_symbol
#else
#define boost_dll_import_symbol ::boost::dll::import
#endif

int main(int, char *argv[]) {
    boost::shared_ptr<abstract_plugin> plugin =
        boost_dll_import_symbol<abstract_plugin>(argv[1], "plugin");
    std::cout << "value=" << plugin->value() << "\n";
    return 0;
}
