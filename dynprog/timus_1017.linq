<Query Kind="Program">
  <Reference>&lt;RuntimeDirectory&gt;\System.Web.dll</Reference>
  <Namespace>System.Collections.Concurrent</Namespace>
</Query>

ConcurrentDictionary<Tuple<int, int, int>, int> cache = new ConcurrentDictionary<Tuple<int, int, int>, int>();

int LadderRec(int _n, int _min, int _level)
{
    return cache.GetOrAdd(
        Tuple.Create(_n, _min, _level),
        uncurriedArgs => // This is, BTW, one place where C# sucks compared to Python or ML/F#/Haskell: you can't just say (n, min, level)
        {
            int n     = uncurriedArgs.Item1;
            int min   = uncurriedArgs.Item2;
            int level = uncurriedArgs.Item3;

            return n == 0 && level >= 2 ? 1 :
                   n < min              ? 0 :
                                          Enumerable.Range(min, n - min + 1).Sum(i => LadderRec(n - i, i + 1, level + 1));
        });
}

int Ladder(int n)
{
    return LadderRec(n, 1, 0);
}

void Main()
{
    Ladder(212).Dump();
}
