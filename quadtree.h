#pragma once
#include <array>
#include <iostream>
#include <string_view>

struct Bounds2D {
  size_t top_left_x, top_left_y, bot_right_x, bot_right_y;

  Bounds2D() = delete;
  consteval Bounds2D(size_t tl_x, size_t tl_y, size_t br_x, size_t br_y)
      : top_left_x{tl_x}, top_left_y{tl_y}, bot_right_x{br_x}, bot_right_y{
                                                                   br_y} {}

  consteval static Bounds2D from_width_height(size_t width, size_t height) {
    return Bounds2D(0, 0, width, height);
  }
};

/**
 * @brief Check if a number is a power of 4 at compile time.
 *
 * @param number A possible power of 4
 * @return consteval bool — True if `number` == 4^k for some integer `k` else
 * false
 */
consteval bool is_power_of_4(size_t number) {
  size_t prod = 1;
  while (prod < number)
    prod *= 4;
  return prod == number;
}

template <class ElementType, size_t SubtreeCount, size_t SubtreeCapacity,
          Bounds2D Bounds>
class StaticQuadTree;

/**
 * @brief A non-allocating, generic quadtree. Useful for accessing spatial data
 * efficiently. A quadtree partitions a 2D space into nested quadrilateral
 * regions, allowing for logarithmic access to points in a given partition.
 *
 * @tparam ElementType The type of the element stored in each quadtree node
 * @tparam SubtreeCount The total number of subtrees into which the space is
 * partitioned. Should be a power of 4.
 * @tparam SubtreeCapacity The number of elements stored in each subtree.
 * @tparam Bounds The 2D region being partitioned by the quadtree.
 */
template <class ElementType, size_t SubtreeCount, size_t SubtreeCapacity,
          Bounds2D Bounds>
class StaticQuadTree {
public:
  StaticQuadTree() {
    static_assert(is_power_of_4(SubtreeCount),
                  "The capacity of a static quadtree must be a power of 4");

    for (int i = 0; i < SubtreeCount; ++i) {
      std::cout << "QT " << i << '\n';
    }
  }

private:
  // Currently just a wrapper around an array. Could flatten the array.
  struct StaticQuadTreeNode {
    std::array<ElementType, SubtreeCapacity> storage;
  };

  /*
0     1   2   3   4   5   6   7   8   9
{root, TL, TR, BL, BR,
     5 TLTL, \
     6 TLTR,  \(map to 1)
     7 TLBL,  /
     8 TLBR, /
         9 TRTL, \
        10 TRTR,  \(map to 2)
        11 TRBL,  /
        12 TRBR, /
           13
  }
  */

  /**
   * @brief Get the parent index for the given index `idx`.
   *
   * @param idx The node index for which to fetch the parent.
   * @return int The index of the parent of `idx`.
   */
  int get_parent_index(int idx) { return std::max(0, (idx - 1) / 4); }

  /**
   * @brief Get the index of the first child of the given index `idx`. Note:
   * quadtrees have 4 children.
   *
   * @param idx
   * @return int
   */
  int get_children_index(int idx) { return idx * 4 + 1; }

  friend void Test_get_parent_index();

  std::array<StaticQuadTreeNode, SubtreeCount> subtrees_;
};

void Test_get_parent_index() {}