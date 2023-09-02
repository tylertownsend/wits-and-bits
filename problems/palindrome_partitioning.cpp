#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct State {
  int start;
  vector<string> currentList;
};

bool isPalindrome(const string& s, int lo, int hi) {
  while (lo <= hi) {
    if(s[lo++] != s[hi--]) {
      return false;
    }
  }
  return true;
}

// dfs
void generateAllPalindromeSets(
    const string& s,
    int start,
    vector<string>& currentList,
    vector<vector<string>>& result) {
  int n = s.length();

  if (start == n) {
    result.push_back(currentList);
  }

  for (int end = start; end < n; end ++) {
    if (!isPalindrome(s, start, end)) {
      continue;
    }
    int length = end - start + 1;
    currentList.push_back(s.substr(start, length));
    generateAllPalindromeSets(s, end + 1, currentList, result);
    currentList.pop_back();
  }
}

vector<vector<string>> palindromePartition(string& s) {
  vector<vector<string>> result;
  vector<string> currentList;
  generateAllPalindromeSets(s, 0, currentList, result);
  return result;
}

void test(int testCase, vector<vector<string>> expected, vector<vector<string>> actual) {
  cout << "Test case " << testCase << ": ";
  if (actual == expected)
    cout << "Passed\n";
  else {
    cout << "Failed\nExpected: ";
    for (const auto& partition : expected) {
      cout << "{ ";
      for (const auto& s : partition) cout << s << ' ';
      cout << "} ";
    }
    cout << "\nActual: ";
    for (const auto& partition : actual) {
      cout << "{ ";
      for (const auto& s : partition) cout << s << ' ';
      cout << "} ";
    }
    cout << endl;
  }
}

int main() {
  // Test case 1
  string s1 = "aab";
  vector<vector<string>> expected1{{"a","a","b"},{"aa","b"}};
  test(0, expected1, palindromePartition(s1));

  // Test case 2
  string s2 = "aba";
  vector<vector<string>> expected2{{"a","b","a"},{"aba"}};
  test(1, expected2, palindromePartition(s2));

  // Add more test cases here...

  return 0;
}