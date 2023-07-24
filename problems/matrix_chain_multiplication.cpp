#include <vector>
#include <iostream>
#include <climits>
using namespace std;

// This algorithm is essentially
// given an array of sizes from range i to j,
// partition the multiplication from i to j with k
// when we have a single matrix no multiplications need to be done
// so we add up the left and right side of partitions then multiply them together
// (i - 1 x k) * (k x j)
// for all k
//
// left bound for partition location
// right bound for partition location
// e.g. ABCD =>  A * B * C * D has 3 diffent location to partition.
int matrixChainMultiplicationRecursive(const vector<int>& dimensions, int i, int j) {
  if (i == j)
      return 0;
  
  int minCost = INT_MAX;
  
  for (int k = i; k < j; k++) {
    int cost = matrixChainMultiplicationRecursive(dimensions, i, k) +
               matrixChainMultiplicationRecursive(dimensions, k + 1, j) +
               dimensions[i - 1] * dimensions[k] * dimensions[j];

    if (cost < minCost)
      minCost = cost;
  }
  
  return minCost;
}

int matrixChainMultiplicationMemo(const vector<int>& dimensions, int i, int j, vector<vector<int>>& memo) {
  if (i == j)
    return 0;
  
  if (memo[i][j] != -1) {
    return memo[i][j];
  }


  int minCost = INT_MAX;
  for (int k = i; k < j; k++) {
    int cost = matrixChainMultiplicationRecursive(dimensions, i, k) +
               matrixChainMultiplicationRecursive(dimensions, k + 1, j) +
               dimensions[i - 1] * dimensions[k] * dimensions[j];

    if (cost < minCost)
      minCost = cost;
  }

  memo[i][j] = minCost;

  return memo[i][j];
}

int matrixChainMultiplication(vector<int>& dimensions) {
  vector<vector<int>> memo(dimensions.size(), vector<int>(dimensions.size(), - 1));
  auto res = matrixChainMultiplicationMemo(dimensions, 1, dimensions.size() - 1, memo);
  return res;
}


int matrixChainMultiplicationDp(vector<int>& dimensions) {
  int n = dimensions.size();
  // dp represents the computation of multiply the chain from Ai to Aj
  // where Ai is the maxtrix composed of dimensions (dimensions_i-1 x dimensions_i)
  int dp[n][n];
  for (int i = 1; i < n; i++) {
    dp[i][i] = 0;
  }

  for (int len = 2; len < n; len ++) {
    for (int i = 1; i < n - len + 1; i++) {
      int j = i + len - 1;

      dp[i][j] = INT_MAX;

      for (int k = i; k < j; k++) {
        int multiplications = dp[i][k] + 
                              dp[k + 1][j] + 
                              dimensions[i - 1] * dimensions[k] * dimensions[j];

        dp[i][j] = min(dp[i][j], multiplications);
      }
    }
  }
  return dp[1][n - 1];
}

void test(int testCase, int expected, int actual) {
  cout << "Test case " << testCase << ": ";
    if (actual == expected)
        cout << "Passed";
    else
        cout << "Failed (expcted = " << expected << ", actual = " << actual << " )";
    cout << endl;
}

int main() {
    // Test case 1
    vector<int> arr1 = {10, 20, 30, 40, 30};
    int expected1 = 30000;
    int computed1 = matrixChainMultiplicationDp(arr1);
    test(1, expected1, computed1);
    

    // Test case 2
    vector<int> arr2 = {5, 10, 3, 12, 5, 50, 6};
    int expected2 = 2010;
    int computed2 = matrixChainMultiplicationDp(arr2);
    test(2, expected2, computed2);

    // Add more test cases here...

    return 0;
}