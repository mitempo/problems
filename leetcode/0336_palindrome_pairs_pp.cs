// https://leetcode.com/problems/palindrome-pairs/description/

public class Solution {
    public IList<IList<int>> PalindromePairs(string[] words) {
        Dictionary<string, int> invs = words.Select((word, i) => (word: new string(word.Reverse().ToArray()), i: i)).ToDictionary(pair => pair.word, pair => pair.i);

        var r = new HashSet<(int, int)>();

        for (int i = 0; i < words.Length; ++i)
        {
            for (int n = 0; n <= words[i].Length; ++n)
            {
                if (IsPalindrome(words[i].Substring(0, n)) && invs.TryGetValue(n >= words[i].Length ? "" : words[i].Substring(n), out int j) && i != j)
                    r.Add((j, i));
                if (IsPalindrome(n >= words[i].Length ? "" : words[i].Substring(n)) && invs.TryGetValue(words[i].Substring(0, n), out j) && i != j)
                    r.Add((i, j));
            }
        }

        return r.Select(x => new[] { x.Item1, x.Item2 }).ToArray();
    }
    
    public bool IsPalindrome(string s)
    {
        return s == new string(s.Reverse().ToArray());
    }
}
