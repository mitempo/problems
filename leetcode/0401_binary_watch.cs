// https://leetcode.com/problems/binary-watch/description/

public class Solution {
    public bool next_combination(IList<int> p, int n)
    {
        int i = p.Count - 1;
        
        for (; i >= 0 && ++p[i] >= n - (p.Count - 1 - i); --i)
            ;
        
        if (i < 0) return false;
        
        for (++i; i < p.Count; ++i)
            p[i] = i == 0 ? 0 : p[i-1] + 1;
        
        return true;
    }

    public IList<string> ReadBinaryWatch(int num) {
        IList<string> result = new List<string>();
        var p = Enumerable.Range(0, num).ToArray();
        
        do
        {
            int hours = p.Where(e => e < 4).Aggregate(0, (acc, e) => acc + (int)Math.Pow(2, e));
            int mins = p.Where(e => e >= 4).Aggregate(0, (acc, e) => acc + (int)Math.Pow(2, e - 4));
            
            if (hours > 11 || mins > 59) continue;
            
            result.Add($"{hours}:{mins:D2}");
        }
        while (next_combination(p, 10));
            
        return result;
    }
}
