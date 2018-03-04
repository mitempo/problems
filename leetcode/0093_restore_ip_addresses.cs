// https://leetcode.com/problems/restore-ip-addresses/description/

public class Solution {
    public IList<string> RestoreIpAddresses(string s) {
        return ipaddr(s, 4, "").ToArray();
    }

    public IEnumerable<string> ipaddr(string s, int nOctets, string acc) {
        if (nOctets == 0)
        {
            if (s == "") yield return acc;
            yield break;
        }

        for (int i = 1; i <= s.Length && i < 4; ++i)
        {
            string fst = s.Substring(0, i);
            if (fst.StartsWith("0") && fst.Length > 1 || !int.TryParse(fst, out int o) || o < 0 || o > 255) continue;
            foreach (string e in ipaddr(s.Substring(i), nOctets - 1, acc + (acc == "" ? "" : ".") + fst))
                yield return e;
        }
    }
}
