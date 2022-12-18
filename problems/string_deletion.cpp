#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>

class Solution {
 public:
  int Delete(std::string query, std::unordered_set<std::string>& dictionary) {
    std::queue<std::string> queue;
    std::unordered_set<std::string> queue_elements;
    queue.push(query);
    queue_elements.insert(query);

    int result = -1;
    while(!queue.empty()) {
      auto s = queue.front();
      queue.pop();

      if (dictionary.find(s) != dictionary.end()) {
        result = query.length() - s.length();
        break;
      }

      for (int i = 0; i < s.length(); i++) {
        std::string sub = s.substr(0, i) + s.substr(i + 1, s.length());
        if (queue_elements.find(sub) == queue_elements.end() && sub.length() > 0) {
          queue.push(sub);
          queue_elements.insert(sub);
        }
      }
    }

    return result;
  }
};

int main(int argc, char** argv) {

  std::unordered_set<std::string> dictionary { "aaa", "aa", "a" };
  std::string query = "abc";

  Solution sol;
  int res = sol.Delete(query, dictionary);
  std::cout << res << std::endl;
  return 0;
}