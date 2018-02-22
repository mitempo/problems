class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> r;
        sort(nums.begin(), nums.end());
        r.push_back(nums);
        while (next_perm(nums.begin(), nums.end()))
            r.push_back(nums);
        return r;
    }
    
    template <typename I> bool next_perm(I pb, I pe)
    {
        auto postpeak = is_so_u(make_reverse_iterator(pe), make_reverse_iterator(pb));
        if (postpeak.base() != pb)
            iter_swap(postpeak, upper_bound(make_reverse_iterator(pe), postpeak, *postpeak));
        reverse(make_reverse_iterator(pe), postpeak);
        return postpeak.base() != pb;
    }
    
    template <typename I> I is_so_u(I pb, I pe)
    {
        auto p = adj_f(pb, pe, greater<>());
        return p == pe ? p : next(p);
    }
    
    template <typename I, typename Predicate> I adj_f(I pb, I pe, Predicate pr)
    {
        while (pb != pe && !pr(*pb, *next(pb))) ++pb;
        return pb;
    }
};
