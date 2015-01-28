// Solution for http://acm.timus.ru/problem.aspx?space=1&num=1029 ("Ministry")
// Via Dijkstra shortest path, time complexity O(MxNxlog(MxN))

#include <algorithm>
#include <cstdio>
#include <iterator>
#include <vector>

using namespace std;

template <typename T, typename Compare, typename Map> class pqueue
{
private:
    vector<T> heap_;
    Map indices_; // Mapping of a value to its index in the heap_ vector. Required for decrease_key().
    Compare comp_;

    size_t get_parent(size_t i) { return (i - 1) / 2; }
    size_t get_left(size_t i)   { return i * 2 + 1; }
    size_t get_right(size_t i)  { return i * 2 + 2; }

    void percolate_up(size_t i)
    {
        while (i != 0)
        {
            auto p = get_parent(i);
            if (comp_(heap_[p], heap_[i])) break;
            swap(heap_[p], heap_[i]);

            indices_[heap_[p]] = p;
            indices_[heap_[i]] = i;

            i = p;
        }
    }

    void percolate_down(size_t i)
    {
        for (;;)
        {
            size_t min = i;

            size_t l = get_left(i);
            size_t r = get_right(i);

            if (l >= heap_.size()) break;

            if (comp_(heap_[l], heap_[i])) min = l;
            if (r < heap_.size() && comp_(heap_[r], heap_[min])) min = r;

            if (min == i) break;

            swap(heap_[i], heap_[min]);

            indices_[heap_[min]] = min;
            indices_[heap_[i]] = i;

            i = min;
        }
    }

public:
    pqueue(const Compare& comp = Compare(), const Map& map = Map()) :
        comp_(comp),
        indices_(map)
    {
    }

    friend void swap(pqueue<T, Compare, Map>& left, pqueue<T, Compare, Map>& right)
    {
        using std::swap;

        swap(left.heap_, right.heap_);
        swap(left.indices_, right.indices_);
        swap(left.comp_, right.comp_);
    }

    void push(T e)
    {
        heap_.push_back(e);

        size_t i = heap_.size() - 1;
        indices_[e] = i;

        percolate_up(i);
    }

    void decrease_key(const T& e)
    {
        decrease_key(indices_.find(e)->second);
    }

    void decrease_key(size_t i)
    {
        percolate_up(i);
    }

    void push_or_decrease(const T& e)
    {
        size_t i = indices_[e];
        if (i == static_cast<size_t>(-1))
            push(e);
        else
            decrease_key(i);
    }

    const T& top()
    {
        return heap_.front();
    }

    void pop()
    {
        indices_.erase(heap_.front());
        if (heap_.size() > 1) swap(heap_.front(), heap_.back());
        heap_.pop_back();

        if (heap_.empty()) return;

        indices_[heap_[0]] = 0;
        percolate_down(0);
    }

    bool empty() const
    {
        return heap_.empty();
    }
};

struct nodeid
{
    int i;
    int j;

    friend bool operator<(const nodeid& a, const nodeid& b)
    {
        return a.i < b.i || a.i == b.i && a.j < b.j;
    }

    friend bool operator==(const nodeid& a, const nodeid& b)
    {
        return a.i == b.i && a.j == b.j;
    }
};

const int MAX_M = 100; // Max possible number of floors
const int MAX_N = 500; // Max possible number of rooms on a floor

unsigned long long input[MAX_M][MAX_N]; // Ministry as read from the input
unsigned long long lens [MAX_M][MAX_N]; // Lengths of the shortest paths
nodeid             pred [MAX_M][MAX_N]; // Predecessor room on the shortest path
size_t             ind  [MAX_M][MAX_N]; // Indices in the priority queue's heap

int m; // Number of floors
int n; // Number of rooms on each floor

void get_succs(nodeid id, vector<nodeid>& succs) // Output reference here far outperforms return by value
{
    succs.clear();

    succs.push_back({ id.i + 1, id.j });

    if (id.j != 0)    succs.push_back({ id.i, id.j - 1 });
    if (id.j < n - 1) succs.push_back({ id.i, id.j + 1 });
}

struct lencomp
{
    bool operator()(const nodeid& a, const nodeid& b) const
    {
        return lens[a.i][a.j] < lens[b.i][b.j];
    }
};

struct nodeidhash
{
    size_t& operator[](nodeid id)
    {
        return ind[id.i][id.j];
    }

    void erase(nodeid id)
    {
        ind[id.i][id.j] = static_cast<size_t>(-1);
    }
};

int main()
{
    scanf("%d%d", &m, &n);

    for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
    {
        scanf("%llu", &input[i][j]);
        lens[i][j] = i == 0 ? input[i][j] : static_cast<unsigned long long>(-1);
        ind[i][j] = static_cast<size_t>(-1);
    }

    pqueue<nodeid, lencomp, nodeidhash> q;

    for (int j = 0; j < n; ++j)
    {
        pred[0][j] = { -1, -1 };
        q.push({ 0, j });
    }

    nodeid cur;
    vector<nodeid> succs;

    for ( ; ; )
    {
        cur = q.top();

        if (cur.i == m - 1) break;

        get_succs(cur, succs);

        for (const auto& s : succs)
        {
            auto len = lens[cur.i][cur.j] + input[s.i][s.j];

            if (len < lens[s.i][s.j])
            {
                lens[s.i][s.j] = len;
                pred[s.i][s.j] = { cur.i, cur.j };
                q.push_or_decrease(s);
            }
        }

        q.pop();
    }

    vector<int> result;

    do
    {
        result.push_back(cur.j + 1);
        cur = pred[cur.i][cur.j];
    } while (cur.i >= 0);

    for (auto p = result.rbegin(); p != result.rend(); ++p)
        printf("%d ", *p);
}
