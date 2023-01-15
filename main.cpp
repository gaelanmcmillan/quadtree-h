#include <concepts>
#include <iostream>

#include "quadtree.h"

template <class T>
concept printable = requires(T t) { std::cout << t << '\n'; };

void print(const printable auto &item) { std::cout << item << std::endl; }

int main() {
  StaticQuadTree<int, 16> qt{};
  print("Hello, world!");
  return 0;
}