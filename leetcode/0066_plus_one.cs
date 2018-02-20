// https://leetcode.com/problems/plus-one/description/

public class Solution {
    public int[] PlusOne(int[] digits) {
        int[] result = digits.ToArray();

        ++result[result.Length - 1];
        int c = 0;
        
        for (int i = result.Length - 1; i >= 0; --i)
        {
            result[i] += c;
            c = result[i] / 10;
            result[i] %= 10;
            if (c == 0) break;
        }
        
        if (c != 0)
            result = new[]{1}.Concat(result).ToArray();
        
        return result;
    }
}
