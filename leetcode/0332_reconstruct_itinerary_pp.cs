public class Solution {
    private List<string> reco = new List<string>();
    IDictionary<string, List<string>> idcs = new Dictionary<string, List<string>>();

    public IList<string> FindItinerary(string[,] tickets) {
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

        bt("JFK");

        reco.Reverse();
        return reco;
    }
    
    void bt(string src)
    {
        while (idcs.TryGetValue(src, out List<string> dsts) && dsts.Count > 0)
        {
            string dst = dsts[0];
            dsts.RemoveAt(0);
            bt(dst);
        }

        reco.Add(src);
    }
}
