#include <iostream>
#include <vector>
using namespace std;

// declare the maximumProfit function here if not already declared
int maximumProfit(vector<int> & prices, int n) {
  if (n == 0) {
    return 0;
  }

  int maxProfit = -1;
  // using n to find the minimum number of iterations since that is the size of the current
  // rod
  for (int i = 0; i < n; i++) {
    int len = i + 1;
    int profit = prices[i];
    int result = profit + maximumProfit(prices, n - len);
    maxProfit = std::max(maxProfit, result);
  }
  return maxProfit;
}
// Your test function is assumed to be declared here
void test(int testCase, int expected, int actual);

int main() {
  // Test case 1
  vector<int> prices1 = {1, 5, 8, 9, 10, 17, 17, 20};
  int n1 = 8;
  int expected1 = 22;
  test(1, expected1, maximumProfit(prices1, n1));

  // Test case 2
  vector<int> prices2 = {3, 5, 8, 9, 10, 17, 17, 20};
  int n2 = 8;
  int expected2 = 24;
  test(2, expected2, maximumProfit(prices2, n2));
  
  // Test case 3
  vector<int> prices3 = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
  int n3 = 10;
  int expected3 = 30;
  test(3, expected3, maximumProfit(prices3, n3));

  // Add more test cases here...

  return 0;
}

void test(int testCase, int expected, int actual) {
  cout << "Test case " << testCase << ": ";
  if (actual == expected)
    cout << "Passed";
  else
    cout << "Failed (expected = " << expected << ", actual = " << actual << ")";
  cout << endl;
}