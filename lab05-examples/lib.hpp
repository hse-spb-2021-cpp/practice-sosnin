#pragma once

#include <iostream>

#define PRINT(num, array) \
    std::cout << #array " arg #" << (num) << " = " << array[(num)] << std::endl;

void print(int num, char *array[]);

void print_all(int size, char *array[]);
