#include <iostream>
#include <string>
#include <vector>

using namespace std;

int Calculator(const string &expression) {

  // process the string from l -> r
  // cases:
  // 1. digit: continue until whole digit is found (stoi)
  // 2. operand: 
}

void test(int testCase, int expected, int actual) {
    std::cout << "Test case " << testCase << ": ";
    if (actual == expected)
        std::cout << "Passed";
    else
        std::cout << "Failed (expected = " << expected << ", actual = " << actual << ")";
    std::cout << std::endl;
}

int main() {
    // Test case 1
    test(1, 5, Calculator("2 + 3"));
    
    // Test case 2
    test(2, 3, Calculator("5 - 2"));
    
    // Test case 3
    test(3, -1, Calculator("-1"));
    
    // Test case 4
    test(4, -5, Calculator("-2 - 3"));
    
    // Test case 5
    test(5, 15, Calculator("3 + 4 + 8"));
    
    // Test case 6
    test(6, 14, Calculator("3 + (4 + 8) - 1"));
    
    // Test case 7
    test(7, 2, Calculator("1 - (3 + 4) + 8"));
    
    // Test case 8
    test(8, 9, Calculator("2 + 3 + 4"));
    
    // Add more test cases here...

    return 0;
}
