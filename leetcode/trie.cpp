// https://leetcode.com/problems/implement-trie-prefix-tree
// Version with map: in lower 20th percentile for speed, in upper 20th percentile for memory

struct Trie {
    struct node
    {
        bool isStop;
        unordered_map<char, unique_ptr<node>> children;
        
        node() : isStop(false) {}
        node(string_view s) : node() { add(s); }

        void add(string_view s)
        {
            if (s.empty())
            {
                isStop = true;
                return;
            }

            char c = s.front();
            s.remove_prefix(1);

            auto& p = children[c];
            if (p)
                p->add(s);
            else
                p = make_unique<node>(s);
        }
        
        pair<const node *, string_view> follow(string_view s) const
        {
            if (s.empty()) return {this, s};
            
            auto p = children.find(s.front());

            if (p == cend(children)) return {this, s};
            
            s.remove_prefix(1);
            return p->second->follow(s);
        }


        bool contains(string_view s) const
        {
            auto[p, s_final] = follow(s);
            return s_final.empty() && p->isStop;
        }

        bool contains_prefix(string_view s) const
        {
            auto[p, s_final] = follow(s);
            return s_final.empty();
        }
    };

    node root;

public:
    Trie() = default;      
    
    void insert(string word) {
        root.add(word);        
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        return root.contains(word);        
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return root.contains_prefix(prefix);
    }
};
