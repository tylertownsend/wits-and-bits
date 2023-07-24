#pragma once
/**
 * @file binary_indexed_tree.h
 * @author tylertownsend
 * @brief  A binary indexed tree implementation based on https://stackoverflow.com/a/15444954
 * @version 0.1
 * @date 2023-02-12
 * 
 * 
 */

#include <vector>

// Also this answer is helpful: https://cs.stackexchange.com/a/95954
namespace tst {

class BinaryIndexedTree {

private:
  std::vector<int> bi_tree_;

public:
  BinaryIndexedTree() {}
  BinaryIndexedTree(int n) {
    bi_tree_.assign(n + 1, 0);
  }

  BinaryIndexedTree(std::vector<int> input) {
    bi_tree_.assign(input.size() + 1, 0);
    for (int i = 0; i < input.size(); i++) {
      UpdateBit(i, input[i]);
    }
  }

  void UpdateBit(int index, int val) {
    index = index + 1;

    while (index <= bi_tree_.size()) {
      bi_tree_[index] += val;
      // Traversing up the tree to the parent by moving to up and to left.
      // This is done by shaving off the last set 1 bit in the index (i.e, index & -index)
      index += index & (-index);
    }
  }

  int GetSum(int index) {
    int sum = 0;

    index = index + 1;

    while (index > 0) {
      sum += bi_tree_[index];
      index -= index & (- index);
    }

    return sum;
  }
};

} // namespace tst;