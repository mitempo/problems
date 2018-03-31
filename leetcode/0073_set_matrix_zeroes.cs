// https://leetcode.com/problems/set-matrix-zeroes/description/

public class Solution {
    public void SetZeroes(int[,] matrix) {
        bool zeroesInFirstCol = Enumerable.Range(0, matrix.GetLength(0)).Any(i => matrix[i,0] == 0);
        bool zeroesInFirstRow = Enumerable.Range(0, matrix.GetLength(1)).Any(i => matrix[0,i] == 0);
        
        for (int i = 1; i < matrix.GetLength(0); ++i)
            for (int j = 1; j < matrix.GetLength(1); ++j)
                if (matrix[i,j] == 0)
                    matrix[i,0] = matrix[0,j] = 0;

        for (int i = 1; i < matrix.GetLength(0); ++i)
            if (matrix[i,0] == 0)
                for (int j = 1; j < matrix.GetLength(1); ++j)
                    matrix[i,j] = 0;

        for (int j = 1; j < matrix.GetLength(1); ++j)
            if (matrix[0,j] == 0)
                for (int i = 1; i < matrix.GetLength(0); ++i)
                    matrix[i,j] = 0;

        if (zeroesInFirstCol)
            for (int i = 0; i < matrix.GetLength(0); ++i)
                matrix[i,0] = 0;

        if (zeroesInFirstRow)
            for (int j = 0; j < matrix.GetLength(1); ++j)
                matrix[0,j] = 0;
    }
}
