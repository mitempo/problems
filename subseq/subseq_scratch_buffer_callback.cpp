// Problem:
//   Given a sequence, generate k-element subsequences (combinations)

#include <iostream>
#include <functional>
#include <vector>

using namespace std;

// Generates k-element subsequences of a sequence defined by pb and pe iterators.
// Each subsequence is generated in turn in the same scratch buffer, pointed to by presult. fVisit
// is called after each subsequence is generated
template <typename FI, typename FO> void seq(FI pb, FI pe, unsigned int k, FO presult, function<void()> fVisit)
{
    if (k == 0) return fVisit();

    while (pb != pe)
    {
        *presult = *pb++;
        seq(pb, pe, k - 1, presult + 1, fVisit);
    }
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};

    vector<int> result(3);

    seq(v.cbegin(), v.cend(), 3, result.begin(), [&result]()
    {
        cout << "( ";
        for (const auto& e : result) 
            cout << e << " ";
        cout << ")" << endl;
    });
}
