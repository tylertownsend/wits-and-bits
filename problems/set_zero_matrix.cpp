#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> SetMatrixZeros(vector<vector<int>>& mat) {
  int m = mat.size();
  int n = mat[0].size();
  vector<int> rows(m, 0);
  vector<int> cols(n, 0);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (mat[i][j] == 0) {
        rows[i] = 1;
        cols[j] = 1;
      }
    }
  }


  auto transformedMatrix(mat);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (rows[i] == 1 || cols[j] == 1) {
        transformedMatrix[i][j] = 0;
      }
    }
  }
  return transformedMatrix;
}

void test(int testCase, vector<vector<int>> expected, vector<vector<int>> actual) {
    cout << "Test case " << testCase << ": ";
    if (actual == expected)
        cout << "Passed";
    else {
        cout << "Failed\n";
        cout << "Expected:\n";
        for (const auto &row : expected) {
            for (int num : row)
                cout << num << " ";
            cout << "\n";
        }
        cout << "Actual:\n";
        for (const auto &row : actual) {
            for (int num : row)
                cout << num << " ";
            cout << "\n";
        }
    }
    cout << endl;
}

int main() {
    // Test case 1
    vector<vector<int>> mat1 = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 8, 9}
    };
    vector<vector<int>> expected1 = {
        {1, 0, 3},
        {0, 0, 0},
        {7, 0, 9}
    };
    test(1, expected1, SetMatrixZeros(mat1));

    // Test case 2
    vector<vector<int>> mat2 = {
        {0, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    vector<vector<int>> expected2 = {
        {0, 0, 0},
        {0, 5, 6},
        {0, 8, 9}
    };
    test(2, expected2, SetMatrixZeros(mat2));

    // Add more test cases here...

    return 0;
}
