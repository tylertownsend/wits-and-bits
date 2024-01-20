#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

std::string RemoveDuplicates(std::string str) {
  stack<char> st;

  for (const char c : str) {
    if (st.empty() || st.top() != c) {
      st.push(c);
    } else {
      st.pop();
    }
  }

  string result = "";
  while (!st.empty()) {
    result = st.top() + result;
    st.pop();
  }
  return result;
}

void test(int testCase, std::string expected, std::string actual) {
  std::cout << "Test case " << testCase << ": ";
  if (actual == expected)
    std::cout << "Passed";
  else
    std::cout << "Failed (expected = " << expected << ", actual = " << actual << ")";
  std::cout << std::endl;
}

int main() {
  // Test case 1
  std::string input1 = "aabbcc";
  std::string expected1 = "";
  test(1, expected1, RemoveDuplicates(input1));

  // Test case 2
  std::string input2 = "aabcc";
  std::string expected2 = "b";
  test(2, expected2, RemoveDuplicates(input2));

  // Test case 3
  std::string input3 = "abcde";
  std::string expected3 = "abcde";
  test(3, expected3, RemoveDuplicates(input3));

  // Add more test cases here...

  return 0;
}
