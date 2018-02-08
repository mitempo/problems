public class Solution {
    public int[] TwoSum(int[] numbers, int target) {
        int i = 0, j = numbers.Length - 1;
        
        while (j > i)
        {
            int s = numbers[i] + numbers[j];
            if (s == target) return new[]{i + 1, j + 1};
            if (s > target) --j;
            if (s < target) ++i;
        }
        
        return new int[]{};
    }
}
