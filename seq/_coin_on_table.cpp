// https://www.hackerrank.com/challenges/coin-on-the-table?h_r=next-challenge&h_v=zen

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <utility>
#include <map>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;

struct pos {
    pos(int ai, int aj) : i(ai), j(aj) {}
    pos(const pos& other) : i(other.i), j(other.j) {}
    int i;
    int j;
    
    friend bool operator<(const pos& l, const pos& r) {
        return l.i < r.i || l.i == r.i && l.j < r.j;
    }
};

class bset
{
    int n, m;
    vector<uint64_t> v;

public:
    bset(int an, int am) : n(an), m(am), v(n * m / 64 + 1, 0) {} 

    bool contains(pos ij) const {
        auto idx_with_mask = to_mask(ij);
        return v[idx_with_mask.first] & idx_with_mask.second;
    }

    pair<int, uint64_t> to_mask(pos ij) const { return {(ij.i * n + ij.j) / 64, 1 << (ij.i * n + ij.j) % 64}; } 

    friend bset operator +(bset src, pos ij) {
        auto idx_with_mask = src.to_mask(ij);
        src.v[idx_with_mask.first] |= idx_with_mask.second;
        return src;
    }

    friend bool operator <(const bset& l, const bset& r) {
        return l.v < r.v;
    }
};

int n, m, k;
string board;
map<pos, int> d;

char& at(pos pos) { return board[pos.i * n + pos.j]; }

pos adjust(pos ij, char c) {
    return c == 'L' ? pos(ij.i, ij.j - 1) :
           c == 'R' ? pos(ij.i, ij.j + 1) :
           c == 'U' ? pos(ij.i - 1, ij.j) :
           c == 'D' ? pos(ij.i + 1, ij.j) :
                      throw runtime_error("");
}

int solve(const bset& bset, pos ij, int rest)
{
    int r = numeric_limits<int>::max();
    
    if (rest < 0 || ij.i < 0 || ij.i >= n || ij.j < 0 || ij.j >= m || bset.contains(ij))
        return r;
    
    if (at(ij) == '*') return 0;

    auto p = d.find(ij);
    if (p != d.end()) return p->second;
    
    for (auto&& dir : {'L', 'R', 'U', 'D'})
    {
        pos newpos(adjust(ij, dir));
        int rr = solve(bset + ij, newpos, rest - 1);
        if (rr == numeric_limits<int>::max()) continue;
        if (dir != at(ij)) ++rr;
        if (rr < r) r = rr;
    }

    return d[ij] = r;
}

int main() {
    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;
        board += s;
    }

    cout << solve(bset(n, m), pos(0, 0), k);
}
