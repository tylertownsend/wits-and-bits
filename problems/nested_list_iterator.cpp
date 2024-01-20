#include <iostream>
#include <vector>
using namespace std;



// The following class is used for creating nested lists.
// You should not implement this class or speculate about its implementation.
class NestedDirectory {
  vector<NestedDirectory *> list;
  int file;

public:
  // Constructor initializes an empty nested list.

  NestedDirectory() {
    this->file = -1;
  }

  // Constructor initializes a single integer.
  NestedDirectory(int value) {
    this->file = value;
  }

  // @return true if this NestedDirectory holds a single integer, rather than a nested list.
  bool isFile() {
    if (this->file != -1)
      return true;
    return false;
  }

  // @return the single integer that this NestedDirectory holds, if it holds a single integer
  // Return null if this NestedDirectory holds a nested list
  int getFile() {
    return (this->file);
  }

  // Set this NestedDirectory to hold a single integer.
  void setFile(int value) {
    this->list.clear();
    this->file = value;
  }

  // Set this NestedDirectory to hold a nested list and adds a nested integer to it.
  void add(NestedDirectory *ni) {
    if (this->file != -1) {
      this->list.push_back(new NestedDirectory((this->file)));
      this->file = -1;
    }
    this->list.push_back(ni);
  }

  // @return the nested list that this NestedDirectory holds, if it holds a nested list
  // Return null if this NestedDirectory holds a single integer
  vector<NestedDirectory *> getList() {
    return list;
  }
  ~NestedDirectory() {
    //delete this->file;
    for (int i = 0; i < list.size(); i++) {
        delete this->list[i];
    }
    this->list.clear();
  }
};

class NestedIterator {
public:
  NestedIterator(vector<NestedDirectory *> nestedList)
  {
    // Write your code here
  }

  bool HasNext()
  {
  }

  int Next()
  {
  }
};


void test(int testCase, vector<int> expected, vector<int> actual) {
    std::cout << "Test case " << testCase << ": ";
    if (actual == expected)
        std::cout << "Passed";
    else {
        std::cout << "Failed (expected = ";
        for (const int& e : expected) std::cout << e << " ";
        std::cout << ", actual = ";
        for (const int& a : actual) std::cout << a << " ";
        std::cout << ")";
    }
    std::cout << std::endl;
}

int main() {
  return 0;
}
