#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void test(int testCase, int expected, int actual) {
  cout << "Test case " << testCase << ": ";
  if (actual == expected)
    cout << "Passed";
  else
    cout << "Failed (expected = " << expected << ", actual = " << actual << ")";
  cout << endl;
}

int coinChangeRecIter(vector<int>& coins, int amount) {
  if (amount < 0) {
    return -1;
  }

  if (amount == 0) {
    return 0;
  }

  int minCoins = INT_MAX;
  for (auto coin : coins) {
    int res = coinChangeRecIter(coins, amount - coin);
    if (res >= 0 && res < minCoins) {
      minCoins = 1 + res;
    }
  }
  return (minCoins == INT_MAX) ? -1 : minCoins;
}

// The problem is actually breaking it down into states
//   - coins
//   - amount
// coins: the set of denominations
// amount: the amount of change to calculate
// i: starting index of subset of coins to choose from
//    Increasing i is essentially use removing coins from the set
//    coins[i+1: ] in python
int coinChangeRecChoose(vector<int>& coins, int amount, int i) {

  // base cases ----------------
  if (amount == 0) {
    return 0;
  }

  if (i == coins.size()) {
    return -1;
  }

  if (amount < 0) {
    return -1;
  }
  // end base cases -----------

  int takeCoin = -1;
  if (amount >= coins[i]) {
    int temp = 1 + coinChangeRecChoose(coins, amount - coins[i], i);
    if (temp != 0) {
      takeCoin = temp;
    }
  }

  int noTake = coinChangeRecChoose(coins, amount, i + 1);

  // Case 1: Both are invalid
  if (takeCoin == -1 && noTake == -1) {
    return -1;
  }

  // Case 2a, 2b: One is invalid
  if (takeCoin == -1) return noTake;
  if (noTake == -1 )  return takeCoin;

  // case 3
  return min(takeCoin, noTake);
}

int main() {
  // Test case 1
  vector<int> coins1 = {1, 2, 5};
  int amount1 = 11;
  int expected1 = 3; // 5 + 5 + 1 = 11
  test(1, expected1, coinChangeRecChoose(coins1, amount1, 0));
  test(1, expected1, coinChangeRecIter(coins1, amount1));

  // Test case 2
  vector<int> coins2 = {2};
  int amount2 = 3;
  int expected2 = -1; // No combination can sum to 3
  test(2, expected2, coinChangeRecChoose(coins2, amount2, 0));
  test(2, expected2, coinChangeRecIter(coins2, amount2));

  // Test case 3
  vector<int> coins3 = {1};
  int amount3 = 0;
  int expected3 = 0; // No coins needed for amount 0
  test(3, expected3, coinChangeRecChoose(coins3, amount3, 0));
  test(3, expected3, coinChangeRecIter(coins3, amount3));

  // Test case 4
  vector<int> coins4 = {1};
  int amount4 = 2;
  int expected4 = 2; // 1 + 1 = 2
  test(4, expected4, coinChangeRecChoose(coins4, amount4, 0));
  test(4, expected4, coinChangeRecIter(coins4, amount4));
  // Add more test cases here...

  return 0;
}