// Constant memory solution for the "Volume of the trapped water" problem.
//
// Input: vector of non-negative numbers. Each element is the height of a 1-width column
// of concrete. Adjacent columns stick together seamlessly.
//
// The vector is read from the standard input as whitespace-separated list of decimal numbers.
// Use Ctrl+Z to indicate the end of input when using Windows console.
//
// Output: the volume of the water trapped in the construction when the shower
// is turned off.

#include <algorithm>
#include <iterator>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main()
{
    vector<int> v((istream_iterator<int>(cin)), istream_iterator<int>());

    if (v.size() < 2)
    {
        cout << 0;
        return 0;
    }

    int iLeft  = 0;                               // Position of the left cursor
    int iRight = static_cast<int>(v.size() - 1);  // Position of the right cursor

    bool isLeftActive;
    int cap;
    int highest_so_far;
    
    tie(isLeftActive, cap, highest_so_far) = v[iLeft] <= v[iRight] ? make_tuple(true,  v[iLeft],  v[iRight]) :
                                                                     make_tuple(false, v[iRight], v[iLeft]); 

    int volume = 0;

    while (iLeft < iRight - 1)
    {
        int h = v[isLeftActive ? ++iLeft : --iRight];

        if (h <= cap)
        {
            volume += cap - h;
            continue;
        }

        if (h <= highest_so_far)
        {
            cap = h;
            continue;
        }

        cap = highest_so_far;
        highest_so_far = h;

        isLeftActive = !isLeftActive;
    }

    cout << volume;
}
