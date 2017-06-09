// https://leetcode.com/problems/set-matrix-zeroes

// O(n+m) memory

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix.front().empty()) return;

        vector<bool> rows(matrix.size()), cols(matrix.front().size());
        for (int i = 0; i < matrix.size(); ++i)
            for (int j = 0; j < matrix[i].size(); ++j)
                if (matrix[i][j] == 0) rows[i] = true, cols[j] = true;

        for (int i = 0; i < matrix.size(); ++i)
            for (int j = 0; j < matrix[i].size(); ++j)
                if (rows[i] || cols[j]) matrix[i][j] = 0;
    }
};

// Constant memory

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;

        bool firstrow = false, firstcol = false;

        for (int i = 0; i < matrix.size(); ++i)
            firstcol |= matrix[i][0] == 0;

        for (int j = 0; j < matrix[0].size(); ++j)
            firstrow |= matrix[0][j] == 0;

        for (int i = 1; i < matrix.size(); ++i)
            for (int j = 1; j < matrix[i].size(); ++j)
                if (matrix[i][j] == 0) matrix[i][0] = matrix[0][j] = 0;

        for (int i = 1; i < matrix.size(); ++i)
            for (int j = 1; j < matrix[i].size(); ++j)
                if (matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;

        if (firstcol)
            for (int i = 0; i < matrix.size(); ++i)
                matrix[i][0] = 0;

        if (firstrow)
            for (int j = 0; j < matrix[0].size(); ++j)
                matrix[0][j] = 0;
    }
};
