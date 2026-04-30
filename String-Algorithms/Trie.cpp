#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class TrieNode
{
public:
    TrieNode *child[26];
    bool isLeaf;

    TrieNode()
    {
        isLeaf = false;
        for (int i = 0; i < 26; i++)
        {
            child[i] = NULL;
        }
    }
};
class Trie
{
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }
    void insert(const string &s)
    {
        TrieNode *cur = root;

        for (char c : s)
        {
            if (cur->child[c - 'a'] == NULL)
            {
                cur->child[c - 'a'] = new TrieNode();
            }
            cur = cur->child[c - 'a'];
        }
        cur->isLeaf = true;
    }

    bool search(const string &s)
    {
        TrieNode *cur = root;
        for (char c : s)
        {
            if (cur->child[c - 'a'] == NULL)
                return false;
            cur = cur->child[c - 'a'];
        }
        return cur->isLeaf;
    }
    bool isPrefix(const string &s)
    {
        TrieNode *cur = root;
        for (char c : s)
        {
            if (!cur->child[c - 'a'])
                return false;
            cur = cur->child[c - 'a'];
        }
        return true;
    }
};

int main()
{
    Trie trie;
    trie.insert("hello");
    trie.insert("world");
    cout << trie.search("hello") << endl; // Output: 1 (true)
    cout << trie.search("world") << endl; // Output: 1 (true)
    cout << trie.search("hi") << endl;    // Output: 0 (false)
    cout << trie.isPrefix("he") << endl;   // Output: 1 (true)
    cout << trie.isPrefix("wo") << endl;   // Output: 1 (true)
    cout << trie.isPrefix("hi") << endl;   // Output: 0 (false)
    return 0;
}
