#include <iostream>
#include <vector>
using namespace std;

int knapsack(int n, int W, vector<int>& weights, vector<int>& values) {
// Base Case 
  if (n == 0 || W == 0) {
     return 0; 
  }
  
  // If weight of the nth item is more than Knapsack capacity W, then this item cannot be included in the optimal solution 
  if (weights[n-1] > W) {
    return knapsack(n-1, W, weights, values); 
  }
  
  // Return the maximum of two cases:  
  // (1) nth item included  
  // (2) not included 
  return max(values[n-1] + knapsack(n-1, W-weights[n-1], weights, values), knapsack(n-1, W, weights, values)); 
}

void test(int testCase, int expected, int actual) {
  cout << "Test case " << testCase << ": ";
  if (actual == expected)
    cout << "Passed";
  else
    cout << "Failed (expected = " << expected << ", actual = " << actual << ")";
  cout << endl;
}

int main() {
  // Test case 1
  int n1 = 3;
  int W1 = 50;
  vector<int> weights1 = {10, 20, 30};
  vector<int> values1 = {60, 100, 120};
  int expected1 = 220;
  test(0, expected1, knapsack(n1, W1, weights1, values1));

  // Test case 2
  int n2 = 4;
  int W2 = 50;
  vector<int> weights2 = {10, 20, 30, 40};
  vector<int> values2 = {60, 100, 120, 180};
  int expected2 = 240;
  test(1, expected2, knapsack(n2, W2, weights2, values2));

  // Test case 3
  int n3 = 5;
  int W3 = 60;
  vector<int> weights3 = {10, 20, 30, 40, 50};
  vector<int> values3 = {60, 100, 120, 180, 220};
  int expected3 = 280;
  test(2, expected3, knapsack(n3, W3, weights3, values3));

  // Add more test cases here...

  return 0;
}