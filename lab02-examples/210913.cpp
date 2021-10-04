#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string line;
    std::string word;

    while (std::getline(std::cin, line)) {
        std::istringstream line_stream(line);
        while (line_stream >> word) {
            if (word == "EXIT") {
                return 0;
            }

            std::cout << word << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}