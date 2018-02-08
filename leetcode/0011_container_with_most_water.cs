// https://leetcode.com/problems/container-with-most-water

public class Solution {
    public int MaxArea(int[] height) {
        int maxvol = 0;

        int il = 0;
        int ir = height.Length - 1;

        while (il < ir)
        {
            int hl = height[il];
            int hr = height[ir];

            maxvol = Math.Max(maxvol, Math.Min(hl, hr) * (ir - il));

            if (hl < hr)
            {
                int i = il + 1;
                for (; i < ir && height[i] <= hl; ++i)
                    ;
                il = i;
            }
            else
            {
                int i = ir - 1;
                for (; i > il && height[i] <= hr; --i)
                    ;
                ir = i;
            }
        }

        return maxvol;
    }
}
