// https://leetcode.com/problems/reconstruct-itinerary

public class Solution {
    private int len = 0;
    private List<string> reco = null;

    public IList<string> FindItinerary(string[,] tickets) {
        IDictionary<string, List<string>> idcs = new Dictionary<string, List<string>>();

        len = tickets.GetLength(0) + 1;

        for (int i = 0; i < tickets.GetLength(0); ++i)
        {
            string src = tickets[i,0];
            if (idcs.TryGetValue(src, out var hash))
			{
			    int ix = hash.BinarySearch(tickets[i,1]);
                hash.Insert(ix >= 0 ? ix : ~ix, tickets[i,1]);
	        }
            else
                idcs[src] = new List<string>{tickets[i,1]};
        }

        bt(idcs, new Dictionary<string, HashSet<int>>(), new List<string>{"JFK"});

        return reco;
    }
    
    void bt(IDictionary<string, List<string>> idcs, Dictionary<string, HashSet<int>> used, List<string> soFar)
    {
        if (reco != null) return;
        if (soFar.Count == len) { reco = soFar; return; }
        
        string last = soFar[soFar.Count-1];
        
        if (!idcs.ContainsKey(last) || idcs[last].Count == 0) return;
        
		for (int i = 0; i < idcs[last].Count; ++i)
        {
            if (used.TryGetValue(last, out var hs) && hs.Contains(i)) continue;
		    string cand = idcs[last][i];
            if (reco != null && string.Compare(reco[soFar.Count], cand) < 0) continue;
            var newUsed = used.ToDictionary(pair => pair.Key, pair => new HashSet<int>(pair.Value));
            if (!newUsed.ContainsKey(last)) newUsed[last] = new HashSet<int>{i}; else newUsed[last].Add(i);
            bt(idcs, newUsed, soFar.Concat(new[]{cand}).ToList());
        }
    }
}
