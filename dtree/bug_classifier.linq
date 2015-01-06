<Query Kind="Program">
  <Reference>&lt;RuntimeDirectory&gt;\System.Net.Http.dll</Reference>
  <Reference>&lt;RuntimeDirectory&gt;\System.Web.dll</Reference>
  <Namespace>System.Collections.Concurrent</Namespace>
  <Namespace>System.Net</Namespace>
  <Namespace>System.Net.Http</Namespace>
</Query>

// Solution for http://haskell98.blogspot.com/2014/12/blog-post_5.html

class DecisionTree {}

class Fork : DecisionTree
{
    public string Feature;                            // Name of the feature used for the decision in this node, e.g. "Наличие бомбурий"
    public Dictionary<string, DecisionTree> Branches; // Mapping of feature values into decision subtrees
}

class Leaf : DecisionTree
{
    public string Label; // Bug species
}

DecisionTree BuildDecisionTree(Dictionary<string, Dictionary<string, string>> matrix)
{
    if (matrix.Count == 0) throw new ArgumentException("Данных в исходной траблице недостаточно для построения дерева решений");

    string featureWithMaxEntropy = EnumerableEx.MaxBy(matrix, e => e.Value.ContainsValue("—") ? -1 : Entropy(e.Value.Select(answer => answer.Value))).Key;

    Dictionary<string, Dictionary<string, string>> reducedMatrix =
        matrix.Where(e => e.Key != featureWithMaxEntropy)
              .ToDictionary(pair => pair.Key, pair => pair.Value);

    Dictionary<string, List<string>> inverse =
        matrix[featureWithMaxEntropy].GroupBy(e => e.Value, e => e.Key)
                                     .ToDictionary(g => g.Key, g => g.ToList());
    
    return inverse.Count() == 1 ?
        BuildDecisionTree(reducedMatrix) :
        new Fork
        {
            Feature = featureWithMaxEntropy,
            Branches = inverse.ToDictionary
            (
                invpair => invpair.Key,
                invpair => invpair.Value.Count() == 1 ?
                    new Leaf { Label = invpair.Value.Single() } :
                    BuildDecisionTree
                    (
                        reducedMatrix.ToDictionary
                        (
                            p => p.Key,
                            p => p.Value.Where(pp => invpair.Value.Contains(pp.Key)).ToDictionary(pp => pp.Key, pp => pp.Value)
                        )
                    )
            )
        };
}

IEnumerable<string> Interact(DecisionTree tree)
{
    Leaf leaf = tree as Leaf;
    if (leaf != null) return new[]{ leaf.Label };

    Fork fork = (Fork)tree;
    Console.WriteLine(
        "Введите значение признака '{0}' ({1}) или '?' если значение неизвестно:",
        fork.Feature,
        string.Join(", ", fork.Branches.Keys.Where(e => e != "—").Select(e => string.Format("'{0}'", e))));
    string enteredFeatureValue = Console.ReadLine();

    HashSet<DecisionTree> branchesToFollow = new HashSet<DecisionTree>();
    if (fork.Branches.ContainsKey(enteredFeatureValue)) branchesToFollow.Add(fork.Branches[enteredFeatureValue]);
    if (fork.Branches.ContainsKey("—")) branchesToFollow.Add(fork.Branches["—"]);
    if (enteredFeatureValue == "?") branchesToFollow = new HashSet<DecisionTree>(fork.Branches.Values);

    return branchesToFollow.Select(t => Interact(t)).Aggregate(Enumerable.Empty<string>(), (a, b) => a.Union(b));
}

void Main()
{
    var classes = new[]
    {
        "Аурата сетуньская",
        "Десятилиньята лепая",
        "Семипунктата Коха",
        "Популий грыжомельский",
        "Гортикола филоперьевая"
    };

    var input = new Dictionary<string, string[]>
    {
        { "Наличие бомбурий",         new[]{ "Да",      "Да",        "Нет",       "Да",    "Нет"   }},
        { "Количество клептиконов",   new[]{ "1",       "1",         "0",         "3",     "5"     }},
        { "Цвет велория",             new[]{ "Красный", "Оранжевый", "Оранжевый", "—",     "Синий" }},
        { "Наличие пумпеля",          new[]{ "Нет",     "Да",        "Да",        "—",     "—"     }},
        { "Величина пумпеля",         new[]{ "—",       "Большой",   "Маленький", "—",     "—"     }},
        { "Возможность крокотания",   new[]{ "Нет",     "Нет",       "—",         "Да",    "Нет"   }},
        { "Возможность бульботания",  new[]{ "Нет",     "Да",        "—",         "Да",    "Нет"   }},
        { "Наличие дуков и труков",   new[]{ "—",       "—",         "—",         "—",     "Да"    }},
        { "Цвет лемпелей",            new[]{ "Жёлтый",  "Жёлтый",    "Жёлтый",    "Белый", "Белый" }},
        { "Наличие пильских трапков", new[]{ "Да",      "Да",        "Да",        "Да",    "Да"    }}
    };
    
    var matrix = input.ToDictionary
    (
        pair => pair.Key,
        pair => pair.Value.Select((e, i) => new {e, i}).ToDictionary(p => classes[p.i], p => p.e)
    );

    Console.WriteLine("-= Распознаватель жуков =-");
    string[] species = Interact(BuildDecisionTree(matrix)).ToArray();

    if (species.Length == 0)
        Console.WriteLine("Распознать жука не удалось.");
    else if (species.Length == 1)
        Console.WriteLine("Жук относится к виду {0}", species.Single());
    else
        Console.WriteLine("Жук относится к одному из видов: {0}", string.Join(", ", species));
}

// Calculates information entropy of a distribution
double Entropy<T>(IEnumerable<T> dist)
{
    return Entropy(dist.GroupBy(e => e, (key, elems) => new KeyValuePair<T, int>(key, elems.Count())));
}

// Calculates information entropy of a distribution
double Entropy<K>(IEnumerable<KeyValuePair<K,int>> dist)
{
    double N = dist.Select(e => e.Value).Sum();
    return dist.Aggregate(0.0, (f, e) => f + e.Value/N*Math.Log(N/e.Value));
}

// General-purpose extension methods of IEnumerable<T>
public static class EnumerableEx
{
    public static T MaxBy<T>(IEnumerable<T> source, Func<T, double> keySelector)
    {
        T result = source.First();
        var maxkey = keySelector(result);
        
        foreach (var e in source.Skip(1))
        {
            var key = keySelector(e);
            if (key > maxkey)
            {
                result = e;
                maxkey = key;
            }
        }
        
        return result;
    }
}
