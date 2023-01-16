#include "quadtree.h"
#include <iostream>

int main() {
  StaticQuadTree<int, 64, 3, Bounds2D::from_width_height(1000, 1000)> qt{};
  printf("QuadTree occupies %lu bytes\n", sizeof(qt));
  return 0;
}