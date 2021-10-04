#include "lib.hpp"

void print(int num, char *array[]) {
    PRINT(num, array);
}

void print_all(int size, char *array[]) {
    for (int i = 0; i < size; ++i)
        PRINT(i, array);
}