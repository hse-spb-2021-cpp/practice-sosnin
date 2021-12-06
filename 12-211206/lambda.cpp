#include <functional>
#include <iostream>

// Functor - function object
struct Summator {
  int value;

  explicit Summator(int base) : value(base) {}
  int operator()(int add) {
    value += add;
    return value;
  }
};

struct Object {
  explicit Object(int base) : value(base) {}

  void init_printers() {
    printer_by_ref = [this]() { // Capture this by reference
      std::cout << "Object::printer_by_ref " << value << std::endl;
    };
    printer_by_value = [*this]() { // Capture this by value (make a copy)
      std::cout << "Object::printer_by_value " << value << std::endl;
    };
  }

  int value;
  std::function<void()> printer_by_ref;
  std::function<void()> printer_by_value;
};

int main() {
  Summator sum(11);
  sum(4);
  std::cout << sum(17) << std::endl;

  int a = 0;
  int b = 0;
  int c = 0;

  auto nothing = [] {}; // same as [](){}
  nothing();

  auto print_all_by_ref = [&] { // warn: Summator sum captured by lambda too
    std::cout << "print_all_by_ref " << a << " " << b << " " << c << std::endl;
  };
  print_all_by_ref(); // 0 0 0

  ++a; // 1
  ++b; // 1
  auto print_a_b_by_ref = [&a, &b] {
    std::cout << "print_a_b_by_ref " << a << " " << b
              << /* " " << c << */ std::endl;
  };
  print_a_b_by_ref(); // 1 1

  ++a; // 2
  ++b; // 2
  const int &ref_a = a;
  const int &ref_b = b;
  auto print_a_b_by_const_ref = [&ref_a, &ref_b] {
    std::cout << "print_a_b_by_const_ref " << ref_a << " " << ref_b
              << std::endl;
  };
  print_a_b_by_const_ref(); // 2 2

  c += 2;                       // 2
  auto print_all_by_val = [=] { // warn: Summator sum captured by lambda AS COPY
    std::cout << "print_all_by_val " << a << " " << b << " " << c << std::endl;
  };

  ++a;                // 3
  ++b;                // 3
  ++c;                // 3
  print_all_by_val(); // 2 2 2

  auto print_a_b_by_val = [val_a = a, b = b] { // Same name but other scope
    std::cout << "print_a_b_by_val " << val_a << " " << b
              << /* " " << c << */ std::endl;
  };

  ++a;                // 4
  ++b;                // 4
  ++c;                // 4
  print_a_b_by_val(); // 3 3

  std::string my_very_long_string = "short";
  auto print_str = [&s = my_very_long_string] {
    std::cout << "print_str " << s << std::endl;
  };
  print_str();

  auto change_str = [&s = my_very_long_string] {
    s = "long";
  }; // ref is not const
  change_str();
  print_str();

  my_very_long_string = "not so short";
  auto change_str_val =
      [s_by_value =
           my_very_long_string]() mutable { // Have to write () w/o args because
                                            // of mutable qualifier
        std::cout << "change_str_val before " << s_by_value << std::endl;
        s_by_value = "not so long";
        std::cout << "change_str_val after " << s_by_value << std::endl;
      };
  change_str_val();

  Object obj(42);
  obj.init_printers();
  obj.value++;
  obj.printer_by_ref();   // 43
  obj.printer_by_value(); // 42

  return 0;
}