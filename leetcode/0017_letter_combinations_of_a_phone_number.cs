// https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/

public class Solution {
    public Dictionary<char, char[]> letters = new Dictionary<char, char[]>{
        ['2'] = new[]{'a', 'b', 'c'},
        ['3'] = new[]{'d', 'e', 'f'},
        ['4'] = new[]{'g', 'h', 'i'},
        ['5'] = new[]{'j', 'k', 'l'},
        ['6'] = new[]{'m', 'n', 'o'},
        ['7'] = new[]{'p', 'q', 'r', 's'},
        ['8'] = new[]{'t', 'u', 'v'},
        ['9'] = new[]{'w', 'x', 'y', 'z'},
        ['0'] = new[]{' '},
    };

    public IList<string> LetterCombinations(string digits) {
        return CartProd(digits.Replace("1", "").Select(c => letters[c])).Where(e => e.Any()).Select(e => new string(e.ToArray())).ToArray();
    }
    
    public IEnumerable<IEnumerable<char>> CartProd(IEnumerable<IEnumerable<char>> vals)
    {
        var firstList = vals.FirstOrDefault();
        if (firstList == null){
            yield return Enumerable.Empty<char>();
            yield break;
        }

        foreach (char c in firstList)
            foreach (var e in CartProd(vals.Skip(1)))
                yield return new[]{c}.Concat(e);
    }
}
