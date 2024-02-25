#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#include <algorithm>
#include <numeric>
using namespace std;

// generate
// cage --> solo, 1-4-3 / 4
// 


struct Node {
    int value;
    Node* right;
    Node* down;
    Node() : value(0), right(nullptr), down(nullptr) {}
};


bool isValid(vector<unordered_set<int>>& usedRows, vector<unordered_set<int>>& usedCols, int row, int col, int value) {
    return usedRows[row].find(value) == usedRows[row].end() && usedCols[col].find(value) == usedCols[col].end();
}

bool fillGrid(vector<vector<Node*>>& grid, vector<unordered_set<int>>& usedRows, vector<unordered_set<int>>& usedCols, int row, int col, int n) {
    if (col == n) {
        row++;
        col = 0;
    }
    if (row == n) return true; // Successfully filled the grid

    vector<int> values(n);
    iota(values.begin(), values.end(), 1); // Fill values with 1 to n
    shuffle(values.begin(), values.end(), default_random_engine(random_device{}()));

    for (int val : values) {
        if (isValid(usedRows, usedCols, row, col, val)) {
            grid[row][col]->value = val;
            usedRows[row].insert(val);
            usedCols[col].insert(val);

            if (fillGrid(grid, usedRows, usedCols, row, col + 1, n)) return true;

            // Backtrack
            usedRows[row].erase(val);
            usedCols[col].erase(val);
        }
    }
    return false;
}

int main() {
    int n;

    do {
        cout << "Enter the size of your array (or -1 to exit): ";
        cin >> n;

        // Creates Vector Grid Container
        vector<vector<Node*>> grid(n, vector<Node*>(n, nullptr));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = new Node();
            }
        }

        vector<unordered_set<int>> usedRows(n), usedCols(n);
        if (!fillGrid(grid, usedRows, usedCols, 0, 0, n)) {
            cout << "Failed to generate a valid grid." << endl;
        }
        else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cout << grid[i][j]->value << " ";
                }
                cout << endl;
            }
        }

        // Cleanup
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                delete grid[i][j];
            }
        }
    } while (n != -1);
    return 0;
}
