#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

enum State {
  Stop,
  Start
};

// {function id}:{"start" | "end"}:{timestamp}
struct Log {
  int id;
  State state;
  int timestamp;

  Log(const string& log) {
    stringstream ss(log);

    string buffer;

    getline(ss, buffer, ':');
    id = stoi(buffer);

    getline(ss, buffer, ':');
    state = (buffer == "start" ? State::Start : State::Stop);

    getline(ss, buffer);
    timestamp = stoi(buffer);
  }
};

vector<int> ExclusiveTime(int n, vector<string> logs) {
  vector<int> result(n);
  stack<Log> st;

  for (const auto& content : logs) {
    Log log(content);
    if (log.state == State::Start) {
      st.push(log);
    } else {
      // we get a closing state we know that the interval closes the most recent
      // process because we can only have 1 on a single core processor
      auto start = st.top(); st.pop();

      // add the duration to current log id
      result[log.id] += log.timestamp - start.timestamp + 1;

      // subtract overlap of the current log from the previous process
      if (!st.empty()) {
        result[st.top().id] -= (log.timestamp - start.timestamp + 1);
      }
    }
  }

  return result;
}

// The helper function
void test(int testCase, vector<int> expected, vector<int> actual) {
  std::cout << "Test case " << testCase << ": ";
  if (actual == expected)
    std::cout << "Passed";
  else {
    std::cout << "Failed (expected = ";
    for (int i = 0; i < expected.size(); i++) {
        std::cout << expected[i] << " ";
    }
    std::cout << ", actual = ";
    for (int i = 0; i < actual.size(); i++) {
        std::cout << actual[i] << " ";
    }
    std::cout << ")";
  }
  std::cout << std::endl;
}

int main() {
  // Test case 1
  vector<string> logs1 = {"0:start:0","0:end:1"};
  test(1, vector<int>{2}, ExclusiveTime(1, logs1));

  // Test case 2
  vector<string> logs2 = {"0:start:0","1:start:2","1:end:5","0:end:6"};
  test(2, vector<int>{3, 4}, ExclusiveTime(2, logs2));

  // Add more test cases here...
  vector<string> log3 = {"0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"};
  test(3, vector<int>{3, 4}, ExclusiveTime(2, logs2));

  return 0;
}
