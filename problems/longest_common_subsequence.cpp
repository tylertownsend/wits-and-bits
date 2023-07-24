#include <iostream>
#include <vector>
#include <string>

using namespace std;

void test(int testCase, int expected, int actual) {
    cout << "Test case " << testCase << ": ";
    if (actual == expected)
        cout << "Passed";
    else
        cout << "Failed (expected = " << expected << ", actual = " << actual << ")";
    cout << endl;
}

int LCS(string text1, string text2, int n, int m) {
  if (n <= 0 || m <= 0) {
    return 0;
  }

  if (text1[n - 1] == text2[m - 1]) {
    return 1 + LCS(text1, text2, n - 1, m - 1);
  } else {
    return std::max(LCS(text1, text2, n - 1, m), LCS(text1, text2, n, m - 1));
  }
}

int LCSMemo(string text1, string text2, int n, int m, vector<vector<int>> memo) {
  if (n <= 0 || m <= 0) {
    return 0;
  }

  int cachedResult = memo[n - 1][m - 1];
  if (cachedResult != -1) {
    return cachedResult;
  }

  if (text1[n - 1] == text2[m - 1]) {
    memo[n - 1][m - 1] = 1 + LCS(text1, text2, n - 1, m - 1);
  } else {
    memo[n - 1][m - 1]  = std::max(LCS(text1, text2, n - 1, m), LCS(text1, text2, n, m - 1));
  }

  return memo[n - 1][m - 1];
}

int LCSDP(string text1, string text2, int n, int m) {
  int dp[n + 1][m + 1];
  for (int i = 0; i <= n; i++) {
    dp[i][0] = 0;
  }
  for (int j = 0; j <= m; j++) {
    dp[0][j] = 0;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (text1[i - 1] == text2[j - 1]) {
        dp[i][j] = 1 + dp[i - 1][j - 1];
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  return dp[n][m];
}

int main() {
    // Test case 1
    string text1_1 = "ABCDEF";
    string text2_1 = "ABCD";
    vector<vector<int>> memo_1(text1_1.length(), vector<int>(text2_1.length(), -1));
    int expected1 = 4;
    test(0, expected1, LCS(text1_1, text2_1, text1_1.length(), text2_1.length()));
    test(1, expected1, LCSMemo(text1_1, text2_1, text1_1.length(), text2_1.length(), memo_1));
    test(2, expected1, LCSDP(text1_1, text2_1, text1_1.length(), text2_1.length()));

    // Test case 2
    string text1_2 = "AGGTAB";
    string text2_2 = "GXTXAYB";
    vector<vector<int>> memo_2(text1_2.length(), vector<int>(text2_2.length(), -1));
    int expected2 = 4;
    test(3, expected2, LCS(text1_2, text2_2, text1_2.length(), text2_2.length()));
    test(4, expected2, LCSMemo(text1_2, text2_2, text1_2.length(), text2_2.length(), memo_2));
    test(5, expected2, LCSDP(text1_2, text2_2, text1_2.length(), text2_2.length()));

    // Add more test cases here...

    return 0;
}
