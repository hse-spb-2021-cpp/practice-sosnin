#include "api.h"
#include "secret_api.h"
#include <boost/dll/import.hpp>
#include <boost/version.hpp>
#include <iostream>

#if BOOST_VERSION >= 107600
#define boost_dll_import_symbol ::boost::dll::import_symbol
#else
#define boost_dll_import_symbol ::boost::dll::import
#endif

int main(int, char *argv[])
{
    boost::shared_ptr<abstract_plugin> plugin =
        boost_dll_import_symbol<abstract_plugin>(argv[1], "plugin");
    std::cout << "value=" << plugin->value() << "\n";

    boost::dll::shared_library lib(argv[1], boost::dll::load_mode::default_mode);
    if (lib.has("plugin_secret"))
    {
        boost::shared_ptr<abstract_plugin_secret> plugin_secret =
            boost_dll_import_symbol<abstract_plugin_secret>(argv[1], "plugin_secret");
        std::cout << "secret=" << plugin_secret->value() << "\n";
    }
    else
    {
        std::cout << "no secret found\n";
    }

    return 0;
}
