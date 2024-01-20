#include <iostream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

void printCount(unordered_map<char, int>& graph) {

  for (const auto& count : graph) {
    std::cout << count.first << ": " << count.second << std::endl;
  }
}

vector<char> FindCompilationOrder(vector<vector<char>> dependencies) {

  vector<char> order;

  unordered_map<char, vector<char>> dependencyGraph;
  unordered_map<char, int> dependencyCount;
  for (const auto& dependencyList : dependencies) {
    dependencyGraph[dependencyList[0]] = {};
    dependencyGraph[dependencyList[1]] = {};

    dependencyCount[dependencyList[0]] = 0;
    dependencyCount[dependencyList[1]] = 0;
  }

  for (const auto& dependencyList : dependencies) {
    dependencyGraph[dependencyList[1]].push_back(dependencyList[0]);
  }

  for (const auto& classDependencyCount: dependencyGraph) {
    std::cout << classDependencyCount.first << ": ";
    for (const auto& dependentsOfClass : classDependencyCount.second) {
      std::cout << dependentsOfClass << ",";
    }
    std::cout << std::endl;
  }

  for (const auto& dependencyList : dependencies) {
    dependencyCount[dependencyList[0]] ++;
  }
  printCount(dependencyCount);

  queue<char> q;
  for (const auto& classDependencyCount: dependencyCount) {
    if (classDependencyCount.second == 0) {
      q.push(classDependencyCount.first);
    }
  }

  while (!q.empty()) {
    char className = q.front(); q.pop();
    order.push_back(className);

    for (const auto& dependentOfClassName: dependencyGraph.at(className)) {
      dependencyCount[dependentOfClassName]--;
      if (dependencyCount[dependentOfClassName] == 0) {
        q.push(dependentOfClassName);
      }
    }
  }

  return order;
}

void test(int testCase, vector<char> expected, vector<char> actual) {
    cout << "Test case " << testCase << ": ";
    if (actual == expected)
        cout << "Passed";
    else
        cout << "Failed (expected = ";
        for(char c : expected) {
            cout << c << " ";
        }
        cout << ", actual = ";
        for(char c : actual) {
            cout << c << " ";
        }
        cout << ")";
    cout << endl;
}

int main() {
  // Test case 1
  vector<vector<char>> dependencies1 = {{'A', 'B'}, {'B', 'C'}, {'C', 'D'}};
  vector<char> expected1 = {'A', 'B', 'C', 'D'};  // Assuming this order, adjust as needed.
  vector<char> actual1 = FindCompilationOrder(dependencies1);
  test(1, expected1, actual1);

  // Test case 2
  vector<vector<char>> dependencies2 = {{'A', 'D'}, {'B', 'C'}};
  vector<char> expected2 = {'A', 'D', 'B', 'C'};  // Assuming this order, adjust as needed.
  vector<char> actual2 = FindCompilationOrder(dependencies2);
  test(2, expected2, actual2);

  // Add more test cases here...

  return 0;
}
