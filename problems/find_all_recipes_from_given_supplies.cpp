#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

vector<string> FindAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
  vector<string> availableRecipes;

  unordered_set<string> suppliedIngredients;

  // the recipes are the inverted roots of each graph
  unordered_map<string, vector<string>> graph;
  for (int i = 0; i < recipes.size(); i++) {
    for (const string& ingredient : ingredients[i]) {
      graph[ingredient].push_back(recipes[i]);
    }
  }

  // number of ingoing edges is the size of the ingredients
  // to make the recipe
  unordered_map<string, int> inDegree;
  for (int i = 0; i < recipes.size(); i++) {
    inDegree[recipes[i]] = ingredients[i].size();
  }

  // all supplies have 0 dependencies
  queue<string> q;
  for (const string& supply : supplies) {
    if (suppliedIngredients.find(supply) != suppliedIngredients.end()) {
      continue;
    }
    q.push(supply);
  }

  while (!q.empty()) {
    auto supply = q.front(); q.pop();

    for (const string& dep: graph[supply]) {
      if (suppliedIngredients.find(supply) != suppliedIngredients.end()) {
        continue;
      }
      inDegree[dep]--;
      if (inDegree[dep] == 0) {
        q.push(dep);
      }
    }
  }

  for (const string& recipe : recipes) {
    if (inDegree[recipe] == 0) {
      availableRecipes.push_back(recipe);
    }
  }
  return availableRecipes;
}

void test(int testCase, vector<string> expected, vector<string> actual) {
    std::cout << "Test case " << testCase << ": ";
    if (actual == expected)
        std::cout << "Passed";
    else {
        std::cout << "Failed (expected = ";
        for(const auto& s : expected) std::cout << s << " ";
        std::cout << ", actual = ";
        for(const auto& s : actual) std::cout << s << " ";
        std::cout << ")";
    }
    std::cout << endl;
} 

int main() {
    // Test case 1
    vector<string> recipes1 = {"custard", "trifle"};
    vector<vector<string>> ingredients1 = {{"milk", "sugar"}, {"custard", "fruit"}};
    vector<string> supplies1 = {"milk", "sugar", "fruit"};
    vector<string> expected1 = {"custard"};
    test(1, expected1, FindAllRecipes(recipes1, ingredients1, supplies1));

    // Test case 2
    vector<string> recipes2 = {"custard", "trifle"};
    vector<vector<string>> ingredients2 = {{"milk", "sugar"}, {"custard", "fruit"}};
    vector<string> supplies2 = {"milk", "sugar", "fruit", "custard"};
    vector<string> expected2 = {"custard", "trifle"};
    test(2, expected2, FindAllRecipes(recipes2, ingredients2, supplies2));

    // Test case 3 - when recipes list each other as ingredients
    vector<string> recipes3 = {"custard", "trifle"};
    vector<vector<string>> ingredients3 = {{"trifle"}, {"custard"}};
    vector<string> supplies3 = {};
    vector<string> expected3 = {};
    test(3, expected3, FindAllRecipes(recipes3, ingredients3, supplies3));

    // Add more test cases as needed...

    return 0;
}
