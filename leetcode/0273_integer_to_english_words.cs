// https://leetcode.com/problems/integer-to-english-words/description/

public class Solution {
    public Dictionary<int, string> ones = new Dictionary<int, string>
    {
        {1, "One"},
        {2, "Two"},
        {3, "Three"},
        {4, "Four"},
        {5, "Five"},
        {6, "Six"},
        {7, "Seven"},
        {8, "Eight"},
        {9, "Nine"},
        {10, "Ten"},
        {11, "Eleven"},
        {12, "Twelve"},
        {13, "Thirteen"},
        {14, "Fourteen"},
        {15, "Fifteen"},
        {16, "Sixteen"},
        {17, "Seventeen"},
        {18, "Eighteen"},
        {19, "Nineteen"},
    };
    
    public Dictionary<int, string> tens = new Dictionary<int, string>
    {
        {2, "Twenty"},
        {3, "Thirty"},
        {4, "Forty"},
        {5, "Fifty"},
        {6, "Sixty"},
        {7, "Seventy"},
        {8, "Eighty"},
        {9, "Ninety"},
    };
    
    public string NumberToWords(int num) {
        return num == 0 ? "Zero" : n2w(num);
    }

    public string n2w(int num) {
        if (num < 20) return ones[num];
        if (num < 100) return tens[num / 10] + (num % 10 != 0 ? $" {ones[num % 10]}" : "");
        if (num < 1000) return $"{ones[num / 100]} Hundred" + (num % 100 != 0 ? $" {n2w(num % 100)}" : "");
        if (num < 1000000) return $"{n2w(num / 1000)} Thousand" + (num % 1000 != 0 ? $" {n2w(num % 1000)}" : "");
        if (num < 1000000000) return $"{n2w(num / 1000000)} Million" + (num % 1000000 != 0 ? $" {n2w(num % 1000000)}" : "");
        return $"{n2w(num / 1000000000)} Billion" +(num % 1000000000 != 0 ? $" {n2w(num % 1000000000)}" : "");
    }
}
