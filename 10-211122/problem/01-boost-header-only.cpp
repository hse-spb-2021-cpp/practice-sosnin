#include <boost/core/demangle.hpp>
#include <boost/version.hpp>
#include <iostream>
#include <string>

constexpr int NEED_BOOST_VERSION = 107100;

int main() {
    std::cout << "Boost version is: " << BOOST_VERSION << "...\n";
    if (BOOST_VERSION < NEED_BOOST_VERSION) {
        std::cout << "ERROR: Boost is too old\n";
        return 1;
    }
    if (BOOST_VERSION > NEED_BOOST_VERSION) {
        std::cout << "WARNING: your Boost may be too recent\n";
    }

    std::string int_name = boost::core::demangle(typeid(int).name());
    std::cout << "Demangled typeid(int).name(): " << int_name << "\n";
    // Not guaranteed by either Standard or Boost.Demangle, but works on our
    // compilers.
    if (int_name != "int") {
        std::cout << "ERROR: unexpected demangle result\n";
        return 1;
    }

    std::cout << "All OK\n";
}
