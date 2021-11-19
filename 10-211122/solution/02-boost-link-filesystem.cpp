#include <boost/filesystem/operations.hpp>
#include <cstdint>
#include <iostream>

int main() {
    constexpr std::uintmax_t expected_file_size = 23;
    auto got_file_size =
        boost::filesystem::file_size("02-boost-link-filesystem.input.txt");
    if (expected_file_size != got_file_size) {
        std::cout << "Expected " << expected_file_size << ", got "
                  << got_file_size << "\n";
        return 1;
    }
    std::cout << "All OK\n";
}
