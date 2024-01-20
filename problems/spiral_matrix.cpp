#include <iostream>
#include <vector>
#include <queue>

using namespace std;

std::vector<int> SpiralOrder(std::vector<std::vector<int>> matrix) {
  vector<int> order;

  int totalRows = matrix.size();
  int totalCols = matrix[0].size();
  int total = totalRows * totalCols;

  int direction = 1;

  int row = 0;
  int col = 0;
  int i = 0;
  while (order.size() != total) {
    for (int i = 0; i < totalCols - 1; i++) {
      order.push_back(matrix[row][col]);
      std::cout << matrix[row][col] << " ";
      col += direction;
    }


    for (int i = 0; i < totalRows - 1; i++) {
      order.push_back(matrix[row][col]);
      std::cout << matrix[row][col] << " ";
      row += direction;
    }


    direction *= -1;

    if (direction > 0) {
      row ++;
      col ++;
      totalRows-=2;
      totalCols-=2;
    }
  }
  return order;
}

void test(int testCase, vector<int> expected, vector<int> actual) {
  std::cout << "Test case " << testCase << ": ";
  if (actual == expected)
    std::cout << "Passed";
  else {
    std::cout << "Failed (expected = ";
    for (auto e : expected) std::cout << e << " ";
    std::cout << ", actual = ";
    for (auto a : actual) std::cout << a << " ";
    std::cout << ")";
  }
  std::cout << std::endl;
}

int main() {
  // Test case 1
  vector<vector<int>> matrix1 = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };
  test(1, {1, 2, 3, 6, 9, 8, 7, 4, 5}, SpiralOrder(matrix1));

  // Test case 2
  vector<vector<int>> matrix2 = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
  };
  test(2, {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7}, SpiralOrder(matrix2));

  // Add more test cases here...

  return 0;
}
