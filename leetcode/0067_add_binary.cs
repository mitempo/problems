// https://leetcode.com/problems/add-binary/description/

public class Solution {
    public string AddBinary(string a, string b) {
        int i = a.Length - 1;
        int j = b.Length - 1;
        
        int c = 0;
        string result = "";
        
        for (; i >= 0 || j >= 0 || c != 0; --i, --j)
        {
            int r =
                ((i >= 0 ? a[i] : '0') == '1' ? 1 : 0) +
                ((j >= 0 ? b[j] : '0') == '1' ? 1 : 0) +
                c;
            
            c = r / 2;
            r %= 2;
            
            result = (r == 0 ? '0' : '1') + result;
        }
        
        return result;
    }
}
