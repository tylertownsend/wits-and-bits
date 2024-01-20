#include <iostream>
#include <stack>
#include <string>

using namespace std;

void test(int testCase, string expected, string actual) {
  std::cout << "Test case " << testCase << ": ";
  if (actual == expected)
    std::cout << "Passed";
  else
    std::cout << "Failed (expected = " << expected << ", actual = " << actual << ")";
  std::cout << std::endl;
}


string MinRemoveParentheses(string s) {
  stack<char> forward;
  stack<char> back;

  int balance = 0;

  for (char c : s) {
    if (c == ')') {
      if (balance <= 0) {
        continue;
      } else {
        balance--;
      }
    }

    forward.push(c);
    if (c == '(') {
      balance++;
    }
  }

  while (!forward.empty()) {
    char curr = forward.top(); forward.pop();

    if (balance > 0 && curr == '(') {
      // throw away the opening parenthesis
      balance--;
    } else {
      back.push(curr);
    }
  }

  string result = "";
  while (!back.empty()) {
    result += back.top();
    back.pop();
  }

  return result;
}

int main() {
  // Test case 1
  // string input1 = "a(b)";
  // string expected1 = "a(b)";
  // test(1, expected1, MinRemoveParentheses(input1));

  // // Test case 2
  // string input2 = "a(b";
  // string expected2 = "ab";
  // test(2, expected2, MinRemoveParentheses(input2));

  // // Test case 3
  // string input3 = "a)b(c)d";
  // string expected3 = "ab(c)d";
  // test(3, expected3, MinRemoveParentheses(input3));

  // Test case 4
  string input4 = "a)b()c)d";
  string expected4 = "ab()cd";
  test(4, expected4, MinRemoveParentheses(input4));

  // Add more test cases here...

  return 0;
}
