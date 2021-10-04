// clang-format off
#include <lib.hpp>
#include <lib.hpp>

#include <vector>

// clang-format on

int main(int argc, char *argv[]) {
    PRINT(0, argv);  // argv arg #0 = ./lab05_01

    print_all(argc, argv);  // array arg #0 = ./lab05_01

    std::vector<int> vec{5, 4, 3, 2, 1};  // vec arg #3 = 2

    PRINT(3, vec);

    // print(0, vec);
    // print_all(static_cast<int>(vec.size()), vec);
}
