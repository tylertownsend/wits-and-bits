#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// Helper function to print vector<int>
string vecToString(const vector<int>& v) {
    string res = "{";
    for (int i = 0; i < v.size(); ++i) {
        res += to_string(v[i]);
        if (i != v.size() - 1) res += ", ";
    }
    res += "}";
    return res;
}

vector<int> FindOrder(int n, vector<vector<int>> preRequisites) {
  vector<int> order;
  vector<vector<int>> depGraph(n + 1, vector<int>());
  for (const auto& preRequisite : preRequisites) {
    depGraph[preRequisite[1]].push_back(preRequisite[0]);
  }
  for(int i = 1; i <= n; i++) {
    std::cout << i << ": ";
    std::cout << vecToString(depGraph[i]) << std::endl;
    std::cout << std::endl;
  }

  vector<int> depCount(n+1, 0);
  for (const auto& preRequisite : preRequisites) {
    depCount[preRequisite[0]]++;
  }
  std::cout << vecToString(depCount) << std::endl;

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (depCount[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int curr = q.front(); q.pop();
    order.push_back(curr);

    for (const int child: depGraph[curr]) {
      depCount[child]--;
      if (depCount[child] == 0) {
        q.push(child);
      }
    }
  }
  return order;
}

// Fixed test function
void test(int testCase, vector<int> expected, vector<int> actual) {
    cout << "Test case " << testCase << ": ";
    if (actual == expected)
        cout << "Passed";
    else
        cout << "Failed (expected = " << vecToString(expected) << ", actual = " << vecToString(actual) << ")";
    cout << endl;
}

// Main function for testing
int main() {
    // Test case 1
    vector<vector<int>> prerequisites1 = {{2,1}};
    test(1, {1,2}, FindOrder(2, prerequisites1));

    // Test case 2
    vector<vector<int>> prerequisites2 = {{2,1},{3,1},{4,2},{4,3}};
    test(2, {1, 2, 3, 4}, FindOrder(4, prerequisites2));  // One of the valid orderings

    // Add more test cases here...

    return 0;
}
