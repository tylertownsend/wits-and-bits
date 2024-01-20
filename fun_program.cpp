#include <iostream>

int main() {
  for (int i = 0; i < 2023; i++) {
    for (int j = 0; j < i; j++) {
      std::cout << "*";
    }
    std::cout << "\n";
  }

  // for (int i = 0; i < 100; i++) {
  //   std::cout << i << ".";
  //   std::cout << "\n";
  // }
  // std::cout << "Hello LEO!" << std::endl;
  return 0;
}