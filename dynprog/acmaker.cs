using System;
using System.Collections.Generic;
using System.Linq;
using static System.Console;

public class Solver
{
    private string acronym;
    private Tuple<char, int>[] definition;

    private int[,,] d;

    public Solver(string a, IEnumerable<string> defn)
    {
        acronym = a;
        definition = defn.SelectMany((e, i) => e.Select(c => Tuple.Create(c, i))).ToArray();

        d = new int[a.Length + 1, definition.Length + 1, definition[definition.Length - 1].Item2 + 2];

        for (int i = 0; i < d.GetLength(0); ++i)
        for (int j = 0; j < d.GetLength(1); ++j)
        for (int k = 0; k < d.GetLength(2); ++k)
            d[i,j,k] = -1;

    }

    private int Solve(int ia, int id, int lastMatchIndex)
    {
        if (ia == 0) return lastMatchIndex == 0 ? 1 : 0;
        if (id == 0) return 0;

        int r = d[ia,id,lastMatchIndex];
        if (r != -1) return r;

        return d[ia,id,lastMatchIndex] =
            Solve(ia, id-1, lastMatchIndex) +
            (acronym[ia-1] == definition[id-1].Item1 && lastMatchIndex - definition[id-1].Item2 <= 1 ? Solve(ia-1, id-1, definition[id-1].Item2) : 0);
    }

    public int Solve()
    {
        return Solve(acronym.Length, definition.Length, definition[definition.Length - 1].Item2 + 1);
    }
}

public class Program
{
    public static int Main()
    {
        for ( ; ; )
        {
            int n = int.Parse(ReadLine());

            if (n == 0) break;

            IList<string> stopWords =
                Enumerable.Range(0, n)
                .Select(_ => ReadLine().ToLowerInvariant())
                .ToArray();

            var testCases =
                Enumerable.Range(0, int.MaxValue)
                .Select(_ => ReadLine().ToLowerInvariant())
                .TakeWhile(s => s != null && s != "last case")
                .Select(s => s.Split(new[]{ ' ' }, StringSplitOptions.RemoveEmptyEntries))
                .Select(words => new { Acronym = words[0], Definition = words.Skip(1).Except(stopWords) })
                .ToArray();

            foreach (var testCase in testCases)
            {
                int solution = new Solver(testCase.Acronym, testCase.Definition).Solve();

                if (solution == 0)
                    WriteLine($"{testCase.Acronym.ToUpperInvariant()} is not a valid abbreviation");
                else
                    WriteLine($"{testCase.Acronym.ToUpperInvariant()} can be formed in {solution} ways");
            }
        }
         
        return 0;
    }
}
